#include <vector>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;

//Writes the outputmatrix to output file in column major order
void matrixtofile(string &filename, float outputmatrix[1000][1000],int r,int c){
 int i,j;
 ofstream file(filename);
 file<<c<<"\n";
 file<<r<<"\n";
 for(j=0;j<c;j++){
    for(i=0;i<r;i++){
        
            file<<outputmatrix[i][j]<<"\n";
        }
    }
    file.close();
    return;
}

//Writes outputvector to output file
void vectortofile(string &filename,float outputvector[1000],int r,int c){
 int i;
 ofstream file(filename);
 file<<c<<"\n";
 file<<r<<"\n";
    for(i=0;i<r*c;i++){
        
            file<<outputvector[i]<<"\n";
        }
    
    file.close();
    return;
}

//Takes input from file in the form of 2D matrix
void filetomatrix(string &filename, float inputmatrix[1000][1000]){
	ifstream inputfile;
        inputfile.open(filename);
        int i,j,row,co;
        inputfile>>co;
        inputfile>>row;
   	float x;
       for(j=0;j<co;j++){
        for(i=0;i<row;i++)
        {
        inputfile>>x;
         inputmatrix[i][j]=x;
        }
        }
   	inputfile.close();

}

//Takes input from file in the form of a 1D array
void filetovector(string &filename, float inputmatrix[1000]){
	ifstream inputfile;
                inputfile.open(filename);
                int co1,row1;
                inputfile>>co1;
                inputfile>>row1;
                int i=0;
                float x;
                while (inputfile>>x)
                 {
                 inputmatrix[i++]=x;
                 }
                 inputfile.close();
}

//Return no. of rows 
int row(string &filename){
		ifstream inputfile;
                inputfile.open(filename);
                int c,r;
                inputfile>>c;
                inputfile>>r;
                return r;
}

//Returns no. of columns
int column(string &filename){
ifstream inputfile;
                inputfile.open(filename);
                int c,r;
                inputfile>>c;
                inputfile>>r;
                return c;
}




