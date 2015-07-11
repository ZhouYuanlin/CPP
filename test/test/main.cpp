//
//  main.cpp
//  test
//
//  Created by 木木同学 on 15/5/28.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include <iostream>
using namespace std;
typedef double wages;

int main(int argc, const char * argv[]) {
    // insert code here...
    wages d1 = 13.0;
    using mm = wages;
    
    mm d2 = 4.33;
    
    decltype(d1) d3 = d2;
    
    cout << d1 << " " << d2 << " " << d3 << endl;
    
    return 0;
}
