#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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

void printVector(vector<string> vec)
{
    for (auto &it1 : vec)
    {
        cout << it1 << ' ';
    }
    cout << endl;
}

void printFirstWord(vector<string> vec)
{
    int count = 0;
    for (auto &it1 : vec)
    {
        if (count < 1)
        {
            cout << it1;
            count++;
        }
    }
    cout << endl;
}

vector<string> tokenize(string s)
{
    vector<string> tokens;
    stringstream line(s);
    string word;

    while (getline(line, word, ' '))
    {
        tokens.push_back(word);
    }

    return tokens;
}

vector<string> output(vector<string> line)
{

    vector<string> quad;
    quad.push_back("out");
    string s = line[1];

    if (int(s[0]) == 34)
        quad.push_back(s.substr(1, s.length() - 2));
    else
        quad.push_back(s);

    return quad;
}

vector<string> input(vector<string> line)
{
    vector<string> quad;
    quad.push_back(line[0]);
    quad.push_back(line[1]);
    // cout << line[0] << " " << line[1] << endl;

    return quad;
}

vector<string> gotoStatement(vector<string> line)
{
    vector<string> quad;
    quad.push_back(line[0]);
    quad.push_back(line[1]);
    // cout << line[0] << " " << line[1] << endl;

    return quad;
}

vector<string> variable(vector<string> line)
{
    vector<string> quad;

    if (line.size() == 5)
    {
        // t1 = x + y
        quad.push_back(line[3]);
        quad.push_back(line[2]);
        quad.push_back(line[4]);
        quad.push_back(line[0]);

        // cout << line[3] << " " << line[2] << " " << line[4] << " " << line[0] << endl;
    }
    else if (line.size() == 3)
    {
        // z = t1
        quad.push_back("mov");
        quad.push_back(line[0]);
        quad.push_back(line[2]);
        // cout << "mov " << line[0] << " " << line[2] << endl;
    }

    return quad;
}

vector<string> ifStatement(vector<string> line)
{

    vector<string> quad;
    quad.push_back(line[2]);
    quad.push_back(line[1]);
    quad.push_back(line[3]);
    quad.push_back(line[5]);

    // cout << line[2] << " " << line[1] << " " << line[3] << " " << line[5] << endl;

    return quad;
}

vector<string> ret(vector<string> line)
{
    vector<string> quad;
    quad.push_back(line[0]);
    quad.push_back(line[1]);
    // cout << line[0] << " " << line[1] << endl;

    return quad;
}

vector<vector<string>> convertToQuad(vector<vector<string>> arr)
{
    vector<vector<string>> quad;

    vector<string> v;
    vector<string> v1;

    for (auto &it : arr)
    {

        // cout << "pehla " << it[0] << endl;
        if (it[0] == "out")
        {
            v1 = output(it);
            quad.push_back(v1);
            printVector(v1);
        }
        else if (it[0] == "in")
        {
            v1 = input(it);
            quad.push_back(v1);
            printVector(v1);
        }
        else if (it[0] == "goto")
        {
            v1 = gotoStatement(it);
            quad.push_back(v1);
            printVector(v1);
        }
        else if (it[0] == "if")
        {
            v1 = ifStatement(it);
            quad.push_back(v1);
            printVector(v1);
        }
        else if (it[0] == "ret")
        {
            v1 = ret(it);
            quad.push_back(v1);
            printVector(v1);
        }
        else
        {
            v1 = variable(it);
            quad.push_back(v1);
            printVector(v1);
        }

        v.clear();
        v1.clear();
    }

    return quad;
}

int main()
{
    vector<string> a = tac();

    for (auto &it : a)
    {
        cout << it << endl;
    }

    cout << endl
         << endl
         << endl;

    vector<vector<string>> v;
    vector<string> s;
    for (auto &it : a)
    {
        s = tokenize(it);
        // printVector(s);
        // cout << "----------" << endl;
        v.push_back(s);
        s.clear();
    }

    vector<vector<string>> vc = convertToQuad(v);

    // for (auto &it : a)
    // {
    //     for (auto &it1 : it)
    //     {
    //         cout << it1;
    //     }
    //     cout << endl;
    // }
}