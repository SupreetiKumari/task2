#include <stdlib.h>
#include <chrono>
#include <vector>
#include <math.h>
using namespace std;
//this function first does the matrix multiplication and then add the bias vector to it
vector<vector<float> > fullyconnected(vector<vector<float> > a, vector<vector<float> > b, vector<vector<float> > c)
{
    int R1 = a.size();
    int C1 = a[0].size();
    int R2 = b.size();
    int C2 = b[0].size();
    vector<vector<float> > result(R1, vector<float>(C2, 0.0));
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            result[i][j] = 0.0;
            for (int k = 0; k < R2; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            result[i][j] += c[i][j];
        }
    }
    return result;
}

// this function is to check if a string is a number or not
bool isanumber(const string& stride)
{
    string::const_iterator it = stride.begin();
    while (it != stride.end() && std::isdigit(*it)) ++it;
    return !stride.empty() && it == stride.end();
}

auto time(){
    return std::chrono::high_resolution_clock::now();
}
