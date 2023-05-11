#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> tac()
{
    vector<string> v;
    string str;
    ifstream fin;
    fin.open("TAC.txt");

    while (!fin.eof())
    {
        getline(fin, str);
        v.push_back(str);
        str = "";
    }

    fin.close();
    return v;
}

int main()
{
    vector<string> a = tac();

    for (auto &it : a)
    {
        cout << it << endl;
    }
}