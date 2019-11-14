#include "utils.hpp"

int main(int argc, char const *argv[])
{
    const char* valid_dir = argv[1];
    const char* weights_dir = argv[2];


    Dir dir(weights_dir);
    vector<string> weight_files = dir.get_sub_dir();
    int n = weight_files.size();

    make_n_lin_clf(n);
    make_voter();
    wait_till_done(n);

    cout<<"parent done"<<endl;

    // for (size_t i = 0; i < n; i++)
    // {

    //     int pid = fork();
    //     if(pid == 0) //for each child(linear classifer)
    //         execvp(lc_args[0],lc_args);
    // }

    // execvp(lc_args[0],lc_args);
    
    // for (size_t i = 0; i < n; i++)
    // {
    //     int status;
    //     wait(&status);
    // }
    

    
    

    // iterate over files and print file names
    // struct dirent *entry = nullptr;
    // DIR *dp = nullptr;

    // dp = opendir(weights_dir);
    // if (dp != nullptr) {
    //     while ((entry = readdir(dp)))
    //         printf ("%s\n", entry->d_name);
    // }

    // closedir(dp);



    // const char* myfifo = "test";
    // const char* msg = "salam";
    // mkfifo(myfifo , 0666);
    // int fd = open(myfifo , O_WRONLY);
    // write(fd , msg , strlen(msg)+1);
    // close(fd);
    return 0;
}
