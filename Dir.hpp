#ifndef __DIR__HEADER__
#define __DIR__HEADER__
/*
this class is a wrapper for unix drent.h
aimed to simplify it's use for unix users
*/
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <vector>

#define SLASH '/'

class Dir
{
private:
    char * dir_name;
public:
    Dir(const char* dir);
    ~Dir();
    std::vector<std::string> get_sub_dir();
};

Dir::Dir(const char* dir)
{
    this->dir_name = (char*) malloc(strlen(dir)+1);
    strcpy(this->dir_name , dir);
}

Dir::~Dir()
{
    free(this->dir_name);
}
std::vector<std::string> Dir::get_sub_dir()
{
    std::vector<std::string> sub_dirs;
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    std::string base = std::string(this->dir_name);
    if(base.back() != SLASH)
        base.push_back(SLASH);
    
    dp = opendir(this->dir_name);
    if (dp != nullptr) {
        while ((entry = readdir(dp)))
        {
            sub_dirs.push_back(base+ std::string(entry->d_name));
            if(sub_dirs.back() == base + "." || sub_dirs.back() == base + "..")
                sub_dirs.pop_back();
        }
    }
    closedir(dp);
    return sub_dirs;
}

#endif
