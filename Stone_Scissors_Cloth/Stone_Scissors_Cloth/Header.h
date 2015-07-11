//
//  Header.h
//  Stone_Scissors_Cloth
//
//  Created by 木木同学 on 15/2/18.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef Stone_Scissors_Cloth_Header_h
#define Stone_Scissors_Cloth_Header_h

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

//猜拳类
class Finger_Guessing_Game
{
public:
    Finger_Guessing_Game()                               //构造函数
    {
        srand((unsigned)time(NULL));                     //初始化种子，以系统当前时间作为种子
        m_cJud = 'n';
    }
    
    virtual ~Finger_Guessing_Game() {};                   //析构函数
    void GuessFist(void);                                //猜拳函数
    
private:
    int m_iCNum;
    int m_iPNum;
    char m_cJud;
};


void Finger_Guessing_Game :: GuessFist(void)
{
    const char *num[] = {"✊", "✌️", "👋"};
    
    do
    {
        cout << "请输入✊（0）、✌️（1）、👋（2）" << endl;
        cin  >> m_iPNum;
        if (m_iPNum != 0 && m_iPNum != 1 && m_iPNum != 2) {
            cout << "你输入的数字有误,请重新输入！" << endl;
            continue;
        }
        cout << "你是：" << num[m_iPNum] << endl;
        m_iCNum = rand() % 3;
        cout << "电脑是：" << num[m_iCNum] << endl;
        if (m_iPNum == m_iCNum)
        {
            cout << "平局！" << endl;
        }
        else if((m_iPNum == 1 && m_iCNum == 0)  || (m_iPNum == 2 && m_iPNum == 1)
                || (m_iPNum == 0 && m_iCNum == 2))
        {
        
            cout << "你输了！" << endl;
        }
        else  cout << "你赢了！" << endl;
        cout << "请问你还要继续玩吗？y or n?" << endl;
        cin  >> m_cJud;
    }
    while(toupper(m_cJud) == 'Y');
    
}

#endif
