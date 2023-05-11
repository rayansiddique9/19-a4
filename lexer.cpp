#include "lexer.h"
#include <iostream>
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
	"END_OF_FILE",
	"ERROR",
	"ID", 
	"NUM", 
	"RO",  
	"STR",
	"CMNT",
	"markazi",
	"kaam",
	"karo",
	"rakho" ,
	"jab" ,
	"tak" ,
	"bas" ,
	"agar" ,
	"to" ,
	"warna" ,
	"phir" ,
	"dekhao" ,
	"lo" ,
	"chalao" ,
	"wapas" ,
	"bhaijo" ,
	"adad" ,
	"khali" ,
	"khatam" ,
	"+" ,
	"-" ,
	"*" ,
	"/" ,
	"%" ,
	"|" ,
	":" ,
	";" ,
	"@" ,
	"`" ,
	"(" ,
	")" ,
	":=" ,
	">>" ,
	"<<",
    "END_OF_LINE"
	};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

bool contains(char s) //check if a character is not a white space.
{
    if (s > ' ')
    {
        return false;
    }

    return true;
}

void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    int state = 0; //initial state as in DFA
    string s = ""; //string for maintaining input
    string keywords[19] = {"markazi", "kaam", "karo", "rakho", "jab", "tak", "bas", "agar", "to", "warna", "phir", "dekhao", "lo", "chalao", "wapas", "bhaijo", "adad", "khali", "khatam"}; //keyword array to check if identifier is really an identifier or a keyword
    bool isID = true; //boolean set true to begin checking if identifier or keyword.
    for (it; it != stream.end(); it++) //loop iterating through the file.
    {
        switch(state)
        {
            case 0:
                if (isalpha(*it) || *it == '_') //underscore or alphabet
                {
                    state = 1;
                    s += *it;
                }

                else if (*it == '=') //= RO operator
                {
                    s += *it;
                    state = 18;
                }

                else if (*it == '>') // All input starting with > 
                {
                    s += *it;
                    state = 9;
                }

                else if (*it == '<') //All input starting with <
                {
                    s += *it;
                    state = 11;
                }

                else if (*it >= 48 && *it <= 57) //digit
                {
                    s += *it;
                    state = 3;
                }

                else if (*it == '|' || *it == '@' || *it == '(' || *it == ')') //special characters
                {
                    s += *it;
                    state = 19;
                }

                else if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%') //arithmetic operators
                {
                    s += *it;
                    state = 20;
                }

                else if (*it == ':') //all inputs starting with :
                {
                    s += *it;
                    state = 21;
                }

                else if (*it == ';') //all inputs starting with ;
                {
                    s += *it;
                    state = 23;
                }

                else if (*it == '`') //all inputs starting with `
                {
                    s += *it;
                    state = 25;
                }

                else if (!contains(*it)) //any other character results in lexical error
                {
                    s += *it;
                    tokens.push_back(token(string(s), TokenType::ERROR));
                    s.clear();
                }

                else if (*it == '\n')
                {
                    tokens.push_back(token(string("\0"), TokenType::END_OF_LINE));
                }

                break;

            case 1:
                if(isalnum(*it) || *it == '_') //if alphanumeric literals keep coming, keep storing them
                {
                    s += *it;
                }

                else //pass the input to the next state for tokenization
                {
                    it--; it--;
                    state = 2;
                }

                break;

            case 2: // create identifier or keyword token
                isID = true;
                for (int i = 0; i < 19; i++) //check if input belongs to a keyword
                {
                    if (keywords[i] == s)
                    {
                        isID = false;
                        tokens.push_back(token(string("\0"), static_cast<TokenType>(i + 7))); //7 points to the first keyword mentioned in the TokenType enum. \0 is for null
                        break;
                    }
                }

                if (isID)
                {
                    isID = false;
                    tokens.push_back(token(string(s), TokenType::ID)); //if identifier create identifier token
                }

                s.clear(); //clear the string for next token
                state = 0;
                break;

            case 3:
                if (*it >= 48 && *it <= 57) //if digits keep coming, store
                {
                    s += *it;
                }

                else //pass to next state for token creation
                {
                    state = 4;
                }

                break;

            case 4:
                tokens.push_back(token(string(s), TokenType::NUM)); //create token for integer
                s.clear();
                it--; it--;
                state = 0;
                break;

            case 9:
                if (*it == '=') //if = comes after > (RO, GE) token is created in state 10
                {
                    s += *it;
                    state = 10;
                }

                else if (*it == '>') //if > comes after > (>>, NULL) token is created in state 13 
                {
                    s += *it;
                    state = 13;
                }

                else //if any other character comes, (RO, GT) token is created in state 14
                {
                    state = 14;
                }

                break;

            case 10:
                tokens.push_back(token(string("GE"), TokenType::RO));
                s.clear();
                it--;
                state = 0;

                break;

            case 11:
                if (*it == '=') //if = comes after < (RO, LE) token is created in state 12
                {
                    s += *it;
                    state = 12;
                }

                else if (*it == '<') //if < comes after < (<<, NULL) token is created in state 15
                {
                    s += *it;
                    state = 15;
                }

                else if(*it == '>') //if > comes after > (RO, NE) token is created in state 17
                {
                    s += *it;
                    state = 17;
                }

                else //if any other character comes, (RO, LT) token is created in state 16
                {
                    state = 16;
                }

                break;
            
            case 12:
                tokens.push_back(token(string("LE"), TokenType::RO));
                s.clear();
                it--;
                state = 0;
                break;

            case 13:
                tokens.push_back(token(string("\0"), TokenType::INPUT));
                s.clear();
                it--;
                state = 0;

                break;

            case 14:
                tokens.push_back(token(string("GT"), TokenType::RO));
                s.clear();
                it--; it--;
                state = 0;

                break;

            case 15:
                tokens.push_back(token(string("\0"), TokenType::OUTPUT));
                s.clear();
                it--;
                state = 0;
                break;

            case 16:
                tokens.push_back(token(string("LT"), TokenType::RO));
                s.clear();
                it--; it--;
                state = 0;

                break;                

            case 17:
                tokens.push_back(token(string("NE"), TokenType::RO));
                s.clear();
                it--;
                state = 0;
                break;

            case 18: //(RO, EQ) token is created 
                tokens.push_back(token(string("EQ"), TokenType::RO));
                s.clear();
                it--;
                state = 0;
                break;

            case 19: //all tokens for special characters are created
                if (s[0] == '|')
                {
                    tokens.push_back(token(string("\0"), TokenType::PIPE));
                }

                else if (s[0] == '@')
                {
                    tokens.push_back(token(string("\0"), TokenType::AT));
                }

                else if (s[0] == '(')
                {
                    tokens.push_back(token(string("\0"), TokenType::OPEN_PARENTHESIS));
                }

                else if (s[0] == ')')
                {
                    tokens.push_back(token(string("\0"), TokenType::CLOSE_PARENTHESIS));
                }

                s.clear();
                it--;
                state = 0;
                break;
            
            case 20: // all tokens for arithmetic operators are created
                if (s[0] == '+')
                {
                    tokens.push_back(token(string("\0"), TokenType::PLUS));
                }

                else if (s[0] == '-')
                {
                    tokens.push_back(token(string("\0"), TokenType::MINUS));
                }

                else if (s[0] == '*')
                {
                    tokens.push_back(token(string("\0"), TokenType::MUL));
                }

                else if (s[0] == '/')
                {
                    tokens.push_back(token(string("\0"), TokenType::DIV));
                }

                else if (s[0] == '%')
                {
                    tokens.push_back(token(string("\0"), TokenType::MOD));
                }

                s.clear();
                it--;
                state = 0;
                break;

            case 21:
                if (*it == '=') //if = comes after : (:=, NULL) token is created in state 22
                {
                    s += *it;
                    state = 22;
                }

                else // else special character (:, NULL) token is created
                {
                    tokens.push_back(token(string("\0"), TokenType::COLON));
                    s.clear();
                    state = 0;
                    it--;
                }

                break;

            case 22:
                tokens.push_back(token(string("\0"), TokenType::ASSIGNMENT));
                it--;
                s.clear();
                state = 0;
                break;

            case 23:
                if (*it == '\n') //if line ends immediately after a semicolon, special character token (;, NULL) is created
                {
                    tokens.push_back(token(string("\0"), TokenType::SEMICOLON));
                    it--;
                    s.clear();
                    state = 0;
                }

                else //pass to next state
                {
                    s += *it;
                    state = 24; //comment
                }

                break;

            case 24:
                if (*it == '\n') //endline comes
                {
                    if (s.length() == 1)//if there is only semicolon and nothing after, (;, NULL) is created
                    {
                        tokens.push_back(token(string("\0"), TokenType::SEMICOLON));
                    }

                    else //both (;, NULL) and (CMNT, '') tokens are created
                    {
                        tokens.push_back(token(string("\0"), TokenType::SEMICOLON));
                        tokens.push_back(token(string(s.substr(1, s.length())), TokenType::CMNT));
                    }
                    
                    it--;
                    s.clear();
                    state = 0;
                }

                else //keep adding to collection
                {
                    s += *it;
                }

                break;
            
            case 25:
                if (*it == '\n') //if endline arrives right after backtick, special character token is created.
                {
                    tokens.push_back(token(string("\0"), TokenType::BACKTICK));
                    
                    while(*it != '`') //to go back to the backtick and the reprocess the input after
                    {
                        it--;
                    }

                    s.clear();
                    state = 0;
                }

                else if (*it == '`') //create token for string uf second backtick appears in the same line.
                {   
                    s += *it;
                    tokens.push_back(token(string(s), TokenType::STR));
                    state = 0;
                }

                else //keep adding to collection
                {
                    s += *it;
                }

                break;


        }
    }
	//push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}