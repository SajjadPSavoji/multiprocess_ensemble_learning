#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "CSV.hpp"

#define PIPE1_NAME "lavel1_pipe"
#define BUFF_SIZE 256
#define DELIM 0
#define PHONY '*'
#define ONE 1
#define ZERO 0

using namespace std;

void get_weight_file_name(char* c , char* buff);

void get_weight_file_name(char* c , char* buff)
{
    int fd = open(PIPE1_NAME , O_RDONLY);
    for (size_t i = 0; i <BUFF_SIZE && c[ZERO] != DELIM ; i++)
    {
        read(fd , c , ONE);
        buff[i] = c[ZERO];
    }
    close(fd);
}