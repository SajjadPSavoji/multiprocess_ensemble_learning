#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>

#include "lc_utils.hpp"

using namespace std;

int n_clf()
{
    char buff[BUFF_SIZE];
    read_from_pipe(rcv_pipe_name() , buff);
    return atoi(buff);
}

int* init_pipes(int n)
{
    int* fds = (int*)malloc((n+1)*sizeof(int));
    for (size_t i = 0; i < n; i++)
    {
        mkfifo(to_string(i).c_str() , O_CREAT | S_IRWXU);
        fds[i] = open(to_string(i).c_str(), O_RDONLY);
    }
    return fds;
}

vector<vector<string>> fetch_data(int* fds , int n)
{
    vector<vector<string>> data;
    
    // for each classifier
    for (size_t i = 0; i < n; i++)
    {
        char buff[BUFF_SIZE] = {PHONY};
        // get data
        read(fds[i] , buff , BUFF_SIZE);
        vector<string> clf;
        string temp = "";
        // convert data to vector of string
        for (size_t j = 0; j < BUFF_SIZE && buff[j] != PHONY; j++)
        {
            if (buff[j] == CRAP)
            {
                if(temp.size() == ZERO)
                    break;
                clf.push_back(temp);
                temp = "";
                continue;

            }
            temp.push_back(buff[j]);
        }
        data.push_back(clf);
        clf.clear();
    }
    return data;
}

void close_pipes(int n , int* fds)
{
    for (size_t i = 0; i < n; i++)
    {
        close(fds[i]);
    }
}

vector<string> mejority_vote(vector<vector<string>> data)
{
    vector<string> result;
    // for each prediction
    for (size_t j = 0; j < data[0].size(); j++)
    {
        map<string , int> freq;
        for (size_t i = 0; i < data.size(); i++)
        {
            if (freq.find(data[i][j]) == freq.end())
                freq[data[i][j]] = 1;
            else
                freq[data[i][j]] += 1;
        }
        string max_key = "";
        int max_rep = 0;
        
        for (auto itr = freq.begin(); itr != freq.end(); itr++)
        {
            if (itr->second > max_rep)
            {
                max_rep = itr->second;
                max_key = itr->first;
            }
        }
        result.push_back(max_key);
    }
    return result;
}

void send_result(vector<string> result , char* pipe_name)
{
    string temp = "";
    for (size_t i = 0; i < result.size(); i++)
    {
        temp += result[i];
        temp.push_back(CRAP);
    }
    int fd = open(pipe_name , O_WRONLY);
    write(fd , temp.c_str() , temp.size()+1);
    close(fd);
}