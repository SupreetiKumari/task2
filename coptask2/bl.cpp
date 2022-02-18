#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <cblas.h>

using namespace std;

/*auto time(){
    return std::chrono::high_resolution_clock::now();
}*/

bool checkinputfile(string &filename)
{
    ifstream inputfile;
    inputfile.open(filename);
    if(!inputfile.is_open())
    {
        inputfile.close();
        return 0;
    }
    else
    {
        inputfile.close();
        return 1;
    }
}

int main(int argc, char **argv)
{
    double cons1=1.0,cons2=0.0;
    double *A,*B,*C;
    
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
            if(strcmp(argv[5],"openblas")==0){
                ifstream inputfile1;
                inputfile1.open(inputmatrixfile);
                int co1,row1;
                inputfile1>>co1;
                inputfile1>>row1;
                double inputmatrix[co1*row1];
                int i=0;
                double x;
                while (inputfile1>>x)
                 {
                 inputmatrix[i++]=x;
                 }
                 inputfile1.close();
                 ifstream inputfile2;
                inputfile2.open(weightmatrixfile);
                int co2,row2;
                inputfile2>>co2;
                inputfile2>>row2;
                double weightmatrix[co2*row2];
                int j=0;
                double y;
                while (inputfile2>>y)
                 {
                 weightmatrix[j++]=y;
                 }
                 inputfile2.close();
                 ifstream inputfile3;
                inputfile1.open(biasmatrixfile);
                int co3,row3;
                inputfile3>>co3;
                inputfile3>>row3;
                double biasmatrix[co3*row3];
                int k=0;
                double z;
                while (inputfile3>>z)
                 {
                 biasmatrix[k++]=z;
                 }
                 inputfile3.close();
                
                double outputmatrix[co2*row1];
                
              
                
                //auto mkl_t1=time();
                cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                row1, co2, co1, 1.0, inputmatrix, row1, weightmatrix, co1, 0.0, outputmatrix, row1);
                int l;
                for(k=0;k<row1*co2;k++){
                    
                    outputmatrix[k]+=biasmatrix[k];
                    
                }
                
               // auto mkl_t2=time();
               // auto mkl_timespan=duration_cast<duration<double>>(mkl_t2 - mkl_t1);
               // cout<<"Time taken by MKL: " <<mkl_timespan.count()<<"s\n";
               ofstream fout(outputmatrixfile);
               fout << co2 << "\n";
               fout << row1 << "\n";
               for (int i = 0; i < row1*co2; i++)
               {

              fout << outputmatrix[i] << "\n";
             }
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
