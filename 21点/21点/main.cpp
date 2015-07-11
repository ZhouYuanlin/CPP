//
//  main.cpp
//  21点
//
//  Created by 木木同学 on 15/2/18.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#include "card.h"
#include "Game21Point.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    bool bYes = 0;                              //用于接受用户回答是否再次玩游戏
    do {
        char jud;
        Game21Point objGame;                //21点游戏对象
        objGame.Game();                     //运行游戏
        cout << "你想再玩一次吗？（y or n）" << endl;
        cin  >> jud;
        if (toupper(jud) == 'Y') {
            bYes = 1;
        }
        else
            bYes = 0;
    }
    while (bYes);
    return 0;
}
