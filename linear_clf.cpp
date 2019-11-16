#include "lc_utils.hpp"
int main(int argc, char const *argv[])
{
    // cout<<"child"<<endl;
    char buff[BUFF_SIZE] = {PHONY};
    char weight_file[BUFF_SIZE] = {PHONY};
    char valid_file[BUFF_SIZE] = {PHONY};

    read_from_pipe(rcv_pipe_name() , buff);
    split(buff , weight_file , valid_file);    

    // read csv files
    CSV weights(weight_file);
    weights.fetch_data();
    CSV data(valid_file);
    data.fetch_data();

    // load linea classifier
    LC lc(weights);
    vector<string> estimations = lc.estimate_csv(data);

    // cout<<valid_file<<endl;
    // cout<<weight_file<<endl;

    // cout<<"estimations in child"<<endl;
    // for (size_t i = 0; i < estimations.size(); i++)
    // {
    //     cout<<estimations[i]<<",";
    // }
    // cout<<endl;


    send_estimations(estimations , send_pipe_name(weight_file));
    // cout<<"clf sent data and exits"<<endl;
    
    // cout<<pipe_name(weight_file)<<endl;
    // make pipe given

    // esttimate and 

    // cout<<weights;
    // cout<<data;
    // csv.fetch_data();
    // CSV csv2(csv);
    // cout<<csv;
    // cout<<csv2;
    // cout<<buff<<endl;
    return 0;
}
