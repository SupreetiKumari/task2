#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <float.h>

using namespace std;

void fullyconnected(string fileinput,string fileweight,string filebias,string fileoutput){
ifstream file1 (fileinput);
    int noc1;
    int nor1;
    int i,j;
    string line;
    //Checks if the input file exists
    //If not found, displays an error message
    if(!file1.is_open()){
         cout<<"File containing inputmatrix cannot be opened."<<"\n";
         return;
    }
    getline(file1,line);
    //Stores no. of columns
    noc1=stoi(line);
    getline(file1,line);
    //Stores no. of rows
    nor1=stoi(line);
    float inputmatrix[nor1][noc1];
    //Storing elements from input file in inputmatrix
        for(j=0;j<noc1;j++){
        for(i=0;i<nor1;i++)
            {
                getline(file1,line);
                inputmatrix[i][j]=stof(line);
            }
        }
    file1.close();
    ifstream file2 (fileweight);
    int noc2;
    int nor2;
    if(!file2.is_open()){
         cout<<"File containing weightmatrix cannot be opened."<<"\n";
         return;
    }
    getline(file2,line);
    noc2=stoi(line);
    getline(file2,line);
    nor2=stoi(line);
    float weightmatrix[nor2][noc2];
     //Storing elements from inputfile in weightmatrix
        for(j=0;j<noc2;j++){
        for(i=0;i<nor2;i++){
           
                getline(file2,line);
                weightmatrix[i][j]=stof(line);
            }
        }
    file2.close();

    ifstream file3 (filebias);
    int noc3;
    int nor3;
    if(!file3.is_open()){
         cout<<"File containing biasmatrix cannot be opened."<<"\n";
         return;
    }
    getline(file3,line);
    noc3=stoi(line);
    getline(file3,line);
    nor3=stoi(line);
    float biasmatrix[nor3][noc3];
     //Storing elements from inputfile in biasmatrix
        for(j=0;j<noc3;j++){
        for(i=0;i<nor3;i++){
            
                getline(file3,line);
                biasmatrix[i][j]=stof(line);
            }
        }
    file3.close();
    //Initialising matrix values in outputmatrix to 0
    float outputmatrix[nor1][noc2];
    for(i=0;i<nor1;i++){
        for(j=0;j<noc2;j++){
            outputmatrix[i][j]=0;
        }
    }
    int k;
    //Multiplication of inputmatrix and weightmatrix
    for(i=0;i<nor1;i++){
        for(j=0;j<noc2;j++){
            for(k=0;k<noc1;k++){
                outputmatrix[i][j]+=inputmatrix[i][k]*weightmatrix[k][j];
            }
        }

    }
    //Addition of bias matrix and product of inputmatrix and weightmatrix
    for(i=0;i<nor1;i++){
        for(j=0;j<noc2;j++){
            outputmatrix[i][j]+=biasmatrix[i][j];}
    }
    //Displaying the output in output file in column major order
    ofstream file4(fileoutput);
    file4<<noc2<<"\n";
    file4<<nor1<<"\n";
    for(j=0;j<noc2;j++){
    for(i=0;i<nor1;i++){
        
            file4<<outputmatrix[i][j]<<"\n";
        }
    }
    file4.close();
    return;
}
