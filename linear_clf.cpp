#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
int main(int argc, char const *argv[])
{
    cout<<"child"<<endl;
    // const char* myfifo = "test";
    // char buff[1] = {'s'};
    // mkfifo(myfifo , 0666);
    // int fd = open(myfifo , O_RDONLY);
    // while (buff[0] != 0)
    // {
    //     read(fd , buff , 1);
    //     write(1 , buff , 1);
    // }
    // close(fd);
    // // write(1 , buff , strlen(buff));
    // read(0 , buff , 1);
    return 0;
}
