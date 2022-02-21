#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
int sumcount=0;
using namespace std;
float mean(string &filename){

	ifstream inputfile;
        inputfile.open(filename);
        float sum=0.0;
   	float x;
       while(inputfile>>x)
        {
         sum+=x;
         sumcount+=1;
        }
        
   	inputfile.close();
   	return sum/sumcount;
}

float sd(string &filename,float mean, int num){
	ifstream inputfile;
        inputfile.open(filename);
        float sdsum=0.0;
   	float y;
       while(inputfile>>y)
        {
         sdsum+=(y-mean)*(y-mean);
         
        }
        inputfile.close();
        sdsum/=num;
        return sqrt(sdsum);
        

}
int main(){
 cout<<"Enter filename:"<<"\n";
 string s;
 cin>>s;
 cout<<mean(s)<<"\n";
 cout<<sd(s,mean(s),sumcount)<<"\n";
 return 0;
}
