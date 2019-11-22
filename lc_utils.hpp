#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "CSV.hpp"
#include "LC.hpp"

#define PIPE_NAME_PRFIX "PIP_"
#define BUFF_SIZE 4096
#define DELIM 0
#define ONE 1
#define ZERO 0
#define PHONY '*'
#define UNDERSCORE '_'
#define DOT '.'
#define END_CH '!'
#define CRAP '&'

using namespace std;


char* rcv_pipe_name()
{
    return strdup((string(PIPE_NAME_PRFIX) + to_string(getpid())).c_str());
}

void read_from_pipe(char* pipe_name , char* buff)
{
    mkfifo(pipe_name , O_CREAT | S_IRWXU);
    int fd = open(pipe_name , O_RDONLY);
    read(fd , buff , BUFF_SIZE);
    close(fd);
}
void split(char* buff , char* weight_file , char* valid_file)
{
    int w_idx = 0;
    int v_idx = 0;
    int b_idx = 0;
    
    for (; b_idx < BUFF_SIZE && buff[b_idx] != CRAP; b_idx++ , w_idx++)
        weight_file[w_idx] = buff[b_idx];
    
    b_idx ++;

    for (; b_idx < BUFF_SIZE && buff[b_idx] != CRAP; b_idx++ , v_idx++)
        valid_file[v_idx] = buff[b_idx];

}

char* send_pipe_name(char* weight_file)
{
    string temp(weight_file);
    string name;
    int underscore_indx = 0;
    for (int i = 0; i < temp.size(); i++)
        if(temp[i] == UNDERSCORE)
            underscore_indx = i;

    int dot_indx = 0;
    for (int i = 0; i < temp.size(); i++)
        if(temp[i] == DOT)
            dot_indx = i;

    for (int i = underscore_indx + 1; i < dot_indx ; i++)
    {
        name.push_back(temp[i]);
    }
    return strdup(name.c_str());
}

void send_estimations(std::vector<std::string> ests , char* pipe_name)
{
    string temp = "";
    for (size_t i = 0; i < ests.size(); i++)
    {
        temp += ests[i];
        temp.push_back(CRAP);
    }
    
    mkfifo(pipe_name  ,O_CREAT | S_IRWXU);
    int fd = open(pipe_name , O_WRONLY);
    write(fd , temp.c_str() , temp.size());
    close(fd);
    unlink(pipe_name);
}