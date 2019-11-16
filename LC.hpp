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
    float dot(std::vector<std::string> feature , std::vector<std::string> weight);

};
float str2float(std::string s);

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
    std::vector<float> scores;
    for (size_t i = 1; i < this->weights.size(); i++)
    {
        scores.push_back(this->dot(feature , weights[i]));
    }
    return std::to_string(std::max_element(scores.begin(),scores.end()) - scores.begin()); 
}

float LC::dot(std::vector<std::string> feature , std::vector<std::string> weight)
{
    float sum = 0;
    for (size_t i = 0; i < weight.size(); i++)
    {
        sum += str2float(weight[i]) * str2float(feature[i]);
    }
    return sum;
}
float str2float(std::string s){
    std::stringstream stream(s);
    float x = 0;
    stream >> x;
    return x; 
}

#endif