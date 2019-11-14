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

char* lc_args[] = {LIN_CLF_FILE , NULL};
char* vt_args[] = {VOTE_FILE , NULL};

using namespace std;

void make_n_lin_clf(int n);
void make_voter();
void wait_till_done(int n);

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

#endif