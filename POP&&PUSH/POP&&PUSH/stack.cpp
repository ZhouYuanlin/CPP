//
//  stack.cpp
//  POP&&PUSH
//
//  Created by 木木同学 on 15/2/16.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "stack.h"
#include <iostream>
using namespace std;

//入栈操作
void Cstack::Push(int iDate)
{
    CNode *newNode = new CNode(iDate, m_pTop);
    m_pTop = newNode;
}

//出栈操作
int Cstack::Pop(void)
{
    CNode *tempNode = m_pTop;
    if (m_pTop) {
        m_pTop = m_pTop -> m_preNode;
        int tempData = tempNode -> m_iDate;
        delete tempNode;
        return tempData;
    }
    else
    {
        cout << "栈已空" << endl;
        return 0;
    }
}
