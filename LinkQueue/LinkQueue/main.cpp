//
//  main.cpp
//  LinkQueue
//
//  Created by 木木同学 on 15/5/7.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "LinkQueue.h"

using namespace std;

void yanghuiTriangle(int n);

int main(int argc, const char * argv[]) {
    // insert code here...
    yanghuiTriangle(5);
    return 0;
}

void yanghuiTriangle(int n)
//操作结果：显示三角形的第1行～第n行
{
    LinkQueue<int> q;
    int s, t;
    
    q.InQueue(1);
    q.InQueue(1);                                 //存储杨辉三角形的第一行的两个元素值
    
    cout << 1 << "\t" << 1;                       //显示杨辉三角的第一行
    for (int i = 2; i <= n; i++) {
        //依次显示杨辉三角形的第2行～第n行
        cout << endl;
        q.InQueue(1);                             //第i行第1个元素值为1
        cout << 1 << "\t";                        //显示第i行第1个元素值
        q.OutQueue(s);                            //取出第i－1行第1个元素
        for (int j = 2; j <= i; j++) {
            q.OutQueue(t);                        //取出第i－1行第j个元素
            q.InQueue(s+t);                       //s+t为第i行第j个元素的值
            cout << s+t << "\t";                  //显示第i行第j个元素的值
            s = t;
        }
        q.InQueue(1);                             //第i行第i+1个元素的值为1
        cout << 1;
    }
    cout << endl;
}