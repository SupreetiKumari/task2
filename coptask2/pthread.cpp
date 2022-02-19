#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <pthread.h>
int row1,co1,row2,co2,row3,co3;
float inputmatrix[1000][1000];
float weightmatrix[1000][1000];
float biasmatrix[1000][1000];
float outputmatrix[1000][1000];
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
                ifstream inputfile1;
                inputfile1.open(inputmatrixfile);
                int i,j;
                inputfile1>>co1;
                inputfile1>>row1;
   		 float x;
       	for(j=0;j<co1;j++){
        	for(i=0;i<row1;i++)
           	 {
                inputfile1>>x;
                inputmatrix[i][j]=x;
          	  }
        	}
   		 inputfile1.close();
                 ifstream inputfile2;
                inputfile2.open(weightmatrixfile);
                
                inputfile2>>co2;
                inputfile2>>row2;
   		 float y;
       	for(j=0;j<co2;j++){
        	for(i=0;i<row2;i++)
           	 {
                inputfile2>>y;
                weightmatrix[i][j]=y;
          	  }
        	}
   		 inputfile2.close();
                 ifstream inputfile3;
                inputfile1.open(biasmatrixfile);
               
                inputfile3>>co3;
                inputfile3>>row3;
   		 float z;
       	for(j=0;j<co3;j++){
        	for(i=0;i<row3;i++)
           	 {
                inputfile3>>z;
                biasmatrix[i][j]=z;
          	  }
        	}
   		 inputfile3.close();
                
                
                //auto mkl_t1=time();
                
                pthread_t tid[4];
                for(i=0;i<4;i++){
                    pthread_create(&tid[i],NULL,multi,(void*)i);
                }
                for(j=0;j<4;j++){
                    pthread_join(tid[j],NULL);
                }
                
                
                
                //output
                
               // auto mkl_t2=time();
               // auto mkl_timespan=duration_cast<duration<double>>(mkl_t2 - mkl_t1);
               // cout<<"Time taken by MKL: " <<mkl_timespan.count()<<"s\n";
		for(i=0;i<row1;i++){
		for(j=0;j<co2;j++){
		    outputmatrix[i][j]+=biasmatrix[i][j];}
	    }
	    //Displaying the output in output file in column major order
	    ofstream inputfile4(outputmatrixfile);
	    inputfile4<<co2<<"\n";
	    inputfile4<<row1<<"\n";
	    for(j=0;j<co2;j++){
	    for(i=0;i<row1;i++){
		
		    inputfile4<<outputmatrix[i][j]<<"\n";
		}
	    }
	    inputfile4.close();
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

