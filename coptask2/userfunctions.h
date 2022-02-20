#include <stdlib.h>
#include <chrono>
#include <vector>
#include <math.h>
using namespace std;
//this function first does the matrix multiplication and then adds the bias vector to it
void sequential(int row1,int co1,int co2,float inputmatrix[1000][1000],float weightmatrix[1000][1000],float biasmatrix[1000][1000],float outputmatrix[1000][1000]){
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




