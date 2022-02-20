#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <pthread.h>
#include <cblas.h>
#include "userfunctions.h"
#include "filecheck.h"
#include "IO.h"
#define MAX 1000000
int row1,co1,row2,co2,row3,co3;
float inputmatrix[1000][1000];
float weightmatrix[1000][1000];
float biasmatrix[1000][1000];
float outputmatrix[1000][1000];
float inputmatrix1[MAX];
float weightmatrix1[MAX];
float biasmatrix1[MAX];
float outputmatrix1[MAX];
using namespace std;

//Multiplication function
void * multi(void *arg){
 long int num=(long int)arg;
 int a,b,c;
int start=(num*row1)/4;
int end= ((num+1)*row1)/4;
 for(a=start;a<end;a++){
        for(b=0;b<co2;b++){
           outputmatrix[a][b]=0;
            for(c=0;c<co1;c++){
                outputmatrix[a][b]+=inputmatrix[a][c]*weightmatrix[c][b];
            }
        }

    }

}
auto time(){
    return std::chrono::high_resolution_clock::now();
}


int main(int argc, char **argv)
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
            if(strcmp(argv[5],"pthread")==0){
               
                co1=column(inputmatrixfile);
                row1=row(inputmatrixfile);
   		
   		
   		 filetomatrix(inputmatrixfile,inputmatrix);
             
                 co2=column(weightmatrixfile);
                row2=row(weightmatrixfile);
   		
   		
   		 filetomatrix(weightmatrixfile,weightmatrix);
             
                 co3=column(biasmatrixfile);
                row3=row(biasmatrixfile);
   		
   		 filetomatrix(biasmatrixfile,biasmatrix);
                int i,j;
                
                auto p_t1=time();
                
                pthread_t tid[4];
                for(i=0;i<4;i++){
                    pthread_create(&tid[i],NULL,multi,(void*)&i);
                }
                for(j=0;j<4;j++){
                    pthread_join(tid[j],NULL);
                }
                
                
                
                 auto p_t2=time();
               auto p_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(p_t2 - p_t1);
               cout<<"Time taken by pthread: " <<p_timespan.count()<<"s\n";
		for(i=0;i<row1;i++){
		for(j=0;j<co2;j++){
		    outputmatrix[i][j]+=biasmatrix[i][j];}
	    }
	    
	     matrixtofile(outputmatrixfile,outputmatrix,row1,co2);
            }
            
            else if(strcmp(argv[5],"openblas")==0){
              
                 co1=column(inputmatrixfile);
                row1=row(inputmatrixfile);
                int i=0;             
                 filetovector(inputmatrixfile,inputmatrix1);             
                 co2=column(weightmatrixfile);
                row2=row(weightmatrixfile);
                int j=0;          
                 filetovector(weightmatrixfile,weightmatrix1);            
                 co3=column(biasmatrixfile);
                row3=row(biasmatrixfile);
                int k=0;            
                 filetovector(biasmatrixfile,biasmatrix1);
                auto mkl_t1=time();
                cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                row1, co2, co1, 1.0, inputmatrix1, row1, weightmatrix1, co1, 0.0, outputmatrix1, row1);
                int l;
                for(k=0;k<row1*co2;k++){                    
                    outputmatrix1[k]+=biasmatrix1[k];
                                    }                               
                 auto mkl_t2=time();
               auto mkl_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(mkl_t2 - mkl_t1);
               cout<<"Time taken by openblas: " <<mkl_timespan.count()<<"s\n";
            
                vectortofile(outputmatrixfile,outputmatrix1,row1,co2);
                
                auto seqt1=time();
             
                sequential(row1,co1,co2,inputmatrix,weightmatrix,biasmatrix,outputmatrix);
                auto seqt2=time();
      auto seq_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(seqt2 - seqt1);
               cout<<"Time taken by sequential: " <<seq_timespan.count()<<"s\n";
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

