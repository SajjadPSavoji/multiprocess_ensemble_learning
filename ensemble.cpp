#include "utils.hpp"

int main(int argc, char const *argv[])
{
    const char* valid_dir = argv[1];
    const char* weights_dir = argv[2];


    Dir dir(weights_dir);
    vector<string> weight_files = dir.get_sub_dir();
    int n = weight_files.size();

    vector<string> pipe_names;

    make_n_lin_clf(n , pipe_names);
    make_voter(n , pipe_names);

    // for (size_t i = 0; i < pipe_names.size(); i++)
    // {
    //     cout<<pipe_names[i]<<endl;
    // }

    send_info_to_clf(pipe_names , valid_dir , weight_files);
    wait_till_done(n);
    vector<string> res = result(pipe_names);
    wait_till_done(1);
    
    // for (size_t i = 0; i < res.size(); i++)
    // {
    //     cout<<res[i]<<',';
    // }
    // cout<<endl;


    // read labels
    CSV labels(strdup(valid_label_path(valid_dir).c_str()));
    labels.fetch_data();
    // cout<<labels;
    // cout<<res<<endl;
    // cout<<res.size()<<endl;
    // cout<<labels.size()<<endl;

    // for (size_t i = 1; i < labels.size(); i++)
    // {
    //     cout<<labels[i][0]<<",";
    // }
    // cout<<endl;
    

    cout<<std::fixed;
    cout<<"Accuracy: "<<std::setprecision(2)<<labels.acc(res)*100<<"%"<<endl;
    
    del_pipes(pipe_names);
    // cout<<"parent done"<<endl;
    return 0;
}
