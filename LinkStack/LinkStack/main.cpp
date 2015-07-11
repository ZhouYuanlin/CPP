//
//  main.cpp
//  LinkStack
//
//  Created by 木木同学 on 15/5/6.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "LinkStack.h"


using namespace std;
bool Match(char *s);
int main(int argc, const char * argv[]) {
    // insert code here...
    char s[50] = "{4+[5*(6-1)+(2+3)*3]+[8*(9-2)]}*(3+2)";
    cout << Match(s) << endl;
    return 0;
}

bool Match(char *s) {
    //操作结果：判别用字符串s表示的表达式中大、中、小括号是否配对出现
    LinkStack<char> tmpS;                                      //临时栈
    char tmpCh;                                                //临时字符
    
    for (int i = 0; i < strlen(s); i++) {
        //从左向右依次扫描各字符
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            //如果读入的字符为“（”、“［”、“｛”，则进栈
            tmpS.Push(s[i]);
        }
        else if (s[i] == ')') {
            //读入的字符为“）”
            if (tmpS.Empty()) {
                //如果栈空则左右括号不匹配
                return false;
            }
            else if(tmpS.Top(tmpCh), tmpCh == '(') {
                //如果栈顶的括号是“（”，则出栈
                tmpS.Pop(tmpCh);
            }
            else return false;                                 //否则不匹配（这时栈顶为‘［’或‘｛’）
        }
        else if(s[i] == ']') {
            //读入的字符为“］”
            if (tmpS.Empty()) {
                //如果栈空则左右括号不匹配
                return false;
            }
            else if (tmpS.Top(tmpCh), tmpCh == '[') {
                //如果栈顶的括号是“］”，则出栈
                tmpS.Pop(tmpCh);
            }
            else return false;                                 //否则不匹配（这时栈顶为‘｛’或‘（’）
        }
        else if (s[i] == '}') {
            //读入的字符为“｝”
            if (tmpS.Empty()) {
                //如果栈空则左右括号不匹配
                return false;
            }
            else if (tmpS.Top(tmpCh), tmpCh == '{') {
                //如果栈顶的括号是“｝”，则出栈
                tmpS.Pop(tmpCh);
            }
            else return false;                                 //否则不匹配（这时栈顶为‘［’或‘(’）
        }
    }
    if (tmpS.Empty()) {
        //栈空着左右括号匹配
        return true;
    }
    else return false;                                         //栈不空则左右括号不匹配
    
}
