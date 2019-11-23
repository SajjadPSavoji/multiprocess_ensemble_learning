#include "utils.hpp"

int main(int argc, char const *argv[])
{
    // get input from terminal
    const char* valid_dir = argv[1];
    const char* weights_dir = argv[2];

    // make a Dir class 
    Dir dir(weights_dir);
    vector<string> weight_files = dir.get_sub_dir();
    int n = weight_files.size();
    vector<string> pipe_names;

    // init un_named pipe params
    init_send_pipe(n);

    // make n linear lassifier and one voter as classifier fusion method
    make_n_lin_clf(n , pipe_names);
    make_voter(n , pipe_names);
    
    // send data to each linear classifier
    send_info_to_clf(pipe_names , valid_dir , weight_files);
    send_info_to_voter(pipe_names , n);

    // wait for all classifiers to terminalte
    wait_till_done(n);

    // get final result from voter
    vector<string> res = result(pipe_names);
    wait_till_done(1);
    
    // read original labels
    CSV labels(strdup(valid_label_path(valid_dir).c_str()));
    labels.fetch_data();
    
    // output accuracy in specified format
    cout<<std::fixed;
    cout<<"Accuracy: "<<std::setprecision(2)<<labels.acc(res)*100<<"%"<<endl;
    
    // delete pipes created for data communication
    del_pipes(pipe_names);

    return 0;
}
