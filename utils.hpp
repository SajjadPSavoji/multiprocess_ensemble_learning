#ifndef __UTILS__HEAD__
#define __UTILS__HEAD__

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>

#include "Dir.hpp"
#include "CSV.hpp"

#define LIN_CLF_FILE "./linear_clf.o"
#define VOTE_FILE "./voter.o"
#define PIPE_NAME_PRFIX "PIP_"
#define BUFF_SIZE 4096
#define DELIM 0
#define PHONY '*'
#define TWO 2
#define ONE 1
#define ZERO 0
#define CRAP '&'

#define SLASH '/'
#define DATASET "dataset.csv"
#define LABEL "labels.csv"

using namespace std;

char* lc_args[] = {LIN_CLF_FILE , NULL , NULL};
char* vt_args[] = {VOTE_FILE , NULL , NULL};
vector<int> pip_0;
vector<int> pip_1;
int pip[TWO];


void make_n_lin_clf(int n , vector<string> &pipe_names);
void make_voter(int n , vector<string> &pipe_names);
void wait_till_done(int n);
string valid_data_path(const char* valid_dir);
string valid_label_path(const char* valid_dir);
void send_info_to_clf( vector<string> pipe_names,const char* valid_dir ,  vector<string> &dirs);
void make_pipe(int pipe_number , vector<string> &pipe_names);
void del_pipes(vector<string> pipe_names);
void send_info_to_voter(vector<string> pipe_names , int n);
void init_send_pipe();
void init_lc_args();

void init_send_pipe(int n)
{
    for (size_t i = 0; i < n; i++)
    {
        pipe(pip);
        pip_0.push_back(pip[ZERO]);
        pip_1.push_back(pip[ONE]);
    }
}

void init_lc_args(int pip_0 , int pip_1)
{
    lc_args[ONE] = strdup(to_string(pip_0).c_str());
    lc_args[TWO] = strdup(to_string(pip_1).c_str());
}

void del_pipes(vector<string> pipe_names)
{
    for (size_t i = 0; i < pipe_names.size(); i++)
    {
        unlink(pipe_names[i].c_str());
    }
}

void make_pipe(int n ,vector<string> &pipe_names)
{    
    mkfifo((string(PIPE_NAME_PRFIX) + to_string(n)).c_str() , O_CREAT | S_IRWXU);
    pipe_names.push_back((string(PIPE_NAME_PRFIX) + to_string(n)));
}


void make_n_lin_clf(int n , vector<string> &pipe_names)
{
    for (size_t i = 0; i < n; i++)
    {

        int pid = fork();
        if(pid)
            make_pipe(pid , pipe_names);
        else
        {
            init_lc_args(pip_0[i] , pip_1[i]);
            execvp(lc_args[0],lc_args);
        }
    }
}

void make_voter(int n , vector<string> &pipe_names)
{
    int pid = fork();
    vt_args[1] = strdup(to_string(n).c_str());
    if(pid)
        make_pipe(pid , pipe_names);
    else
        execvp(vt_args[0],vt_args);
}

void wait_till_done(int n)
{
    for (size_t i = 0; i < n; i++)
    {
        int status;
        wait(&status);
    }
}

void send_info_to_clf( vector<string> pipe_names,const char* valid_dir ,  vector<string> &dirs)
{
    // send weights file name and valid directory name
    string temp = "";
    for (size_t i = 0; i < pipe_names.size()-1; i++)
    {
        // make message
        temp += dirs[i];
        temp.push_back(CRAP);
        temp += valid_data_path(valid_dir);
        temp.push_back(CRAP);

        // send via un_named pipe
        write(pip_1[i] , temp.c_str() , temp.size());
        close(pip_1[i]);

        // send via named pipe
        int fd = open(pipe_names[i].c_str() , O_WRONLY);
        write(fd ,temp.c_str(), temp.size());
        temp = "";
        close(fd);
    }
}

void send_info_to_voter(vector<string> pipe_names , int n)
{
    int fd = open(pipe_names.back().c_str() , O_WRONLY);
    write(fd , (to_string(n)+ CRAP).c_str() , strlen(to_string(n).c_str()) + 1);
    close(fd);
}

string valid_data_path(const char* valid_dir)
{
    string temp(valid_dir);
    if(temp.back() != SLASH)
        temp.push_back(SLASH);
    return temp + string(DATASET);
}

string valid_label_path(const char* valid_dir)
{
    string temp(valid_dir);
    if(temp.back() != SLASH)
        temp.push_back(SLASH);
    return temp + LABEL;
}

vector<string> result(vector<string> pipe_names)
{
    vector<string> res;
    char buff[BUFF_SIZE] = {PHONY};
    string temp = "";
    int fd = open(pipe_names.back().c_str() , O_RDONLY);
    read(fd , buff , BUFF_SIZE);
    for (size_t i = 0; i < BUFF_SIZE && buff[i] != PHONY ; i++)
    {
        if(buff[i] == CRAP)
        {
            if(temp.size() == ZERO)
                break;
            res.push_back(temp);
            temp = "";
            continue;
        }
        temp.push_back(buff[i]);
    }
    close(fd);
    return res;
}

#endif