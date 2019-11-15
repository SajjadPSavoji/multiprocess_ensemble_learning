#include "lc_utils.hpp"
int main(int argc, char const *argv[])
{
    cout<<"child"<<endl;
    char buff[BUFF_SIZE] = {PHONY};
    char c[ONE]={PHONY};

    get_weight_file_name(c , buff);
    
    CSV csv(buff);
    csv.fetch_data();
    cout<<csv;
    cout<<buff<<endl;
    return 0;
}
