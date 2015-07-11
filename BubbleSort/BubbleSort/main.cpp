//
//  main.cpp
//  BubbleSort
//
//  Created by 木木同学 on 15/2/18.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "Header.h"

const int SIZE = 6;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    DataList<int> list(SIZE);
    
    list.InPut();
    cout << "排序前：" << endl;
    list.Show();
    cout << "排序后：" << endl;
    list.SelectSort();
    list.Show();
    
    return 0;
}
