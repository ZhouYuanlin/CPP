//
//  main.cpp
//  SqStack
//
//  Created by 木木同学 on 15/4/28.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "SqStack.h"

using namespace std;
void Reverse();

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Reverse();
    return 0;
}

void Reverse() {
    int n,e;
    SqStack<int> tmps;
    cout << "请输入整数n" << endl;
    cin >> n;
    while (n<=0) {
        cout << "n不能为负数或者0，请重新输入整数n" << endl;
        cin >> n;
    }
    cout << "请输入" << n << "个整数" << endl;
    for (int i = 0; i < n; i++) {
        cin >> e;
        tmps.Push(e);
    }
    cout << "按相反顺序输出" << endl;
    while (tmps.Empty() != true) {
        tmps.Pop(e);
        cout << e<< endl;
    }
}
