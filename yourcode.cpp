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
        else if (strcmp(argv[1], "activation") == 0 && strcmp(argv[2], "relu") == 0 )
        {
            if (argc != 5)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out activation relu inputmatrix.txt outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
            string outputmatrixfile(argv[4]);
            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            
            vector<vector<float> > inputmatrix = filetovector(inputmatrixfile);
            vector<vector<float> > outputmatrix = relu(inputmatrix);
            vectortofile(outputmatrixfile, outputmatrix);
        }
        else if (strcmp(argv[1], "activation") == 0 && strcmp(argv[2], "tanh") == 0)
        {
            if (argc != 5)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
            string outputmatrixfile(argv[4]);
            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
           
            vector<vector<float> > inputmatrix = filetovector(inputmatrixfile);
            vector<vector<float> > outputmatrix = usertanh(inputmatrix);
            vectortofile(outputmatrixfile, outputmatrix);
        }
        else if (strcmp(argv[1], "pooling") == 0 && strcmp(argv[2], "max") == 0 )
        {
            if (argc != 6)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
             if(isanumber(argv[4])==0) 
            {
                cout<<"The stride should be a number.\nPlease try again.\n";
                return 0;
            }
            int stride = stoi(argv[4]);
            string outputmatrixfile(argv[5]);
            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            
            vector<vector<float> > inputmatrix = filetovector(inputmatrixfile);
            vector<vector<float> > outputmatrix = poolmax(inputmatrix, stride);
            vectortofile(outputmatrixfile, outputmatrix);
        }
        else if (strcmp(argv[1], "pooling") == 0 && strcmp(argv[2], "average") == 0 )
        {

            if (argc != 6)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
            if(isanumber(argv[4])==0) 
            {
                cout<<"The stride should be a number.\nPlease try again.\n";
                return 0;
            }
            int stride = stoi(argv[4]);
            string outputmatrixfile(argv[5]);

            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
          
            vector<vector<float> > inputmatrix = filetovector(inputmatrixfile);
            vector<vector<float> > outputmatrix = poolaverage(inputmatrix, stride);
            vectortofile(outputmatrixfile, outputmatrix);
        }
        else if (strcmp(argv[1], "probability") == 0 && strcmp(argv[2], "softmax") == 0 )
        {
            if (argc != 5)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out probability softmax inputvector.txt outputvector.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
            string outputmatrixfile(argv[4]);
            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
           
            vector<float> inputmatrix = fileto1Dvector(inputmatrixfile);
            vector<float> outputmatrix = softmax(inputmatrix);
            vector1Dtofile(outputmatrixfile, outputmatrix);
        }
        else if (strcmp(argv[1], "probability") == 0 && strcmp(argv[2], "sigmoid") == 0 )
        {
            if (argc != 5)
            {
                cout << "Unfortunately you have put a wrong command."
                     << "\n";
                cout << "The correct command is ./yourcode.out probability sigmoid inputvector.txt outputvector.txt\n";
                return 0;
            }
            std::string inputmatrixfile(argv[3]);
            string outputmatrixfile(argv[4]);
            if (checkinputfile(inputmatrixfile) == 0)
            {
                cerr << "The inputmatrixfile file unfortunately could not be opened. Please give a valid file"
                     << "\n";
                return 0;
            }
            
            vector<float> inputmatrix = fileto1Dvector(inputmatrixfile);
            vector<float> outputmatrix = sigmoid(inputmatrix);
            vector1Dtofile(outputmatrixfile, outputmatrix);
        }
        else
        {
            cout << "Please give a valid command\n";
            cout<<"These are the available commands\n";
            cout<<"./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt\n";
            cout<<"./yourcode.out activation relu inputmatrix.txt outputmatrix.txt\n";
            cout<<"./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt\n";
            cout<<"./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt\n";
            cout<<"./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt\n";
            cout<<"./yourcode.out probability softmax inputvector.txt outputvector.txt\n";
            cout<<"./yourcode.out probability sigmoid inputvector.txt outputvector.txt\n";
                return 0;
        }
    }
}
