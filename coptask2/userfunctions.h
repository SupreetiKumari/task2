#include <stdlib.h>
#include <chrono>
#include <vector>
#include <math.h>
using namespace std;
//this function first does the matrix multiplication and then add the bias vector to it

void sequential(int row1,int co1,int co2,float inputmatrix[row1][co1],float weightmatrix[co1][co2],float biasmatrix[row1][co2],float outputmatrix[row1][co2]){
int i,j,k;
	for(i=0;i<row1;i++){
        for(j=0;j<co2;j++){
            for(k=0;k<co1;k++){
                outputmatrix[i][j]+=inputmatrix[i][k]*weightmatrix[k][j];
            }
        }

    }
    //Addition of bias matrix and product of inputmatrix and weightmatrix
    for(i=0;i<row1;i++){
        for(j=0;j<co2;j++){
            outputmatrix[i][j]+=biasmatrix[i][j];}
    }
}

// this function is to check if a string is a number or not
bool isanumber(const string& stride)
{
    string::const_iterator it = stride.begin();
    while (it != stride.end() && std::isdigit(*it)) ++it;
    return !stride.empty() && it == stride.end();
}
