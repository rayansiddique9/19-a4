#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
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
    if (s.substr(0, 3) == "out")
    {

        tokens.push_back(s.substr(0, 3));
        tokens.push_back(s.substr(4,s.length() - 4));
    }

    else
    {
        while (getline(line, word, ' '))
        {
             tokens.push_back(word);
        }
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
            // v1 = output(it);
            quad.push_back(it);
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

bool isNumber(string var)
{
    for (char c : var)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// vector<string> tokenizeSTLine(string s)
// {
//     vector<string> tokens;
//     stringstream line(s);
//     string word;

//     string delimiter = "-----";

//     size_t pos = 0;
//     string token;
//     while ((pos = s.find(delimiter)) != string::npos)
//     {
//         token = s.substr(0, pos);
//         tokens.push_back(token);
//         s.erase(0, pos + delimiter.length());
//     }
//     tokens.push_back(s);
// }

vector<vector<string>> getMarkaziLineNo()
{
    // cout << " in function";
    ifstream fin;
    fin.open("symbol_table.txt");
    string str;
    vector<string> x;
    vector<vector<string>> res;

    for (int i = 1; !fin.eof(); i++)
    {
        if (i <= 5)
        {
            // fin.ignore('\n');
            getline(fin, str);
            str = "";
            // cout << "i = " << i << endl;
        }
        else
        {
            str = "";
            // cout << "agya i = " << i << endl;
            getline(fin, str);
            // cout << str << endl;
            x = tokenize(str);
            // printVector(x);
            if (x[1] == "markazi")
            {
                str = "";
                while (!fin.eof())
                {
                    getline(fin, str);
                    x = tokenize(str);
                    res.push_back(x);
                    str = "";
                    x.empty();
                }
                return res;
            }
            x.empty();
        }
    }
    fin.close();

    return res;
}

// int lookSymbolTable(string s, bool &check)
// {
//     ifstream fin;
//     fin.open("symbol_table.txt");
//     while (!fin.eof())
//     {
//     }
// }

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
        v.push_back(s);
        s.clear();
    }

    cout << "printing quad" << endl
         << endl;
    vector<vector<string>> vc = convertToQuad(v);

    // var ->symbol -> ds.push and map[key, value] = varname, ds[indexof(varname)]
    // number -> ds.push

    vector<int> ds;
    bool varExists = true;
    unordered_map<string, int> m;

    cout << endl
         << endl;
    cout << "------------------------" << endl;
    vector<vector<string>> r = getMarkaziLineNo();

    for (auto &it1 : r)
    {
        printVector(it1);
        ds.push_back(stoi(it1[3]));
        m[it1[1]] = ds.size() - 1;
    }

    // for (auto it = m.begin(); it != m.end(); it++)
    // {
    //     cout << it->first << " " << m[it->first] << " " << ds[m[it->first]] << endl;
    // }

    for (auto &it : vc)
    {
        for (auto &it1 : it)
        {

            if (isNumber(it1))
            {
                ds.push_back(stoi(it1));
                it1 = to_string(ds.size() - 1);
            }
            else if (it1 != "mov" && it1 != "ret" && it1 != "goto" && it1 != "EQ" && it1 != "==" && it1 != "out" && it1 != "in" && it1 != "GT" && it1 != "LT" && it1 != "GE" && it1 != "LE" && it1 != "%" && it1 != "/" && it1 != "*" && it1 != "+" && it1 != "-") // mov x  0
            {
                if(it1[0] == '"')
                {
                    continue;
                }                                   

                if (m.find(it1) == m.end()) // if variable doesnt exist in hash map
                {
                    cout << "Semantic Error at { ";
                    printVector(it);
                    cout << " }" << endl;
                    exit(0);
                }
                else // if var exists in map replace var in quad with its value in map
                {
                    it1 = to_string(m[it1]);
                }
            }
        }
    }

    cout << endl
         << endl;
    cout << "quad after replacement" << endl;

    for (auto &it1 : vc)
    {
        printVector(it1);
    }

    for (int i = 0; i < vc.size(); i++) 
    {
        if (vc[i][0] == "+")
        {
            int i = stoi(vc[i][1]);
            int j = stoi(vc[i][2]);
            int k = stoi(vc[i][3]);
            ds[k] = ds[i] + ds[j];
        }

        else if (vc[i][0] == "-")
        {
            int i = stoi(vc[i][1]);
            int j = stoi(vc[i][2]);
            int k = stoi(vc[i][3]);
            ds[k] = ds[i] - ds[j];
        }

        else if (vc[i][0] == "/")
        {

        }

        else if (vc[i][0] == "*")
        {
            
        }

        else if (vc[i][0] == "%")
        {

        }
        

    // e.g. ‘+’ 10 14 18



    else if (vc[i][0] == "goto")
    {

    }
        // pc = quad[pc][1] - 1;
        // break;

    // goto 100



    else if (vc[i][0] == "GE")
    {

    }

    else if (vc[i][0] == "GT")
    {

    }

    else if(vc[i][0] == "EQ")
    {

    }

    else if (vc[i][0] == "LT")
    {

    }

    else if (vc[i][0] == "LE")
    {

    }

    else if (vc[i][0] == "NE")
    {

    }
        // int i = quad[pc][1];
        // int j = quad[pc][2];
        // int k = quad[pc][3];
        // if (ds[i] >= ds[j])
        //     pc = k - 1;
        // break;

    // e.g. if x >= y goto 100
    // GE &x &y 100



    else if (vc[i][0] == "in")
    {

    }
        // int i = quad[pc][1];
        // cin >> ds[i];
        // break;

    else if (vc[i][0] == "out")
    {
        if (vc[i][1][0] == '"')
        {
            cout << vc[i][1].substr(1, vc[i][1].length() - 2); 
        }

        else
        {
            int i = stoi(vc[i][1]);
            cout << ds[i];
        }
    }

    else if (vc[i][0] == "mov")
    {
        ds[stoi(vc[i][1])] = ds[stoi(vc[i][2])];
    }

    else if (vc[i][0] == "ret")
    {
        exit(1);
    }
}
}