#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include "mkl.h"
#include "userfunctions.h"
#include "IOuseful.h"
#include "filecheck.h"
using namespace std;

/*auto time(){
    return std::chrono::high_resolution_clock::now();
}*/

int main(int argc, char **argv)
{
    double cons1=1.0,cons2=0.0;
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[1], "fullyconnected") == 0 )
        {
            if (argc != 7)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt mkl/openblas/pthread outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[2]);
            string weightmatrixfile(argv[3]);
            string biasmatrixfile(argv[4]);
            string outputmatrixfile(argv[6]);

            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            if (checkinputfile(weightmatrixfile) == 0)
            {
                cerr << "The weightmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            if (checkinputfile(biasmatrixfile) == 0)
            {
                cerr << "The biasmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            if(strcmp(argv[5],"mkl")==0){
                double* inputmatrix = filetovector(inputmatrixfile);
                double* weightmatrix = filetovector(weightmatrixfile);
                double* biasmatrix = filetovector(biasmatrixfile);
                double* outputmatrix;
                int r1=row(inputmatrixfile);
                int c1=column(inputmatrixfile);
                int c2=column(weightmatrixfile);
                
                //auto mkl_t1=time();
                cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                r1, c2, c1, cons1, inputmatrix, c1, weightmatrix, c2, cons2, outputmatrix, c2);
                int k,l;
                for(k=0;k<r1*c2;k++){
                    
                    outputmatrix[k]+=biasmatrix[k];
                    
                }
                
               // auto mkl_t2=time();
               // auto mkl_timespan=duration_cast<duration<double>>(mkl_t2 - mkl_t1);
               // cout<<"Time taken by MKL: " <<mkl_timespan.count()<<"s\n";
                vectortofile(outputmatrixfile, outputmatrix,r1,c2);
                return 0;
            }
            
        }
       
        else
        {
            cout << "Please give a valid command\n";
            cout<<"These are the available commands\n";
            cout<<"./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt mkl/openblas/pthread outputmatrix.txt\n";
           
                return 0;
        }
    }
}
