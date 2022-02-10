#include <vector>
#include <math.h>
using namespace std;
// this function is used to convert the input file to a 1d vector

int row(string &filename)
{
int n;
    ifstream inputfile;
    inputfile.open(filename);
    string co, line;
    getline(inputfile, co);
string row;
getline(inputfile, row);
    n = stoi(row);
return n;}

int column(string &filename)
{
int n;
    ifstream inputfile;
    inputfile.open(filename);
    string co, line;
    getline(inputfile, co);
string row;
getline(inputfile, row);
    n = stoi(co);
return n;}

double* filetovector(string &filename)
{
    int n;
    ifstream inputfile;
    inputfile.open(filename);
    string co, line;
    getline(inputfile, co);
    n = stoi(co);
    string row;
    getline(inputfile, row);
    vector<double> vec;
    while (getline(inputfile, line))
    {
        double val = stod(line);
        vec.push_back(val);
    }
    double* a=&vec[0];
    return a;
}

// this function is used to write a 1d vector on the file passed
void vectortofile(string &filename, double* vec, int r1, int c2)
{

    ofstream fout;
    string line;
    fout.open(filename);
    fout << c2 << "\n";
    fout << r1 << "\n";
    for (int i = 0; i < r1*c2; i++)
    {

        fout << *(vec + i) << "\n";
    }
}
