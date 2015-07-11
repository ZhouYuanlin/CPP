//
//  Scanner.h
//  C－Minus
//
//  Created by 木木同学 on 15/5/15.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef __C_Minus__Scanner__
#define __C_Minus__Scanner__

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*定义的Token的类型(31种)，其种别码如下:
 
 单词符    种别码    value    单词符    种别码      value
 if       IF       1        =        ASSIGN     17
 else     ELSE     2        ;        SEMI       18
 int      INT      3        ,        COMMA      19
 return   RETURN   4        (        LPAREN     20
 void     VOID     5        )        RPAREN     21
 while    WHILE    6        [        LMBRACKET  22
 +        PLUS     7        ]        RMBRACKET  23
 -        MINUS    8        {        LBBRACKET  24
 *        TIMES    9        }        RBBRACKET  25
 /        OVER     10       / *      LCOMMENT   26
 <        LT       11       * /      RCOMMENT   27
 <=       LEQ      12       num      NUM        28
 >        GT       13       id       ID         29
 >=       GEQ      14       error    ERROR      30
 ==       EQ       15       end      ENDFILE    31
 !=       NEQ      16
 
 */
typedef enum
{
    IF = 1, ELSE, INT, RETURN, VOID, WHILE,
    PLUS,MINUS,TIMES,OVER,LT,LEQ,GT,GEQ,EQ,NEQ,ASSIGN,SEMI,COMMA,LPAREN,RPAREN,LMBRACKET,RMBRACKET,LBBRACKET,RBBRACKET,LCOMMENT,RCOMMENT,
    NUM,ID,ERROR,ENDFILE
} TokenType;

//定义DFA的状态
typedef enum
{
    START = 1, INNUM, INID, INDBSYM, DONE
} DFAState;

//定义Token结构体，包括类型、对应的串、所在代码的行号
typedef struct Token
{
    TokenType tokenType;
    string tokenString;
    int lineNo;
} Token;

//每种TokenType对应的串
const string tokenTypeString[32] = {"OTHER", "IF", "ELSE", "INT", "RETURN", "VOID", "WHILE", "PLUS", "MINUS", "TIMES", "OVER", "LT", "LEQ" , "GT", "GEQ", "EQ", "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LMBRACKET", "RMBRACKET", "LBBRACKET", "RBBRACKET", "LCOMMENT", "ROCMMENT", "NUM", "ID", "ERROR", "ENDFILE"};

class Scanner
{
public:
    bool scanSuccess;                              //词法分析是否成功的标志
    Scanner();                                     //构造函数
    void getSourseFile(string s);                  //通过提供的文件名获取源代码
    void deleteComments();                         //删除注释
    void scan();                                   //词法分析，将分析的Token放在tokenList数组中
    Token getTokenAt(int);                         //根据下标从tokenList数组中获取Token
    
private:
    DFAState charType(char);                       //返回字符的类型，如：空格，数字，字母等
    char getNextChar();                            //获取到下一个字符
    void backToLastChar();                         //跳到上一个字符
    TokenType returnTokenType(string s);           //根据字符串返回Token类型
    void printToken();                             //将词法分析好的Token输出到文件Token.txt中
    string sourseString;                           //获取源代码的字符串
    int charIndex;                                 //配合getNextChar()，指定要取的字符位置
    string str;                                    //在分析过程中保存Token对应的串
    bool commentFlag;                              //标注注释开始的标志
    int lineCount = 0;                             //对行号计数，每次获取到'\n'就自增
    static int count;                              //tokenList数组下标
    vector<Token> tokenList;                       //保存的Token序列
};


Scanner :: Scanner()
{
    scanSuccess = true;
    charIndex = 0;
    str = "";
    commentFlag = true;
    sourseString = "";
    lineCount = 0;
}

void Scanner :: scan()
{
    cout << "Scanner starting..." << endl;
    bool doubleSym = false;
    getSourseFile("sourseFile.txt");
    int state = START;
    lineCount = 0;
    char ch;
    while (state < 6) {
        ch = getNextChar();
        if ('\0' == ch)
        {
            Token t;
            t.lineNo = lineCount;
            t.tokenString = "";
            t.tokenType = ENDFILE;
            tokenList.push_back(t);
            break;
        }
        
        if (START == state)
        {
            state = charType(ch);
            if (state != START) {
                str += ch;
            }
        }
        else if (INNUM == state)
        {
            state = charType(ch);
            if (state != INNUM) {
                state = DONE;
            }
            else
                str += ch;
        }
        else if (INID == state)
        {
            state = charType(ch);
            if (state != INID) {
                state = DONE;
            }
            else str += ch;
        }
        else if (INDBSYM == state)
        {
            if ('=' == ch) {
                str += ch;
                doubleSym = true;
            }
            else
                doubleSym = false;
            state = DONE;
        }
        if (DONE == state) {
            int tp = 0;
            if ('\r' == ch)
                tp = 1;
            Token t;
            t.lineNo = lineCount - tp;
            t.tokenString = str;
            t.tokenType = returnTokenType(str);
            tokenList.push_back(t);
            if (ERROR == t.tokenType)
                scanSuccess = false;
            int lastState = charType(str[str.length()-1]);
            if (lastState == INNUM || lastState == INID ||
                (lastState == INDBSYM && doubleSym == false))
                backToLastChar();
            str = "";
            state = START;
            if (doubleSym == true)
                doubleSym = false;
        }
        
    }
    if (scanSuccess == false) {
        cout << "Scannner error" << endl;
    }
    else
        cout << "Scanner success!" << endl;
    printToken();
}

Token Scanner :: getTokenAt(int tokenIndex)
{
    Token token;
    token.lineNo = lineCount;
    token.tokenString = "";
    token.tokenType = ENDFILE;
    if (tokenIndex < tokenList.size()) {
        token = tokenList.at(tokenIndex++);
    }
    return token;
}

void Scanner :: getSourseFile(string path)
{
    ifstream fin(path.c_str());
    string temp;
    sourseString = "";
    
    while (getline(fin, temp, '\r')) {
        sourseString += temp;
        sourseString += '\r';
    }
    fin.close();
    charIndex = 0;
}

void Scanner :: deleteComments()
{
    cout << "Delete comments..." << endl;
    ofstream fout_Sourse("sourseFile.txt");
    int state = 1;
    char ch;
    while (state < 6) {
        ch = getNextChar();
        if('\0' == ch)
            break;
        if (1 == state) {
            if ('/' == ch) {
                state = 2;
            }
            else
            {
                state = 1;
                fout_Sourse << ch;
            }
        }
        else if (2 == state)
        {
            if ('*' == ch) {
                state = 3;
                commentFlag = false;
            }
            else
            {
                state = 1;
                fout_Sourse << '/' << ch;
            }
        }
        else if (3 == state)
        {
            if ('*' == ch) {
                state = 4;
            }
            else
            {
                state = 3;
            }
        }
        else if (4 == state)
        {
            if ('*' == ch) {
                state = 4;
            }
            else if ('/' == ch)
                state = 5;
            else
            {
                state = 3;
            }
        }
        if (5 == state) {
            commentFlag = true;
            state = 1;
        }
    }
    if(!commentFlag) {
        cout << "Error! The comment has no end!" << endl;
        scanSuccess = false;
    }
    else
        cout << "Delete comment success!" << endl;
}

TokenType Scanner :: returnTokenType(string s)
{
    TokenType t;
    if (s == "else") {
        t = ELSE;
    }
    else if (s == "if")
        t = IF;
    else if (s == "int")
        t = INT;
    else if (s == "return")
        t = RETURN;
    else if (s == "void")
        t = VOID;
    else if (s == "while")
        t = WHILE;
    else if (s == "+")
        t = PLUS;
    else if (s == "-")
        t = MINUS;
    else if (s == "*")
        t = TIMES;
    else if (s == "/")
        t = OVER;
    else if (s == "<")
        t = LT;
    else if (s == "<=")
        t = LEQ;
    else if (s == ">")
        t = GT;
    else if (s == ">=")
        t = GEQ;
    else if (s == "==")
        t = EQ;
    else if (s == "!=")
        t = NEQ;
    else if (s == "=")
        t = ASSIGN;
    else if (s == ";")
        t = SEMI;
    else if (s == ",")
        t = COMMA;
    else if (s == "(")
        t = LPAREN;
    else if (s == ")")
        t = RPAREN;
    else if (s == "[")
        t = LMBRACKET;
    else if (s == "]")
        t = RMBRACKET;
    else if (s == "{")
        t = LBBRACKET;
    else if (s == "}")
        t = RBBRACKET;
    else if (s == "/*")
        t = LCOMMENT;
    else if (s == "*/")
        t = RCOMMENT;
    else if (2 == charType(s[s.length() - 1]))
        t = NUM;
    else if (3 == charType(s[s.length() - 1]))
        t = ID;
    else t = ERROR;
    
    return t;
    
}

DFAState Scanner :: charType(char c)
{
    if (' ' == c || '\n' == c || '\t' == c || '\r' == c) {
        return START;
    }
    else if (c >= '0' && c <= '9')
        return INNUM;
    else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return INID;
    else if (c == '<' || c == '>' || c == '=' || c == '!')
        return INDBSYM;
    else return DONE;
}

char Scanner :: getNextChar()
{
    if (charIndex < sourseString.length()) {
        char ch = sourseString[charIndex];
        charIndex++;
        if ('\r' == ch) {
            lineCount++;
        }
        return ch;
    }
    else
        return '\0';
}

void Scanner :: backToLastChar()
{
    if (charIndex > 0) {
        char ch = sourseString[charIndex - 1];
        charIndex--;
        if ('\r' == ch) {
            lineCount--;
        }
    }
}

void Scanner :: printToken()
{
    ofstream fout_Token("Token.txt");
    ifstream fin("sourseFile.txt");
    string temp;
    int lineCount = 0;
    int index = 0;
    while (getline(fin, temp, '\r')) {
        fout_Token << lineCount << ": ";
        fout_Token << temp << endl;
        while (index  < tokenList.size()) {
            Token t = tokenList.at(index);
            if (lineCount == t.lineNo) {
                fout_Token << "     " << lineCount <<":   [";
                index++;
                int width = 10;
                string headS = " ";
                if (t.tokenType >= 1 && t.tokenType <= 6) {
                    string tp = "";
                    for (int i = 0; i < width - t.tokenString.length(); i++) {
                        tp += " ";
                    }
                    fout_Token << "keyWord]: " << headS << t.tokenString << " " << tp << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                else if (t.tokenType >= 7 && t.tokenType <= 27)
                {
                    string tp = "";
                    for (int i = 0; i < width - t.tokenString.length(); i++) {
                        tp += " ";
                    }
                    fout_Token << "symbols]: " << headS << t.tokenString << " " << tp << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                else if (t.tokenType == 28)
                {
                    string tp = "";
                    for (int i = 0; i < width - t.tokenString.length(); i++) {
                        tp += " ";
                    }
                    fout_Token << "    NUM]: " << headS << t.tokenString << " " << tp << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                else if (t.tokenType == 29)
                {
                    string tp = "";
                    for (int i = 0; i < width - t.tokenString.length(); i++) {
                        tp += " ";
                    }
                    fout_Token << "     ID]: " << headS << t.tokenString << " " << tp << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                else if (t.tokenType == 30)
                {
                    string tp = "";
                    for (int i = 0; i < width - t.tokenString.length(); i++) {
                        tp += " ";
                    }
                    fout_Token << "  error]: " << headS << t.tokenString << " " << tp << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                else if (t.tokenType == ENDFILE)
                {
                    fout_Token << "     " << lineCount << ": " << t.tokenString << " " << "[" << tokenTypeString[t.tokenType] << "]" <<endl;
                }
                
            }
            if (lineCount < t.lineNo) {
                break;
            }
        }
        lineCount++;
    }
    fin.close();
    fout_Token.close();
}


#endif /* defined(__C_Minus__Scanner__) */
