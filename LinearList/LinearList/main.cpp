//
//  main.cpp
//  LinearList
//
//  Created by 木木同学 on 15/4/11.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "SqList.h"


using namespace std;



int main(int argc, const char * argv[]) {
    // insert code here...
    
    SqList<int> list1(10);
    SqList<int> list2(10);
    SqList<int> list3(10);
    
    
    
    for (int position = 1; position <= 10; position++) {
        list1.Insert(position, ((position+1)*3 - 1)/2);
    }
    
    Adjust(list1);
    
    for (int position = 1; position <= list1.Length(); position++) {
        
        int e;
        list1.GetElem(position, e);
        cout << e <<" ";
    }

    
    cout << endl;
    for (int position = 1; position <= 10; position++) {
        list2.Insert(position, ((position-1)*4 + 1)/3);
        int e;
        list2.GetElem(position, e);
        cout << e << " ";
    }
    cout << endl;
    
    
    Different(list1, list2, list3);
    
    
    
    
    for (int position = 1; position <= list3.Length(); position++) {
        int e;
        list3.GetElem(position, e);
        
        cout << e << " ";
        
    }
    cout << endl;

    
    
    
    
    
    
    return 0;
}


