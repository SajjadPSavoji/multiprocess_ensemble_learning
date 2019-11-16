#ifndef __LC__HEAD__
#define __LC__HEAD__

#include "CSV.hpp"
#define ONE_STR "1"

class LC
{
private:
    CSV weights;
    
public:
    LC(CSV csv):weights(csv){}
    ~LC(){}
    std::string estimate_instance(std::vector<std::string> feature);
    std::vector<std::string> estimate_csv(CSV csv);
    int dot(std::vector<std::string> feature , std::vector<std::string> weight);

};
int str2int(std::string s);

std::vector<std::string> LC::estimate_csv(CSV csv)
{
    std::vector<std::string> ests;
    for (size_t i = 0; i < csv.size(); i++)
    {
        ests.push_back(this->estimate_instance(csv[i]));
    }
    return ests;
}

std::string LC::estimate_instance(std::vector<std::string> feature)
{
    feature.push_back(ONE_STR);
    std::vector<int> scores;
    for (size_t i = 1; i < this->weights.size(); i++)
    {
        scores.push_back(this->dot(feature , weights[i]));
    }
    return std::to_string(std::max_element(scores.begin(),scores.end()) - scores.begin()); 
}

int LC::dot(std::vector<std::string> feature , std::vector<std::string> weight)
{
    int sum = 0;
    for (size_t i = 0; i < weight.size(); i++)
    {
        sum += str2int(weight[i]) * str2int(feature[i]);
    }
    return sum;
}
int str2int(std::string s){
    std::stringstream stream(s);
    int x = 0;
    stream >> x;
    return x; 
}

#endif