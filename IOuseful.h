#include <vector>
#include <math.h>
using namespace std;
// this function is used to convert the input file to a 2d vector
vector<vector<float> > filetovector(string &filename)
{
    int rows, column;
    ifstream inputfile;
    inputfile.open(filename);
    string ro, co, line;
    getline(inputfile, co);
    column = stoi(co);
    getline(inputfile, ro);
    rows = stoi(ro);
    vector<vector<float> > vec(rows, vector<float>(column, 0.0));
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            getline(inputfile, line);
            float val = stof(line);
            vec[j][i] = val;
        }
    }
    return vec;
}
// this function is used to convert the input file to a 1d vector
vector<float> fileto1Dvector(string &filename)
{
    int n;
    ifstream inputfile;
    inputfile.open(filename);
    string co, line;
    getline(inputfile, co);
    n = stoi(co);
    vector<float> vec;
    while (getline(inputfile, line))
    {
        float val = stof(line);
        vec.push_back(val);
    }
    return vec;
}
// this fucntion is used to write a 2d vector on the file passed
void vectortofile(string &filename, vector<vector<float> > vec)
{
    int row = vec.size();
    int column = vec[0].size();
    ofstream fout;
    string line;
    fout.open(filename);
    fout << column << "\n";
    fout << row << "\n";
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            fout << vec[j][i] << "\n";
        }
    }
}
// this fucntion is used to write a 1d vector on the file passed
void vector1Dtofile(string &filename, vector<float> vec)
{
    int n = vec.size();
    ofstream fout;
    string line;
    fout.open(filename);
    fout << n << "\n";
    for (int i = 0; i < n; i++)
    {

        fout << vec[i] << "\n";
    }
}