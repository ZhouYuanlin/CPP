//
//  main.cpp
//  SimpleLinkList
//
//  Created by 木木同学 on 15/4/22.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
#include "SimpleLinkList.h"
using namespace std;
int main(int argc, const char * argv[]) {
    
    SimpleLinkList<int> la, lb, lc;
    for (int curPosition = 1; curPosition <= 10; curPosition++) {
        la.Insert(la.Length()+1, (curPosition+curPosition/3));
        int e;
        la.GetElem(curPosition, e);
        cout << e << " ";
    }
    cout<<endl;
    for (int curPosition = 1; curPosition <= 15; curPosition++) {
        lb.Insert(lb.Length()+1, (curPosition+curPosition/5));
        int e;
        lb.GetElem(curPosition, e);
        cout << e << " ";
    }
    cout << endl;
    
    MergeList(la, lb, lc);
    
    Reverse(lc);
    
    for (int curPosition = 1; curPosition <= lc.Length(); curPosition++) {
        int e;
        lc.GetElem(curPosition, e);
        cout << e << " ";
    }
    cout << endl;
        return 0;
}
