#include "lc_utils.hpp"
int main(int argc, char const *argv[])
{   
    // local variables
    char buff_unnamed[BUFF_SIZE] = {PHONY};
    char buff[BUFF_SIZE] = {PHONY};
    char weight_file[BUFF_SIZE] = {PHONY};
    char valid_file[BUFF_SIZE] = {PHONY};

    // get data from ensembler
    read_from_unnamed_pipe(argv , buff_unnamed);
    read_from_pipe(rcv_pipe_name() , buff);
    split(buff_unnamed , weight_file , valid_file);    

    // read csv files
    CSV weights(weight_file);
    weights.fetch_data();
    CSV data(valid_file);
    data.fetch_data();

    // load linea classifier
    LC lc(weights);
    vector<string> estimations = lc.estimate_csv(data);

    // send estimations to voter
    send_estimations(estimations , send_pipe_name(weight_file));
    
    return 0;
}
