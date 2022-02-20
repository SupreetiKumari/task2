#include <vector>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;
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

void vectortofile(string &filename, float outputvector,int r,int c){
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
