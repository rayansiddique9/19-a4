#include "parser.h"

string parser::newTemp()
{
    string res = "t" + to_string(varNum);
    return res;
}

void parser::fillBlank(int n, int val)
{
    icLines[n] += to_string(val);
}

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    cout << " at line " << lineNum << endl;
    exit(1);
}

token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}

void parser::checkEL()
{
    while (_lexer.peek(1).tokenType == TokenType::END_OF_LINE)
    {
        expect(TokenType::END_OF_LINE);
        lineNum++;
    }
}

bool parser::T(string &s)
{
    tabs++;
    printTabs("T");
    tabs--;
    if (!F(s))
    {
        syntax_error();
        return false;
    }

    string i = s;

    if (!Q(s, i))
    {
        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::R(string &s, string i)
{
    tabs++;
    printTabs("R");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        tabs++;
        printTabs("+");
        tabs--;
        expect(TokenType::PLUS);
        checkEL();
        if (!T(s))
        {
            syntax_error();
            return false;
        }

        string var = newTemp();
        // fout << var << " = " << i << " + " << s << endl;
        string fileOut = var + " = " + i + " + " +  s + "\n";
        icLines.push_back(fileOut);
        i = var;
        varNum++;
        if (!R(s, i))
        {
            syntax_error();
            return false;
        }
    }

    else if (_lexer.peek(1).tokenType == TokenType::MINUS)
    {
        tabs++;
        printTabs("-");
        tabs--;
        expect(TokenType::MINUS);
        checkEL();

        if (!T(s))
        {
            syntax_error();
            return false;
        }

        string var = newTemp();
        varNum++;
        //fout << var << " = " << i << " - " << s << endl;
        string fileOut = var + " = " + i + " - " +  s + "\n";
        icLines.push_back(fileOut);
        i = var;
        if (!R(s, i))
        {
            syntax_error();
            return false;
        }
    }
    else // for R-> ^ {R.s = R.i} production
    {
        s = i;
    }

    tabs--;
    return true;
}

bool parser::Q(string &s, string i)
{
    tabs++;
    printTabs("Q");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::MUL)
    {
        tabs++;
        printTabs("*");
        tabs--;
        expect(TokenType::MUL);
        checkEL();
        if (!F(s))
        {
            syntax_error();
            return false;
        }

        string var = newTemp();
        varNum++;
        //fout << var << " = " << i << " * " << s << endl;
        string fileOut = var + " = " + i + " * " +  s + "\n";
        icLines.push_back(fileOut);
        i = var;
        if (!Q(s, i))
        {
            syntax_error();
            return false;
        }
    }

    else if (_lexer.peek(1).tokenType == TokenType::DIV)
    {
        tabs++;
        printTabs("/");
        tabs--;
        expect(TokenType::DIV);
        checkEL();
        if (!F(s))
        {
            syntax_error();
            return false;
        }

        string var = newTemp();
        varNum++;
        //fout << var << " = " << i << " / " << s << endl;
        string fileOut = var + " = " + i + " / " +  s + "\n";
        icLines.push_back(fileOut);
        i = var;
        if (!Q(s, i))
        {
            syntax_error();
            return false;
        }
    }

    else if (_lexer.peek(1).tokenType == TokenType::MOD)
    {
        tabs++;
        printTabs("%");
        tabs--;
        expect(TokenType::MOD);
        checkEL();
        if (!F(s))
        {
            syntax_error();
            return false;
        }

        string var = newTemp();
        varNum++;
        //fout << var << " = " << i << " % " << s << endl;
        string fileOut = var + " = " + i + " % " +  s + "\n";
        icLines.push_back(fileOut);
        i = var;
        if (!Q(s, i))
        {
            syntax_error();
            return false;
        }
    }
    else // for Q -> ^ {Q.s = Q.i} production
    {
        s = i;
    }

    tabs--;
    return true;
}

bool parser::F(string &s)
{
    tabs++;
    printTabs("F");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        s = _lexer.peek(1).lexeme;
        expect(TokenType::ID);
        checkEL();
        tabs--;
        return true;
    }

    else if (_lexer.peek(1).tokenType == TokenType::NUM)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        s = _lexer.peek(1).lexeme;
        expect(TokenType::NUM);
        checkEL();
        tabs--;
        return true;
    }

    syntax_error();
    return false;
}

bool parser::Expression(string &s)
{

    tabs++;
    printTabs("Expression");
    if (!T(s))
    {
        syntax_error();
        return false;
    }

    string i = s;

    if (!R(s, i))
    {
        syntax_error();
        return false;
    }

    tabs--;
    // fout << s << endl;
    return true;
}

bool parser::Datatype()
{
    tabs++;
    printTabs("Datatype");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        tbl[tblIndex].d = Datatype::adad;
        tblIndex++;
        tabs++;
        printTabs("adad");
        tabs--;
        expect(TokenType::adad);
        checkEL();
        tabs--;
        return true;
    }

    else if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        tbl[tblIndex].d = Datatype::khali;
        tblIndex++;
        tabs++;
        printTabs("khali");
        tabs--;
        expect(TokenType::khali);
        checkEL();
        tabs--;
        return true;
    }

    syntax_error();
    return false;
}

bool parser::Datatype2()
{
    tabs++;
    printTabs("Datatype");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        tabs++;
        printTabs("adad");
        tabs--;
        expect(TokenType::adad);
        checkEL();
        tabs--;
        return true;
    }

    else if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        tabs++;
        printTabs("khali");
        tabs--;
        expect(TokenType::khali);
        checkEL();
        tabs--;
        return true;
    }

    syntax_error();
    return false;
}

bool parser::Input()
{
    tabs++;
    printTabs("Input");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::lo)
    {
        tabs++;
        printTabs("lo");
        tabs--;
        expect(TokenType::lo);
        checkEL();
        if (!In())
        {
            syntax_error();
            return false;
        }

        tabs--;
        return true;
    }

    return false;
}

bool parser::B()
{
    tabs++;
    printTabs("B");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        tabs++;
        printTabs(">>");
        tabs--;
        expect(TokenType::INPUT);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            icLines.push_back("in " + _lexer.peek(1).lexeme + '\n');
            expect(TokenType::ID);
            checkEL();
            if (!B())
            {
                syntax_error();
                return false;
            }

            tabs--;
            return true;
        }

        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::In()
{
    tabs++;
    printTabs("In");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        tabs++;
        printTabs(">>");
        tabs--;
        expect(TokenType::INPUT);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            icLines.push_back("in " + _lexer.peek(1).lexeme + '\n');
            expect(TokenType::ID);
            checkEL();
            if (!B())
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }

        syntax_error();
        return false;
    }

    else if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        tabs++;
        printTabs("<<");
        tabs--;
        expect(TokenType::OUTPUT);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::STR)
        {
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            icLines.push_back("out \"" + _lexer.peek(1).lexeme.substr(1, _lexer.peek(1).lexeme.length() - 2) + "\"\n");
            expect(TokenType::STR);
            if (_lexer.peek(1).tokenType == TokenType::INPUT)
            {
                tabs++;
                printTabs(">>");
                tabs--;
                expect(TokenType::INPUT);
                checkEL();
                if (_lexer.peek(1).tokenType == TokenType::ID)
                {
                    tabs++;
                    printTabs(_lexer.peek(1).lexeme);
                    tabs--;
                    icLines.push_back("in " + _lexer.peek(1).lexeme + '\n');
                    expect(TokenType::ID);
                    tabs--;
                    return true;
                }
                syntax_error();
                return false;
            }
            syntax_error();
            return false;
        }

        syntax_error();
        return false;
    }

    syntax_error();
    return false;
}

bool parser::A()
{
    tabs++;
    printTabs("A");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        tabs++;
        printTabs("<<");
        tabs--;
        expect(TokenType::OUTPUT);
        checkEL();
        if (!Out())
        {
            syntax_error();
            return false;
        }

        if (!A())
        {
            syntax_error();
            return false;
        }

        tabs--;
        return true;
    }

    tabs--;
    return true;
}

bool parser::Out()
{
    tabs++;
    printTabs("Out");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::NUM)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        icLines.push_back("out " + _lexer.peek(1).lexeme + '\n');
        expect(TokenType::NUM);
        checkEL();
        tabs--;
        return true;
    }

    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        icLines.push_back("out " + _lexer.peek(1).lexeme + '\n');
        expect(TokenType::ID);
        checkEL();
        tabs--;
        return true;
    }

    else if (_lexer.peek(1).tokenType == TokenType::STR)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        icLines.push_back("out \"" + _lexer.peek(1).lexeme.substr(1, _lexer.peek(1).lexeme.length() - 2) + "\"\n");
        expect(TokenType::STR);
        checkEL();
        tabs--;
        return true;
    }

    syntax_error();
    return false;
}

bool parser::Output()
{
    tabs++;
    printTabs("Output");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::dekhao)
    {
        tabs++;
        printTabs("dekhao");
        tabs--;
        expect(TokenType::dekhao);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
        {
            tabs++;
            printTabs("<<");
            tabs--;
            expect(TokenType::OUTPUT);
            checkEL();
            if (!Out())
            {
                syntax_error();
                return false;
            }

            if (!A())
            {
                syntax_error();
                return false;
            }

            tabs--;
            return true;
        }

        syntax_error();
        return false;
    }

    return false;
}

bool parser::Return()
{
    tabs++;
    printTabs("Return");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::wapas)
    {
        tabs++;
        printTabs("wapas");
        tabs--;
        expect(TokenType::wapas);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::bhaijo)
        {
            tabs++;
            printTabs("bhaijo");
            tabs--;
            expect(TokenType::bhaijo);
            checkEL();
            if (_lexer.peek(1).tokenType == TokenType::NUM)
            {
                tabs++;
                printTabs(_lexer.peek(1).lexeme);
                tabs--;
                icLines.push_back("ret " + _lexer.peek(1).lexeme + '\n');
                expect(TokenType::NUM);
                checkEL();
                tabs--;
                return true;
            }
            syntax_error();
            return false;
        }
        syntax_error();
        return false;
    }

    return false;
}

bool parser::Loop()
{
    string s;
    tabs++;
    printTabs("Loop");
    int f = 0;
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::jab)
    {
        tabs++;
        printTabs("jab");
        tabs--;
        expect(TokenType::jab);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::tak)
        {
            tabs++;
            printTabs("tak");
            tabs--;
            expect(TokenType::tak);
            checkEL();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                tabs++;
                printTabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                checkEL();
                if (!Expression(s))
                {
                    syntax_error();
                    return false;
                }
                else
                {
                    // fout << s << endl;
                    icLines.push_back("if " + s);
                    if (_lexer.peek(1).tokenType == TokenType::RO)
                    {
                        tabs++;
                        printTabs(_lexer.peek(1).lexeme);
                        tabs--;
                        icLines[icLines.size() - 1] += ' ' + _lexer.peek(1).lexeme + ' ';
                        expect(TokenType::RO);
                        checkEL();
                        if (!Expression(s))
                        {
                            syntax_error();
                            return false;
                        }
                        else
                        {
                            // fout << s << endl;
                            icLines[icLines.size() - 1] += s + " goto " + to_string(icLines.size() + 2) + '\n';
                            icLines.push_back("goto ");
                            f = icLines.size() - 1;
                            if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                            {
                                tabs++;
                                printTabs(")");
                                tabs--;
                                expect(TokenType::CLOSE_PARENTHESIS);
                                checkEL();
                                if (_lexer.peek(1).tokenType == TokenType::karo)
                                {
                                    tabs++;
                                    printTabs("karo");
                                    tabs--;
                                    expect(TokenType::karo);
                                    checkEL();
                                    if (!Statements())
                                    {
                                        syntax_error();
                                        return false;
                                    }

                                    else
                                    {
                                        if (_lexer.peek(1).tokenType == TokenType::bas)
                                        {
                                            tabs++;
                                            printTabs("bas");
                                            tabs--;
                                            expect(TokenType::bas);
                                            checkEL();
                                            if (_lexer.peek(1).tokenType == TokenType::karo)
                                            {
                                                tabs++;
                                                printTabs("karo");
                                                tabs--;
                                                expect(TokenType::karo);
                                                checkEL();
                                                tabs--;
                                                icLines.push_back("goto " + to_string(f) + '\n');
                                                icLines[f] += to_string(icLines.size() + 1) + '\n';
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool parser::Ele(vector<int>& v)
{
    string s;
    int f = 0;
    tabs++;
    printTabs("Ele");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
    {
        tabs++;
        printTabs("(");
        tabs--;
        expect(TokenType::OPEN_PARENTHESIS);
        checkEL();
        if (!Expression(s))
        {
            syntax_error();
            return false;
        }
        else
        {
            icLines.push_back("if " + s + " ");
            if (_lexer.peek(1).tokenType == TokenType::RO)
            {
                tabs++;
                printTabs(_lexer.peek(1).lexeme);
                tabs--;
                icLines[icLines.size() - 1] += _lexer.peek(1).lexeme;
                expect(TokenType::RO);
                checkEL();

                if (!Expression(s))
                {
                    syntax_error();
                    return false;
                }
                else
                {
                    icLines[icLines.size() - 1] += " " + s + " goto " + to_string(icLines.size() + 2) + "\n";
                    icLines.push_back("goto ");
                    f = icLines.size() - 1;
                    if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                    {
                        tabs++;
                        printTabs(")");
                        tabs--;
                        expect(TokenType::CLOSE_PARENTHESIS);
                        checkEL();
                        if (_lexer.peek(1).tokenType == TokenType::to)
                        {
                            tabs++;
                            printTabs("to");
                            tabs--;
                            expect(TokenType::to);
                            checkEL();
                            if (_lexer.peek(1).tokenType == TokenType::phir)
                            {
                                tabs++;
                                printTabs("phir");
                                tabs--;
                                expect(TokenType::phir);
                                checkEL();
                                if (!Statements())
                                {
                                    syntax_error();
                                    return false;
                                }
                                else
                                {
                                    icLines.push_back("goto ");
                                    icLines[f] += to_string(icLines.size() + 1) + "\n";
                                    v.push_back(icLines.size()- 1);
                                    if (!Els(v))
                                    {
                                        syntax_error();
                                        return false;
                                    }
                                    else
                                    {
                                        tabs--;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    syntax_error();
    return false;
}

bool parser::El()
{
    tabs++;
    printTabs("El");
    if (!Statements())
    {
        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::Els(vector<int>& v)
{
    tabs++;
    printTabs("Els");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        tabs++;
        printTabs("warna");
        tabs--;
        expect(TokenType::warna);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::agar)
        {
            tabs++;
            printTabs("agar");
            tabs--;
            expect(TokenType::agar);
            checkEL();
            if (!Ele(v))
            {
                syntax_error();
                return false;
            }
            else
            {
                tabs--;
                return true;
            }
        }
        else if (_lexer.peek(1).tokenType == TokenType::phir)
        {
            tabs++;
            printTabs("phir");
            tabs--;
            expect(TokenType::phir);
            checkEL();
            if (!El())
            {
                syntax_error();
                return false;
            }
            else
            {
                tabs--;
                return true;
            }
        }
    }

    syntax_error();
    return false;
}

bool parser::Else(vector<int>& v)
{
    string s;
    tabs++;
    printTabs("Else");
    int f = 0;
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        tabs++;
        printTabs("warna");
        tabs--;
        expect(TokenType::warna);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::agar)
        {
            tabs++;
            printTabs("agar");
            tabs--;
            expect(TokenType::agar);
            checkEL();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                tabs++;
                printTabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                checkEL();
                if (!Expression(s))
                {
                    syntax_error();
                    return false;
                }
                else
                {
                    icLines.push_back("if " + s + " ");
                    if (_lexer.peek(1).tokenType == TokenType::RO)
                    {
                        tabs++;
                        printTabs(_lexer.peek(1).lexeme);
                        tabs--;
                        icLines[icLines.size() - 1] += _lexer.peek(1).lexeme;
                        expect(TokenType::RO);
                        checkEL();
                        if (!Expression(s))
                        {
                            syntax_error();
                            return false;
                        }
                        else
                        {
                            icLines[icLines.size() - 1] += " " + s + " goto " + to_string(icLines.size() + 2) + "\n";
                            icLines.push_back("goto ");
                            f = icLines.size() - 1;
                            if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                            {
                                tabs++;
                                printTabs(")");
                                tabs--;
                                expect(TokenType::CLOSE_PARENTHESIS);
                                checkEL();
                                if (_lexer.peek(1).tokenType == TokenType::to)
                                {
                                    tabs++;
                                    printTabs("to");
                                    tabs--;
                                    expect(TokenType::to);
                                    checkEL();

                                    if (_lexer.peek(1).tokenType == TokenType::phir)
                                    {
                                        tabs++;
                                        printTabs("phir");
                                        tabs--;
                                        expect(TokenType::phir);
                                        checkEL();

                                        if (!Statements())
                                        {
                                            syntax_error();
                                            return false;
                                        }
                                        else
                                        {
                                            icLines.push_back("goto ");
                                            icLines[f] += to_string(icLines.size() + 1) + "\n";
                                            v.push_back(icLines.size() - 1);
                                            if (!Els(v))
                                            {
                                                syntax_error();
                                                return false;
                                            }
                                            else
                                            {
                                                tabs--;
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    syntax_error();
    return false;
}

bool parser::If()
{
    vector <int> forIf;
    int f;
    string s;
    ++tabs;
    printTabs("If");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::agar)
    {
        tabs++;
        printTabs("agar");
        tabs--;
        expect(TokenType::agar);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
        {
            tabs++;
            printTabs("(");
            tabs--;
            expect(TokenType::OPEN_PARENTHESIS);
            checkEL();

            if (!Expression(s))
            {
                syntax_error();
                return false;
            }
            else
            {
                icLines.push_back("if " + s + " ");
                if (_lexer.peek(1).tokenType == TokenType::RO)
                {
                    tabs++;
                    printTabs(_lexer.peek(1).lexeme);
                    tabs--;
                    icLines[icLines.size() - 1] += _lexer.peek(1).lexeme;
                    expect(TokenType::RO);
                    checkEL();

                    if (!Expression(s))
                    {
                        syntax_error();
                        return false;
                    }
                    else
                    {
                        icLines[icLines.size() - 1] += " " + s + " goto " + to_string(icLines.size() + 2) + '\n';
                        icLines.push_back("goto ");
                        f = icLines.size() - 1;
                        if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                        {
                            tabs++;
                            printTabs(")");
                            tabs--;
                            expect(TokenType::CLOSE_PARENTHESIS);
                            checkEL();

                            if (_lexer.peek(1).tokenType == TokenType::to)
                            {
                                tabs++;
                                printTabs("to");
                                tabs--;
                                expect(TokenType::to);
                                checkEL();

                                if (_lexer.peek(1).tokenType == TokenType::phir)
                                {
                                    tabs++;
                                    printTabs("phir");
                                    tabs--;
                                    expect(TokenType::phir);
                                    checkEL();

                                    if (_lexer.peek(1).tokenType == TokenType::karo)
                                    {
                                        tabs++;
                                        printTabs("karo");
                                        tabs--;
                                        expect(TokenType::karo);
                                        checkEL();

                                        if (!Statements())
                                        {
                                            syntax_error();
                                            return false;
                                        }
                                        else
                                        {
                                            icLines.push_back("goto "); 
                                            icLines[f] += to_string(icLines.size() + 1) + "\n"; 
                                            forIf.push_back(icLines.size() - 1);
                                            if (!Else(forIf))
                                            {
                                                syntax_error();
                                                return false;
                                            }
                                            else
                                            {
                                                if (_lexer.peek(1).tokenType == TokenType::bas)
                                                {
                                                    tabs++;
                                                    printTabs("bas");
                                                    tabs--;
                                                    expect(TokenType::bas);
                                                    checkEL();

                                                    if (_lexer.peek(1).tokenType == TokenType::karo)
                                                    {
                                                        tabs++;
                                                        for (int i = 0; i < forIf.size(); i++)
                                                        {
                                                            icLines[forIf[i]] += to_string(icLines.size() + 1) + "\n";
                                                        }
                                                        printTabs("karo");
                                                        tabs--;
                                                        expect(TokenType::karo);
                                                        checkEL();
                                                        tabs--;
                                                        return true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool parser::Declaration()
{
    tabs++;
    printTabs("Declaration");
    checkEL();
    string id;
    if (_lexer.peek(1).tokenType == TokenType::rakho)
    {
        tabs++;
        printTabs("rakho");
        tabs--;
        expect(TokenType::rakho);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            id = _lexer.peek(1).lexeme;
            symbol s;
            s.var = _lexer.peek(1).lexeme;
            tbl.push_back(s);
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            expect(TokenType::ID);
            checkEL();
            if (!DecType(id))
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
        syntax_error();
        return false;
    }
    return false;
}

bool parser::DecType(string& id)
{
    tabs++;
    printTabs("DecType");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::AT)
    {
        tabs++;
        printTabs("@");
        tabs--;
        expect(TokenType::AT);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::adad)
        {
            tbl[tblIndex].d = Datatype::adad;
            tblIndex++;
            tabs++;
            printTabs("adad");
            tabs--;
            expect(TokenType::adad);
            checkEL();
            if (!AssignToExp(id))
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
        syntax_error();
        return false;
    }

    else if (_lexer.peek(1).tokenType == TokenType::ASSIGNMENT)
    {
        tbl.pop_back();
        tabs++;
        printTabs(":=");
        tabs--;
        expect(TokenType::ASSIGNMENT);
        checkEL();
        if (!CorE(id))
        {
            syntax_error();
            return false;
        }

        tabs--;
        return true;
    }

    syntax_error();
    return false;
}

bool parser::AssignToExp(string& id)
{
    tabs++;
    printTabs("AssignToExp");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::ASSIGNMENT)
    {
        tabs++;
        printTabs(":=");
        tabs--;
        expect(TokenType::ASSIGNMENT);
        checkEL();
        if (!CorE(id))
        {
            syntax_error();
            return false;
        }

        tabs--;
        return true;
    }

    tabs--;
    return true;
}

bool parser::CorE(string id)
{
    string temp;
    string s;
    tabs++;
    printTabs("CorE");
    if (!Call(temp))
    {
        if (!Expression(s))
        {
            syntax_error();
            return false;
        }

        icLines.push_back(id + " = " + s + '\n');
        tabs--;
        return true;
    }
    icLines.push_back(id + " = " + temp + '\n');
    tabs--;
    return true;
}

bool parser::Call(string& s)
{
    tabs++;
    printTabs("Call");
    checkEL();
    string func;
    int v = 0;
    if (_lexer.peek(1).tokenType == TokenType::chalao)
    {
        tabs++;
        printTabs("chalao");
        tabs--;
        expect(TokenType::chalao);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            func = _lexer.peek(1).lexeme;
            expect(TokenType::ID);
            checkEL();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                tabs++;
                printTabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                checkEL();
                if (!Pass(v))
                {
                    syntax_error();
                    return false;
                }

                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    tabs++;
                    printTabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                    string newT = newTemp();
                    s = newT;
                    icLines.push_back(func + ' ' + to_string(v) + ", " + newT + "\n");
                    checkEL();
                    tabs--;
                    return true;
                }

                syntax_error();
                return false;
            }
            syntax_error();
            return false;
        }
        syntax_error();
        return false;
    }
    return false;
}

bool parser::Pass(int& v)
{
    tabs++;
    printTabs("Pass");
    checkEL();
    string s;
    if (!Expression(s))
    {
        // syntax_error();
        // return false;
    }
    else
    {
        icLines.push_back("param " + s + '\n');
        v++;
        // if (_lexer.peek(1).tokenType == TokenType::ID)
        // {
        //     tabs++;
        //     printTabs(_lexer.peek(1).lexeme);
        //     tabs--;
        //     expect(TokenType::ID);
        //     checkEL();

            if (!L(v))
            {
                syntax_error();
                return false;
            }

        //     tabs--;
        //     return true;
        // }
    }

    tabs--;
    return true;
}

bool parser::L(int& v)
{
    tabs++;
    printTabs("L");
    checkEL();
    string s;
    if (_lexer.peek(1).tokenType == TokenType::PIPE)
    {
        tabs++;
        printTabs("|");
        tabs--;
        expect(TokenType::PIPE);
        checkEL();
        v++;

        if (!Expression(s))
        {
            syntax_error();
            return false;
        }

        else
        {
            icLines.push_back("param " + s + '\n');
            v++;
            if (!L(v))
            {
                syntax_error();
                return false;
            }

            else
            {
                return true;
            }
        }

        // if (_lexer.peek(1).tokenType == TokenType::ID)
        // {
        //     tabs++;
        //     printTabs(_lexer.peek(1).lexeme);
        //     tabs--;
        //     expect(TokenType::ID);
        //     checkEL();

        //     tabs--;
        //     return true;
        // }

        // syntax_error();
        // return false;
    }

    v--;
    tabs--;
    return true;
}

bool parser::Statements()
{
    tabs++;
    printTabs("Statements");
    if (!Statement()) // if loop kaam
    {
        tabs--;
        return true;
    }

    if (!Statements())
    {
        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::Statement()
{
    tabs++;
    printTabs("Statement");
    checkEL();
    if (Declaration())
    {
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            tabs++;
            printTabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            checkEL();
            if (!Comment())
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
    }
    else if (Loop())
    {
        if (!CommentBody())
        {
            syntax_error();
            return false;
        }
        tabs--;
        return true;
    }
    else if (Input())
    {
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            tabs++;
            printTabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            checkEL();

            if (!Comment())
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
    }
    else if (Output())
    {
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            tabs++;
            printTabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            checkEL();

            if (!Comment())
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
    }

    else if (If())
    {
        if (!CommentBody())
        {
            syntax_error();
            return false;
        }
        tabs--;
        return true;
    }
    else if (Return())
    {
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            tabs++;
            printTabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            checkEL();

            if (!Comment())
            {
                syntax_error();
                return false;
            }
            tabs--;
            return true;
        }
    }

    else if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {

        if (!CommentBody())
        {
            syntax_error();
            return false;
        }

        tabs--;
        return true;
    }

    return false;
}

bool parser::CommentBody()
{
    tabs++;
    printTabs("CommentBody");
    tabs--;
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        tabs++;
        printTabs(";");
        tabs--;
        expect(TokenType::SEMICOLON);
        checkEL();
        if (!Comment())
        {
            syntax_error();
            return false;
        }
        if (!X())
        {
            syntax_error();
            return false;
        }
    }

    tabs--;
    return true;
}

bool parser::X()
{
    tabs++;
    printTabs("X");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        tabs++;
        printTabs(";");
        tabs--;
        expect(TokenType::SEMICOLON);
        checkEL();
        if (!Comment())
        {
            syntax_error();
            return false;
        }
        if (!X())
        {
            syntax_error();
            return false;
        }
    }
    tabs--;
    return true;
}

bool parser::Comment()
{
    tabs++;
    printTabs("Comment");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::CMNT)
    {
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        expect(TokenType::CMNT);
        checkEL();
    }

    tabs--;
    return true;
}

bool parser::Start()
{
    tabs++;
    printTabs("Start");

    if (!S())
    {
        syntax_error();
        return false;
    }

    if (!Markazi())
    {
        syntax_error();
        return false;
    }

    if (!S())
    {
        syntax_error();
        return false;
    }

    if (static_cast<int>(_lexer.peek(1).tokenType) != 0)
    {
        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::S()
{
    tabs++;
    printTabs("S");
    checkEL();
    if (!CommentBody())
    {
        syntax_error();
        return false;
    }
    checkEL();

    if (_lexer.peek(1).tokenType == TokenType::kaam)
    {
        tabs++;
        printTabs("kaam");
        tabs--;
        expect(TokenType::kaam);
        checkEL();
        if (!Function())
        {
            syntax_error();
            return false;
        }

        if (_lexer.peek(1).tokenType == TokenType::markazi)
        {
            _lexer.setCurrentPointer(_lexer.getCurrentPointer() - 1);
            return true;
        }

        if (_lexer.peek(1).tokenType == TokenType::kaam)
        {
            tabs++;
            printTabs("kaam");
            tabs--;
            expect(TokenType::kaam);
            checkEL();
            if (_lexer.peek(1).tokenType == TokenType::khatam)
            {
                tabs++;
                printTabs("khatam");
                tabs--;
                expect(TokenType::khatam);
                checkEL();
                if (!S())
                {
                    syntax_error();
                    return false;
                }

                tabs--;
                return true;
            }

            syntax_error();
            return false;
        }

        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::Markazi()
{
    tabs++;
    printTabs("Markazi");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::kaam)
    {
        tabs++;
        printTabs("kaam");
        tabs--;
        expect(TokenType::kaam);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::markazi)
        {
            tabs++;
            printTabs("markazi");
            tabs--;
            expect(TokenType::markazi);
            checkEL();

            if (_lexer.peek(1).tokenType == TokenType::AT)
            {
                tabs++;
                printTabs("@");
                tabs--;
                expect(TokenType::AT);
                checkEL();

                if (!Datatype2())
                {
                    syntax_error();
                    return false;
                }

                if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
                {
                    tabs++;
                    printTabs("(");
                    tabs--;
                    expect(TokenType::OPEN_PARENTHESIS);
                    checkEL();
                    if (!Params())
                    {
                        syntax_error();
                        return false;
                    }
                    if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                    {
                        tabs++;
                        printTabs(")");
                        tabs--;
                        expect(TokenType::CLOSE_PARENTHESIS);
                        checkEL();
                        if (_lexer.peek(1).tokenType == TokenType::karo)
                        {
                            tabs++;
                            printTabs("karo");
                            tabs--;
                            expect(TokenType::karo);
                            checkEL();
                            if (!Statements())
                            {
                                syntax_error();
                                return false;
                            }
                            else
                            {
                                if (_lexer.peek(1).tokenType == TokenType::kaam)
                                {
                                    tabs++;
                                    printTabs("kaam");
                                    tabs--;
                                    expect(TokenType::kaam);
                                    checkEL();
                                    if (_lexer.peek(1).tokenType == TokenType::khatam)
                                    {
                                        tabs++;
                                        printTabs("khatam");
                                        tabs--;
                                        expect(TokenType::khatam);
                                        checkEL();
                                        if (!CommentBody())
                                        {
                                            syntax_error();
                                            return false;
                                        }
                                        tabs--;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    syntax_error();
    return false;
}

bool parser::Params()
{
    tabs++;
    printTabs("Params");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        symbol s;
        s.var = _lexer.peek(1).lexeme;
        tbl.push_back(s);
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        expect(TokenType::ID);
        checkEL();

        if (_lexer.peek(1).tokenType == TokenType::AT)
        {
            tabs++;
            printTabs("@");
            tabs--;
            expect(TokenType::AT);
            checkEL();

            if (_lexer.peek(1).tokenType == TokenType::adad)
            {
                tbl[tblIndex].d = Datatype::adad;
                tblIndex++;
                tabs++;
                printTabs("adad");
                tabs--;
                expect(TokenType::adad);
                checkEL();

                if (!P())
                {
                    syntax_error();
                    return false;
                }
                tabs--;
                return true;
            }
            syntax_error();
            return false;
        }
        syntax_error();
        return false;
    }
    tabs--;
    return true;
}

bool parser::P()
{
    tabs++;
    printTabs("P");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::PIPE)
    {
        tabs++;
        printTabs("|");
        tabs--;
        expect(TokenType::PIPE);
        checkEL();

        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            symbol s;
            s.var = _lexer.peek(1).lexeme;
            tbl.push_back(s);
            tabs++;
            printTabs(_lexer.peek(1).lexeme);
            tabs--;
            expect(TokenType::ID);
            checkEL();

            if (_lexer.peek(1).tokenType == TokenType::AT)
            {
                tabs++;
                printTabs("@");
                tabs--;
                expect(TokenType::AT);
                checkEL();

                if (_lexer.peek(1).tokenType == TokenType::adad)
                {
                    tbl[tblIndex].d = Datatype::adad;
                    tblIndex++;
                    tabs++;
                    printTabs("adad");
                    tabs--;
                    expect(TokenType::adad);
                    checkEL();

                    if (!P())
                    {
                        syntax_error();
                        return false;
                    }
                    tabs--;
                    return true;
                }
                syntax_error();
                return false;
            }
            syntax_error();
            return false;
        }
        syntax_error();
        return false;
    }

    tabs--;
    return true;
}

bool parser::Function()
{
    tabs++;
    printTabs("Function");
    checkEL();
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        symbol s;
        s.var = _lexer.peek(1).lexeme;
        tbl.push_back(s);
        tabs++;
        printTabs(_lexer.peek(1).lexeme);
        tabs--;
        expect(TokenType::ID);
        checkEL();
        if (_lexer.peek(1).tokenType == TokenType::AT)
        {
            tabs++;
            printTabs("@");
            tabs--;
            expect(TokenType::AT);
            checkEL();
            if (!Datatype())
            {
                syntax_error();
                return false;
            }

            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                tabs++;
                printTabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                checkEL();
                if (!Params())
                {
                    syntax_error();
                    return false;
                }

                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    tabs++;
                    printTabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                    checkEL();
                    if (_lexer.peek(1).tokenType == TokenType::karo)
                    {
                        tabs++;
                        printTabs("karo");
                        tabs--;
                        expect(TokenType::karo);
                        checkEL();
                        if (!Statements())
                        {
                            syntax_error();
                            return false;
                        }

                        tabs--;
                        return true;
                    }

                    syntax_error();
                    return false;
                }

                syntax_error();
                return false;
            }

            syntax_error();
            return false;
        }

        syntax_error();
        return false;
    }

    else if (_lexer.peek(1).tokenType == TokenType::markazi)
    {
        return true;
    }

    syntax_error();
    return false;
}

parser::parser(const char filename[])
{
    tabs = 0;
    tblIndex = 0;
    varNum = 1;
    icLines = vector<string>();

    lineNum = 1;
    _lexer = lexer(filename);

    fout.open("TAC.txt");

    if (Start())
    {
        cout << "Compilation Successful" << endl;

        for (int i = 0; i < icLines.size(); i++)
        {
            fout << icLines[i];
        }

        if (tbl.size() > 0)
        {
            cout << endl
                 << endl;
            cout << "TYPE   "
                 << "VARIABLE" << endl;
        }

        for (int i = 0; i < tbl.size(); i++)
        {
            if (tbl[i].d == Datatype::khali)
            {
                cout << "khali  ";
            }

            else
            {
                cout << "adad   ";
            }

            cout << tbl[i].var << endl;
        }
    }

    else
    {
        syntax_error();
    }
}
void parser::readAndPrintAllInput() // read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}