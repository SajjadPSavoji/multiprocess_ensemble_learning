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

    // communicate file names with pipes
    send_weight_files(weight_files);
    cout<<"parent done"<<endl;

    return 0;
}
