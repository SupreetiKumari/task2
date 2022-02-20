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
//Initializing input and output matrices with maximum size.
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

//Multiplication function for pthread
void * multiply(void *param){
int a,b,c;
//Convert param of void * type to long int to calculate thread id(0 to 3)
long int id=(long int)param;
//Start row index for thread 
int start=(id*row1)/4;
//end row index for thread
int end= ((id+1)*row1)/4;
 for(a=start;a<end;a++){
        for(b=0;b<co2;b++){
	   //Setting initial value in outputmatrix to 0
           outputmatrix[a][b]=0;
            for(c=0;c<co1;c++){
                outputmatrix[a][b]+=inputmatrix[a][c]*weightmatrix[c][b];
            }
        }

    }
	return 0;

}
//Function to calculate time elapsed by a execution of a certain implementation
auto time(){
    return std::chrono::high_resolution_clock::now();
}


int main(int argc, char **argv)
{
        //Checks if second argument in command line is fully connected, returns an error message otherwise
        if (strcmp(argv[1], "fullyconnected") == 0 )
        
        {
            if (argc != 7)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt mkl/openblas/pthread outputmatrix.txt\n";
                return 0;
            }
	   //Extracts filenames for all 4 files from command line arguments
            std::string inputmatrixfile(argv[2]);
            string weightmatrixfile(argv[3]);
            string biasmatrixfile(argv[4]);
            string outputmatrixfile(argv[6]);
	    
	    //Checks if the given inputfile exists or not
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
	    //Pthread implementation
            if(strcmp(argv[5],"pthread")==0){
               //Column and row number for inputmatrix
                co1=column(inputmatrixfile);
                row1=row(inputmatrixfile);
   		//Inputmatrix is stored
   		filetomatrix(inputmatrixfile,inputmatrix);
                //Column and row number for weightmatrix
                co2=column(weightmatrixfile);
                row2=row(weightmatrixfile);
   		//Weightmatrix is stored
   		filetomatrix(weightmatrixfile,weightmatrix);
                //Column and row number for biasmatrix
                co3=column(biasmatrixfile);
                row3=row(biasmatrixfile);
   		//Biasmatrix is stored
   		filetomatrix(biasmatrixfile,biasmatrix);
                int i,j;
                //Start time for pthread implementation
                auto p_t1=time();
                //Creating threads(4)
                pthread_t threadid[4];
                for(i=0;i<4;i++){
                    pthread_create(&threadid[i],NULL,multiply,(void*)i);
                }
                //Joining threads
                for(j=0;j<4;j++){
                    pthread_join(threadid[j],NULL);
                }
               //End time for pthread implementation
               auto p_t2=time();
	       //Calculating total time elapsed
               auto p_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(p_t2 - p_t1);
               cout<<"Time taken by pthread: " <<p_timespan.count()<<"s\n";
		//Adding biasmatrix to outputmatrix
		for(i=0;i<row1;i++){
		for(j=0;j<co2;j++){
		    outputmatrix[i][j]+=biasmatrix[i][j];}
	    }
	     //Displaying outputmatrix in output file
	     matrixtofile(outputmatrixfile,outputmatrix,row1,co2);
            }
            
	    //OpenBlas implementation
            else if(strcmp(argv[5],"openblas")==0){
                //Column and row number for inputmatrix
                co1=column(inputmatrixfile);
                row1=row(inputmatrixfile);
                int i=0;
		//1D array inputmatrix1 is stored
                filetovector(inputmatrixfile,inputmatrix1); 
		//Column and row number for weightmatrix    
                co2=column(weightmatrixfile);
                row2=row(weightmatrixfile);
                int j=0; 
		//1D array weightmatrix is stored   
                filetovector(weightmatrixfile,weightmatrix1);  
		//Column and row number for biasmatrix
                co3=column(biasmatrixfile);
                row3=row(biasmatrixfile);
                int k=0;   
		//1D aaray biasmatrix is stored
                filetovector(biasmatrixfile,biasmatrix1);
		 //Start time for openblas implementation
                auto blas_t1=time();
		//Sets outputmatrix=inputmatrix*weightmatrix
                cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                row1, co2, co1, 1.0, inputmatrix1, row1, weightmatrix1, co1, 0.0, outputmatrix1, row1);
                int l;
                for(k=0;k<row1*co2;k++){                    
                 outputmatrix1[k]+=biasmatrix1[k];
                 }  
		 //End time for openblas implementation   
                auto blas_t2=time();
		//Calculating time elapsed for openblas implementation
               auto blas_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(blas_t2 - blas_t1);
               cout<<"Time taken by openblas: " <<blas_timespan.count()<<"s\n";
            
                vectortofile(outputmatrixfile,outputmatrix1,row1,co2);
                //Comparison with time taken for normal matrix multiplication
                auto seqt1=time();
             
                sequential(row1,co1,co2,inputmatrix,weightmatrix,biasmatrix,outputmatrix);
                auto seqt2=time();
     		auto seq_timespan=std::chrono::duration_cast<std::chrono::duration<double>>(seqt2 - seqt1);
               cout<<"Time taken by sequential: " <<seq_timespan.count()<<"s\n";
            }
            
            
            
        }
       //Displays an error for invalid command line argument
        else
        {
            cout << "Please give a valid command\n";
            cout<<"These are the available commands\n";
            cout<<"./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt mkl/openblas/pthread outputmatrix.txt\n";
           
                return 0;
        }
    
}
