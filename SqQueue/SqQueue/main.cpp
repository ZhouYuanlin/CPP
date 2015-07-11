//
//  main.cpp
//  SqQueue
//
//  Created by 木木同学 on 15/5/8.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "SqQueue.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    SqQueue<int> a;
    a.InQueue(1);
    a.InQueue(3);
    a.InQueue(5);
    a.InQueue(7);
    a.InQueue(9);
    SqQueue<int> b(a);
    SqQueue<int> c;
    c = b;
    int d;
    c.OutQueue(d);
    cout << d << " ";
    c.OutQueue(d);
    cout << d << " ";
    c.OutQueue(d);
    cout << d << " ";
    c.OutQueue(d);
    cout << d << " ";
    c.GetHead(d);
    cout << d << " ";
    c.OutQueue(d);
    cout << d << " ";
    cout << c.OutQueue(d) << endl;
    
    
    return 0;
}
