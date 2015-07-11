//
//  Calculator.h
//  LinkStack
//
//  Created by 木木同学 on 15/5/8.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef LinkStack_Calculator_h
#define LinkStack_Calculator_h
#ifndef LinkQueue_Calculator_h
#define LinkQueue_Calculator_h

#include "LinkStack.h"

//中缀表达式计算类
class Claculator
{
private:
    //辅助函数：
    static bool IsOperator(char ch);                               //判断字符ch是否为操作符
    static char Precede(char theta1, char theta2);                 //判断相继出现的操作符theta1和theta2的优先级
    
    static double Operate(double left, char theta,double right);   //执行运算left theta right
    
    static void Get2Operands(LinkStack<double> &opnd, double &left, double &right);
                                                                   //从栈opnd中退出两个操作数
public:
//接口方法声明：
    Calculator() {};                                               //无参构造
    virtual ~Calculator() {};                                      //析构函数
    static void Run();                                             //执行表达式求值计算
};


//类方法实现
bool Calculator::IsOperator(char ch) {
//操作结果：判断字符ch是否为操作符
    if(ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '='
      || ch == '^' || ch == '%' )
        return true;
    else return false;
}

char Calculator::Precede(char theta1, char theta2) {
    if (theta1 == '+' && theta2 == '+') return '>';
    else if (theta1 == '+' && theta2 == '-') return '>';
    else if (theta1 == '+' && theta2 == '*') return '<';
    else if (theta1 == '+' && theta2 == '/') return '<';
    else if (theta1 == '+' && theta2 == '(') return '<';
    else if (theta1 == '+' && theta2 == ')') return '>';
    else if (theta1 == '+' && theta2 == '=') return '>';
    else if (theta1 == '-' && theta2 == '+') return '>';
    else if (theta1 == '-' && theta2 == '-') return '>';
    else if (theta1 == '-' && theta2 == '*') return '<';
    else if (theta1 == '-' && theta2 == '/') return '<';
    else if (theta1 == '-' && theta2 == '(') return '<';
    else if (theta1 == '-' && theta2 == ')') return '>';
    else if (theta1 == '-' && theta2 == '=') return '>';
    else if (theta1 == '*' && theta2 == '+') return '>';
    else if (theta1 == '*' && theta2 == '-') return '>';
    else if (theta1 == '*' && theta2 == '*') return '>';
    else if (theta1 == '*' && theta2 == '/') return '>';
    else if (theta1 == '*' && theta2 == '(') return '<';
    else if (theta1 == '*' && theta2 == ')') return '>';
    else if (theta1 == '*' && theta2 == '=') return '>';
    else if (theta1 == '/' && theta2 == '+') return '>';
    else if (theta1 == '/' && theta2 == '-') return '>';
    else if (theta1 == '/' && theta2 == '*') return '>';
    else if (theta1 == '/' && theta2 == '/') return '>';
    else if (theta1 == '/' && theta2 == '(') return '<';
    else if (theta1 == '/' && theta2 == ')') return '>';
    else if (theta1 == '/' && theta2 == '=') return '>';
    else if (theta1 == '(' && theta2 == '+') return '<';
    else if (theta1 == '(' && theta2 == '-') return '<';
    else if (theta1 == '(' && theta2 == '*') return '<';
    else if (theta1 == '(' && theta2 == '/') return '<';
    else if (theta1 == '(' && theta2 == '(') return '<';
    else if (theta1 == '(' && theta2 == ')') return '=';
    else if (theta1 == '(' && theta2 == '=') return 'e';
    else if (theta1 == ')' && theta2 == '+') return '>';
    else if (theta1 == ')' && theta2 == '-') return '>';
    else if (theta1 == ')' && theta2 == '*') return '>';
    else if (theta1 == ')' && theta2 == '/') return '>';
    else if (theta1 == ')' && theta2 == '(') return 'e';
    else if (theta1 == ')' && theta2 == ')') return '>';
    else if (theta1 == ')' && theta2 == '=') return '>';
    else if (theta1 == '=' && theta2 == '+') return '<';
    else if (theta1 == '=' && theta2 == '-') return '<';
    else if (theta1 == '=' && theta2 == '*') return '<';
    else if (theta1 == '=' && theta2 == '/') return '<';
    else if (theta1 == '=' && theta2 == '(') return '<';
    else if (theta1 == '=' && theta2 == ')') return 'e';
    else if (theta1 == '=' && theta2 == '=') return '=';
}

double Claculator::Operate(double left, char theta,double right) {
    return left theta right;
}

#endif
