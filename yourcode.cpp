#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include "userfunctions.h"
#include "IOuseful.h"
#include "filecheck.h"
using namespace std;

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[1], "fullyconnected") == 0 )
        {
            if (argc != 6)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[2]);
            string weightmatrixfile(argv[3]);
            string biasmatrixfile(argv[4]);
            string outputmatrixfile(argv[5]);

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
            

            vector<vector<float> > inputmatrix = filetovector(inputmatrixfile);
            vector<vector<float> > weightmatrix = filetovector(weightmatrixfile);
            vector<vector<float> > biasmatrix = filetovector(biasmatrixfile);
            vector<vector<float> > outputmatrix = fullyconnected(inputmatrix, weightmatrix, biasmatrix);
            vectortofile(outputmatrixfile, outputmatrix);
        }
       
        else
        {
            cout << "Please give a valid command\n";
            cout<<"These are the available commands\n";
            cout<<"./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt\n";
           
                return 0;
        }
    }
}
