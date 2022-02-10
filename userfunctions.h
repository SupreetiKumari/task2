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
// this function is for calculating relu for every element of input matrix and return new matrix
vector<vector<float> > relu(vector<vector<float> > a)
{
    int R1 = a.size();
    int C1 = a[0].size();
    vector<vector<float> > rslt(R1, vector<float>(C1, 0.0));
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C1; j++)
        {
            rslt[i][j] = max((float)0.0, a[i][j]);
        }
    }
    return rslt;
}
//this function is for calculating tanh for every element of input matrix and return new matrix
vector<vector<float> > usertanh(vector<vector<float> > a)
{
    int R1 = a.size();
    int C1 = a[0].size();
    vector<vector<float> > rslt(R1, vector<float>(C1, 0.0));
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C1; j++)
        {
           
            rslt[i][j] = (float)((exp(2 * a[i][j]) - 1) / (exp(2 * a[i][j]) + 1));
        }
    }
    return rslt;
}
// this function is for creating a poolmax matrix
vector<vector<float> > poolmax(vector<vector<float> > a, int stride)
{
    int R1 = a.size();
    int C1 = a[0].size();
    int n = R1 / stride;
    int m = C1 / stride;
    vector<vector<float> > rslt(n, vector<float>(m, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float val = a[i * stride][j * stride];
            for (int ii = 0; ii < stride; ii++)
            {
                for (int jj = 0; jj < stride; jj++)
                {
                    val = max(val, a[i * stride + ii][j * stride + jj]);
                }
            }
            rslt[i][j] = val;
        }
    }
    return rslt;
}
// this function is for creating a poolaverage matrix
vector<vector<float> > poolaverage(vector<vector<float> > a, int stride)
{
    int R1 = a.size();
    int C1 = a[0].size();
    int n = R1 / stride;
    int m = C1 / stride;
    vector<vector<float> > rslt(n, vector<float>(m, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float val = 0.0;
            for (int ii = 0; ii < stride; ii++)
            {
                for (int jj = 0; jj < stride; jj++)
                {
                    val += a[i * stride + ii][j * stride + jj];
                }
            }
            rslt[i][j] = (float)(val / (stride * stride));
        }
    }
    return rslt;
}
// this function is used to calculate the sigmoid of the vector
vector<float> sigmoid(vector<float> a)
{
    int n = a.size();
    vector<float> result;
    for (int i = 0; i < n; i++)
    {
        
        float val = (float)((exp(a[i])) / (exp(a[i]) + 1));
        result.push_back(val);
    }
    return result;
}
// this function is used to calculate the softmax of the vector
vector<float> softmax(vector<float> a)
{
    int n = a.size();
    vector<float> result;
    float sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += exp(a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        float val = (float)((exp(a[i])) / sum);
        result.push_back(val);
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