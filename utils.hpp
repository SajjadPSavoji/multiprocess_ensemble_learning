#ifndef __UTILS__HEAD__
#define __UTILS__HEAD__

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "Dir.hpp"

#define LIN_CLF_FILE "./linear_clf.o"
#define VOTE_FILE "./voter.o"
#define PIPE1_NAME "lavel1_pipe"
#define BUFF_SIZE 256
#define DELIM 0
#define PHONY '*'
#define ONE 1
#define ZERO 0

char* lc_args[] = {LIN_CLF_FILE , NULL};
char* vt_args[] = {VOTE_FILE , NULL};

using namespace std;

void make_n_lin_clf(int n);
void make_voter();
void wait_till_done(int n);
void send_weight_files(vector<string> &dirs);


void make_n_lin_clf(int n)
{
    for (size_t i = 0; i < n; i++)
    {

        int pid = fork();
        if(pid == 0) //for each child(linear classifer)
            execvp(lc_args[0],lc_args);
    }
}

void make_voter()
{
    int pid = fork();
    if(pid == 0) //make child (voter)
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

void send_weight_files(vector<string> &dirs)
{
    int n = dirs.size();
    mkfifo(PIPE1_NAME , 0666);
    int fd = open(PIPE1_NAME , O_WRONLY);

    for (size_t i = 0; i < n; i++)
    {
        write(fd , dirs[i].c_str() , strlen(dirs[i].c_str()) + 1);
    }
    wait_till_done(n+1);
    close(fd);
}

#endif