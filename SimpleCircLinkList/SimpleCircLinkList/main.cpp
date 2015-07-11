//
//  main.cpp
//  SimpleCircLinkList
//
//  Created by 木木同学 on 15/4/24.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "SimpleCircLinkList.h"
using namespace std;

void Josephus(int n, int m) {
    
    SimpleCircLinkList<int> la;                             //定义一个空循环链表
    int out, winer;
    int position = 0;                                       //报数到的人在链表中的序号
    for (int i = 1; i <= n; i++) {
        la.Insert(la.Length()+1, i);                      //建立数据域为1到n的循环链表
    }
    
    cout << "出列者：";
    
    for (int i = 1; i < n; i++) {                           //循环n－1次，让n－1个人出列
        
        for (int j = 1; j <= m; j++) {                      //从1报数到m
            
            position++;
            
            if (position > la.Length()) {
                position = 1;
            }
        }
        la.Delete(position--, out);                         //报数到m的人出列
        cout << out << " ";
    }
    cout << endl;
    
    la.GetElem(1, winer);                                   //剩下的为优胜者
    cout << "优胜者：" << winer << endl;
   
}


int main(int argc, const char * argv[]) {
    
    Josephus(8, 3);
    
    return 0;
}
