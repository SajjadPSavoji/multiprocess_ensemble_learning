#include "voter_utils.hpp"
int main(int argc, char const *argv[])
{
    // get number of classifiers from ensembler via pipe
    int n = n_clf();

    // make pipes to communicate
    int* fds = init_pipes(n);

    // get estimations from linear classifiers
    vector<vector<string>> data = fetch_data(fds , n);

    // close pipes and send result to ensembler
    close_pipes(n , fds);
    send_result(mejority_vote(data) , rcv_pipe_name());
    
    return 0;
}
