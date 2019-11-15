#ifndef __CSV__HEAD__
#define __CSV__HEAD__
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

#define SPACE ' '
// #include <boost/algorithm/string.hpp>
 
/*
 * A class to read data from a csv file.
 */
class CSV
{
private:

	char* fileName;
	char delimeter;
    std::vector<std::vector<std::string> > data;
 
public:
    CSV(char* filename, char delm = ',') :
			fileName(filename), delimeter(delm)
	{ }
 
	// Function to fetch data from a CSV File
    void fetch_data();
    void store_data(std::string file_name);
	std::vector<std::vector<std::string> > getData(){return data;}
    std::vector<std::string>& operator[](int i){return data[i];}
    std::vector<std::string>& keys(){return data[0];}
    int size()const{return data.size();}
};
 
/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
void CSV::fetch_data()
{
	std::ifstream file(fileName);
    
 
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (std::getline(file, line))
	{
		std::vector<std::string> row;
        std::string cell;
		// parse one line
        std::stringstream lineStream(line);
        while(std::getline(lineStream, cell, delimeter))
        {
            row.push_back(cell);
        }

		data.push_back(row);
	}
	// Close the File
	file.close();
}

// need to be completed !!!!!!!
void CSV::store_data(std::string file_name)
{
    int a = 1;
}

std::ostream& operator<< (std::ostream& stream , CSV& csv)
{
    for (size_t i = 0; i < csv.size(); i++)
    {
        for (size_t j = 0; j < csv[i].size(); j++)
        {
            stream<<csv[i][j]<<",";
        }
        stream<<std::endl;
    }
}
#endif