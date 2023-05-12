#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <fstream>
#include <string>


class parser
{
    int varNum;
    lexer _lexer;
    int tblIndex;
    int tabs;
    int lineNum;
    ofstream fout;
    vector<string> icLines;

    void printTabs(string functionName)
    {
        for (int i = 0; i < tabs; i++)
        {
            cout << "   ";
        }

        cout << functionName << endl;
    }

    enum Datatype
    {
        khali = 0,
        adad = 1
    };

    enum type
    {
        func = 0,
        var = 1
    };

    struct symbol
    {
        Datatype d;
        string var;
        type t;
        int address;
        int init;
    };

    vector<symbol> tbl;
    int address;

public:
    string newTemp();
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    bool Expression(string &s);
    bool T(string &s);
    bool F(string &s);
    bool Q(string &s, string i);
    bool R(string &s, string i);
    bool Datatype();
    bool Datatype2();
    bool Output();
    bool Return();
    bool Input();
    bool In();
    bool Out();
    bool Loop();
    bool Statements();
    bool If();
    bool Else(vector<int>& v);
    bool Els(vector<int>& v);
    bool Ele(vector<int>& v);
    bool El();
    bool Declaration();
    bool DecType(string& id);
    bool AssignToExp(string& id);
    bool CorE(string id);
    bool Call(string& s);
    bool Pass(int& v);
    bool L(int& v);
    bool Statement();
    bool Comment();
    bool CommentBody();
    bool Start();
    bool S();
    bool Function();
    bool Markazi();
    bool Params();
    bool P();
    bool A();
    bool B();
    bool Assignment();
    bool X();
    void checkEL();
    void fillBlank(int n, int val);
};
#endif
