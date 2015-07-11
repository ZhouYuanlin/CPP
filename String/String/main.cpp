//
//  main.cpp
//  String
//
//  Created by 木木同学 on 15/5/19.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "StringTest.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    String test;
    test = "I Love JianJie!";
    String ha(test);
    cout << ha.Length() << endl;
    cout << ha[5] << endl;
    cout << (ha == test) << endl;
    Concat(test, ha);
    Write(test);
    ha = Read(cin);
    Write(ha);
    
    return 0;
}
