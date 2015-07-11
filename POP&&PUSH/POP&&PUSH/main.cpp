//
//  main.cpp
//  POP&&PUSH
//
//  Created by 木木同学 on 15/2/16.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "stack.h"
#include <iomanip>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //test
    Cstack stack;
    
    //入栈
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    
    //出栈
    for (int i = 0; i < 3; i++) {
        cout << stack.Pop() << endl;
    }
    return 0;
}
