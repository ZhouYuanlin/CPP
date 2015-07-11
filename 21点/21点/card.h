//
//  card.h
//  21点
//
//  Created by 木木同学 on 15/2/20.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef _1__card_h
#define _1__card_h

#include <iostream>
#include <time.h>
using namespace std;


typedef enum {        //扑克牌的面值：ACE(),TWO(2)~TEN(10),JACK(J),QUEEN(Q),KING(K)
    ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING
} RankType;

typedef enum {        //扑克牌的花色：CLUBS(梅花♣️),DIAMONDS(方块♦️),HEARTS(红桃♥️),SPADES(黑桃♠️)
    CLUBS,DIAMONDS,HEARTS,SPADES
} SuitType;


struct Card {         //扑克牌结构体
    RankType rank;    //扑克牌面值
    SuitType suit;    //扑克牌花色
};

//操作结果：重载<<运算符
ostream& operator << (ostream& outStream, const Card &card) {
    //输出面值
    if (card.rank == ACE) cout << 'A';                        //ACE表示A
    else if (card.rank == JACK) cout << 'J';                  //JACK表示J
    else if (card.rank == QUEEN) cout << 'Q';                 //QUEEN表示Q
    else if (card.rank == KING) cout << 'L';                  //KING表示K
    else cout << (int)card.rank;                              //(int)card.rank为分值
    
    //输出花色
    if (card.suit == CLUBS) cout << "梅花♣️";                  //CLUBS表示梅花♣️
    else if (card.suit == DIAMONDS) cout << "方块♦️";          //DIAMONDS表示方块♦️
    else if (card.suit == HEARTS) cout << "红桃♥️";            //HEARTS表示红桃♥️
    else if (card.suit == SPADES) cout << "黑桃♠️";            //SPADES表示黑桃♠️
    
    return outStream;
}

#endif
