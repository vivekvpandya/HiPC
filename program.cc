#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::vector< std::vector<double> > dataPointsVector;
std::vector<double> v;

int main()
{   int dataPoints = 0;
    int dimensions = 0;
    int totalData = 0;
    //std::ifstream  data("smallerds.csv");
    std::ifstream  data("bigData.csv");
    // some thing wrong here I am not able to get first line 
    std::string line;
    while(std::getline(data,line))
    {   dataPoints++; 
        v.clear();
        std::stringstream  lineStream(line);
        std::string        cell;

        while(std::getline(lineStream,cell,','))
        {  
            //std::cout << cell;
            v.push_back(std::stod(cell));
            totalData++;
        }
        dataPointsVector.push_back(v);
    }
    dimensions = totalData / dataPoints; // Here we have fixed number of dimension for all data points
    std::cout << "Total dataPoints : " << dataPoints << '\n';
    std::cout << "Total dimensions : " << dimensions << '\n';
    std::vector<double> test = dataPointsVector.at(1);
    for( double data: test){

        std::cout << data << " ";
    }
}