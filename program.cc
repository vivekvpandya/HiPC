#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>

std::vector< std::vector<double> > dataPointsVector;
std::vector< std::vector<double> > sample;
std::vector< std::vector<double> > medoids;
std::vector<double> v;


double manhattanSegDis(std::vector<double> *x1 , std::vector<double> *x2);
std::vector< std::vector<double> > randomInitialSample(std::vector< std::vector<double> > *dataPointsVector, int size);
inline double closed_interval_rand(double x0, double x1)
{
    return x0 + (x1 - x0) * rand() / ((double) RAND_MAX);
}

std::vector< std::vector<double> > greedySample(std::vector< std::vector<double> > *dataPointsVector, int size);


int main()
{   std::cout.precision(15);
    int dataPoints = 0;
    int dimensions = 0;
    int totalData = 0;
    int n_cluster = 0;
    int const_a = 50;
    int const_b = 2;
    
    //std::ifstream  data("smallerds.csv");
    std::ifstream  data("/Users/Mr.Pandya/Documents/HiPC/Program/Program/bigData.csv");
    
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
    // Tesing input
    // std::vector<double> test1 = dataPointsVector.at(9);
    //std::vector<double> test2 = dataPointsVector.at(21);
    //std::cout << std::fixed << manhattanSegDis(&test1, &test2);
    // for( double data: test){
    
    //     std::cout << std::fixed << data << " ";
    // }
    std::cout << "Enter initial number of medoids: ";
    std::cin >> n_cluster;
    sample = randomInitialSample(&dataPointsVector,n_cluster*const_a);
    
    
    
    
    //  std::vector<double> test = sample.at(n_cluster*const_a );
    
    // for( double data: test){
    
    //       std::cout << std::fixed << data << " ";
    //  }
    medoids = greedySample(&sample,n_cluster*const_b);
    std::vector<double> medoid1 = medoids.at(n_cluster*const_b - 1);
    for(double val : medoid1){
        std::cout << std::fixed <<val ;
    }
    
    
    
}

double manhattanSegDis(std::vector<double> *x1 , std::vector<double> *x2){
    
    std::vector<double> *X1 = x1;
    std::vector<double> *X2 = x2;
    
    int n_dimensions = X1->size();
    if (X1->size() != X2->size()){
        return -1.0;
    }
    else{
        double totalDis = 0.0;
        std::vector<double>::iterator itx1;
        std::vector<double>::iterator itx2;
        for(itx1=X1->begin(), itx2 = X2->begin() ; itx1 < X1->end(); itx1++, itx2++){
            totalDis += std::abs(*itx1 - *itx2);
        }
        return totalDis / n_dimensions;
        
    }
    
    
    
    
    
}

std::vector< std::vector<double> > randomInitialSample(std::vector< std::vector<double> > *dataPointsVector, int size){
    std::vector< std::vector<double> > *inputDataPoints = dataPointsVector;
    std::vector< std::vector<double> > outputSample;
    int sizeOfDataPoints = inputDataPoints->size();
    if(size < sizeOfDataPoints){
        
        int upperBoundIndex = sizeOfDataPoints - size - 1 ;
        int r = rand() % upperBoundIndex; // rand is not random
        std::cout << std::fixed << r <<'\n';
        int startIndex =  r;
        //std::cout << startIndex << " Start Index" << '\n';
        for(int i = 0 ; i<size ;i++)
            outputSample.push_back(inputDataPoints->at(startIndex + i));
        
        
    }
    else{
        // empty outputSample will be returned .
        //std::cout << "Size is greator than number of dataPoints";
    }
    
    return outputSample;
    
    
}

std::vector< std::vector<double> > greedySample(std::vector< std::vector<double> > *dataPointsVector, int size){
    std::vector< std::vector<double> > *inputDataPoints = dataPointsVector;
    std::vector<double> distance;
    std::vector< std::vector<double> > medoids;
    int random = rand() % inputDataPoints->size();
    std::vector<double> m = inputDataPoints->at(random);
    medoids.push_back(m);
    inputDataPoints->erase(inputDataPoints->begin() + random);
    
    for(std::vector<double> s : *inputDataPoints ){
        distance.push_back(manhattanSegDis(&s,&m));
    }
    int maxEleIndex;
    for (int i = 1 ; i < size; i++ ){
         maxEleIndex = std::distance( distance.begin(), std::max_element(distance.begin(), distance.end()));
        std::cout << " Farthest element: " << maxEleIndex << '\n';
        m = inputDataPoints->at(maxEleIndex);
        medoids.push_back(m);
        inputDataPoints->erase(inputDataPoints->begin() + maxEleIndex);
        distance.erase(distance.begin() + maxEleIndex);
        std::vector< std::vector<double> >::iterator s_ite;
        std::vector<double>::iterator d_ite;
        int k = 0;
        double newDist;
        for( s_ite=inputDataPoints->begin(), d_ite = distance.begin() ; s_ite < inputDataPoints->end(); s_ite++, d_ite++, k++ ){
            newDist = manhattanSegDis(&*s_ite,&m); // This gives output 0
            if(distance.at(k) > newDist){
                distance.at(k) = newDist;
            }
        }
        
        
    }
    
    return medoids;
    
}
