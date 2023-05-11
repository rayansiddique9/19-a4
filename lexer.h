#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	ERROR = 1,
	ID = 2, 
	NUM = 3, 
	RO = 4,  
	STR = 5,
	CMNT = 6,
	markazi = 7,
	kaam = 8,
	karo = 9,
	rakho = 10,
	jab = 11,
	tak = 12,
	bas = 13,
	agar = 14,
	to = 15,
	warna = 16,
	phir = 17,
	dekhao = 18,
	lo = 19,
	chalao = 20,
	wapas = 21,
	bhaijo = 22,
	adad = 23,
	khali = 24,
	khatam = 25,
	PLUS = 26,
	MINUS = 27,
	MUL = 28,
	DIV = 29,
	MOD = 30,
	PIPE = 31,
	COLON = 32,
	SEMICOLON = 33,
	AT = 34,
	BACKTICK = 35,
	OPEN_PARENTHESIS = 36,
	CLOSE_PARENTHESIS = 37,
	ASSIGNMENT = 38,
	INPUT = 39,
	OUTPUT = 40,
	END_OF_LINE = 41
};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
};

#endif // !_LEXER_H
