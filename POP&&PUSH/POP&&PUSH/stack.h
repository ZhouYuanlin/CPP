//
//  stack.h
//  POP&&PUSH
//
//  Created by 木木同学 on 15/2/16.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef __POP__PUSH__stack__
#define __POP__PUSH__stack__

#include <iostream>
using namespace std;

class Cstack;              //前项引用声明

//定义栈结点类CNode
class CNode
{
public:
    //构造函数
    CNode(int iDate, CNode *preNode)
    {
        m_iDate = iDate;
        m_preNode = preNode;
    }
    
    //将CStack类声明为友元类
    friend class Cstack;
    
private:
    int m_iDate;            //结点值
    CNode *m_preNode;       //指向前一结点的指针
    
};

//定义栈类CStack
class Cstack
{
public:
    //构造函数
    Cstack(void)
    {
        m_pTop = 0;
    }
    
    void Push(int iDate);   //入栈操作
    int Pop(void);          //出栈操作
    
private:
    CNode *m_pTop;          //头指针
};

#endif /* defined(__POP__PUSH__stack__) */
