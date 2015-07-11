//
//  test.cpp
//  Utility
//
//  Created by 木木同学 on 15/2/21.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "Header.h"

#define NUM 280
int main(void) {
    try {
        if (NUM > 280) {
            throw Error("NUM值太大了！");
        }
        
        int a[NUM + 1][NUM + 1], b[NUM + 1][NUM + 1], c[NUM + 1][NUM + 1];
        bool isCoutinue = true;
        Timer objTimer;
        while (isCoutinue) {
            int i, j, k;
            objTimer.Reset();
            
            for (i = 1; i <= NUM; i++) {
                for (j = 1; j <= NUM; j++) {
                    a[i][j] = GetRand();
                    b[i][j] = GetRand();
                }
            }
            for (i = 1; i <= NUM; i++) {
                for (j = 1; j <= NUM; j++) {
                    c[i][j] = 0;
                    for (k = 1; k <= NUM; k++) {
                        c[i][j] = c[i][j] + a[i][k] * b[k][j];
                    }
                }
            }
            cout << "用时:" << objTimer.ElapsedTime() << "毫秒。" << endl;
            cout << "是否继续";
            isCoutinue = UserSaysYes();
        }
        
    } catch (Error err) {
        err.Show();
    }
    return 0;
}
