#include "voter_utils.hpp"
int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    // cout<<"voter : "<<n<<endl;
    int* fds = init_pipes(n);
    vector<vector<string>> data = fetch_data(fds , n);
    // cout<<mejority_vote(data).size()<<endl;
    close_pipes(n , fds);
    send_result(mejority_vote(data) , rcv_pipe_name());
    return 0;
}
