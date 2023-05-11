ru is our file extension abbreviation of "Roman Urdu". The compiler that we are going to make.

Lexical Analyzer Implementation:
We have implemented our code in lexer.h and lexer.cpp files. We made state transitions using switch case and generated tokens for all the requested constructs. 
We have tested our code throughly with the sample file given.

Parser / Syntax Analyzer:
We have implemented our code in parser.h and parser.cpp file with respect to the grammar in grammar.txt
We have defined syntax errors with line numbers. The parse tree and symbol table is printed as well.

How To Run Code:
1.  Open the command line and type 'g++ main.cpp -o a.exe'
2.  Then, type '.\a.exe [filename].ru'. Here, the 'filename' is the name of your source code file, for example: 'sample_code.ru', 
    in which case the resultant command would be:
        .\a.exe sample_code.ru

