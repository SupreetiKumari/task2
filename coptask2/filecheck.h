#include <vector>
#include <math.h>
#include <fstream>
#include<string>
using namespace std;
// this function checks if the input file is a valid one or not
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
