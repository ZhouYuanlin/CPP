//
//  Game21Point.h
//  21点
//
//  Created by 木木同学 on 15/2/20.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef _1__Game21Point_h
#define _1__Game21Point_h

#include "card.h"

#define LEN_OF_MAX_NAME 21         //最大姓名长度

//21点游戏类Game21Point声明
class Game21Point {
private:
    Card deck[52];                 //一副扑克牌
    int dealPos;                   //发牌位置
    Card hands[8][21];             //hand[0]存储庄家手中的扑克牌，hand[1~7]存储各位玩家手中的扑克牌
    
    int numOfCard[8];              //庄家(numOfCard[0])及玩家(numOfCard[1~7]手中的扑克牌数)
    char name[8][LEN_OF_MAX_NAME]; //庄家与玩家姓名
    int numOfPlayer;               //玩家人数
    
//辅助函数
    void Shuffle();                //洗牌
    int GetTotalScore(Card hand[21], int n);
                                   //返回一手扑克牌的总分值
    void ShowStatus(int num, bool hideFirstCardAndTotalScore = false);
                                   //显示庄家或玩家的当前状态
    Card DealOneCard();            //发一张扑克牌
    
public:
    Game21Point();                 //无参构造函数
    virtual ~Game21Point() {};     //析构函数
    void Game();                   //运行游戏
};

//操作结果：初始化扑克牌，发牌位置，庄家与玩家手中的扑克牌数
Game21Point::Game21Point() {
    int curPos = 0;                                      //当前扑克牌位置
    for (int suitPos = 0; suitPos < 4; suitPos++) {
        for (int rankPos = 1; rankPos <= 13; rankPos++) {
            deck[curPos].suit = (SuitType)suitPos;       //花色
            deck[curPos].rank = (RankType)rankPos;       //面值
            curPos++;
        }
    }
    cout << "多少人加入游戏？(1~7):";
    cin  >> numOfPlayer;                                 //玩家人数
    dealPos = 0;                                         //发牌位置置零
    int i;                                               //临时变量
    for (i = 0; i <= numOfPlayer; i++) {
        numOfCard[i] = 0;                                //庄家及玩家手中的扑克牌数置零
    }
    strcpy(name[0], "庄家");                              //初始化庄家姓名
    for (i = 1; i <= numOfPlayer; i++) {
        cout << "输入第" << i << "位玩家的姓名：";
        cin >> name[i];                                  //初始化玩家姓名
    }
    cout << "游戏开始" << endl;
}

//操作结果：洗牌，将扑克牌混在一起以便产生一种随机的排列组合
void Game21Point::Shuffle() {
    for (int curPos = 51; curPos > 0; curPos--) {
        srand((unsigned)time(NULL));
        int pos = rand() % (curPos + 1);                 //产生0~curPos之间的随机数
        //交换deck[pos]与deck[curPos]
        struct Card temp;
        temp = deck[curPos];
        deck[curPos] = deck[pos];
        deck[pos] = temp;
    }
}

//操作结构：返回一手扑克牌的总分值
int Game21Point::GetTotalScore(Card hand[21], int n) {
    int pos;                                             //临时变量
    int totalScore = 0;                                  //总分值置零
    for (pos = 0; pos < n; pos++) {
        if (hand[pos].rank == ACE) totalScore += 11;     //A的分值为11
        else if(hand[pos].rank > TEN) totalScore += 10;  //J,Q,K的分值为10
        else totalScore += (int)hand[pos].rank;          //TWO~TEN的分值为2～10
    }
    
    for (pos = 0; totalScore > 21 && pos < n; pos++) {
        if (hand[pos].rank == ACE) {
            totalScore -= 10;                            //总分大于21则A由11改为1分
        }
    }
    return totalScore;                                   //返回总分
}

//操作结果：当num＝0时，显示庄家当前状态，当num>0时，显示第num个玩家的当前状态
//当hideFirstCardAndTotalScore为真时，将隐藏首张扑克牌与总分，否则将显示首张扑克牌与总分
void Game21Point::ShowStatus(int num, bool hideFirstCardAndTotalScore) {
    cout << name[num] << ":" << "  ";                            //显示庄家或玩家姓名
    if (hideFirstCardAndTotalScore) {
        cout << "<隐藏>" << "  ";                                 //隐藏首张扑克牌
    }
    else cout << hands[num][0] << "  ";                          //显示首张扑克牌
    for (int i = 1; i < numOfCard[num]; i++) {
        cout << hands[num][i] << "  ";                           //显示庄家或玩家手中除第一张的扑克牌
    }
    if (!hideFirstCardAndTotalScore) {
        cout << "总分值" << GetTotalScore(hands[num],numOfCard[num]);
        //显示庄家或玩家总分
    }
    cout << endl;
    if (GetTotalScore(hands[num], numOfCard[num]) > 21) {
        cout << name[num] << "引爆！" << endl;
    }
}

//操作结果：发一张扑克牌
Card Game21Point::DealOneCard() {
    return deck[dealPos++];
}

//操作结果：运行游戏
void Game21Point::Game() {
    Shuffle();                                            //洗牌
    int i,j;                                              //临时变量
    
    for (i = 0; i < 2; i++) {
        hands[0][numOfCard[0]++] = DealOneCard();         //为庄家发两张扑克牌
    }
    ShowStatus(0, true);                                  //显示庄家状态，隐藏首张扑克牌与总分
    
    for (i = 1; i <= numOfPlayer; i++) {
        for (j = 0; j < 2; j++) {
            hands[i][numOfCard[i]++] = DealOneCard();     //为玩家i发两张扑克牌
        }
        ShowStatus(i);                                    //显示玩家i
    }
    cout << endl;
    
    for (i = 1; i <= numOfPlayer; i++) {                  //依次向玩家发额外的牌
        char jud;
        cout << name[i] << ",你想再要一张牌吗？(y or n)" << endl;
        cin  >> jud;
        if (toupper(jud) == 'Y') {
            hands[i][numOfCard[i]++] = DealOneCard();     //为玩家i发一张扑克牌
            ShowStatus(i);                                //显示玩家i
        }
    }
    
    ShowStatus(0);                                        //显示庄家
    while (GetTotalScore(hands[0], numOfCard[0]) <= 16) { //庄家总分小等于16，必须再拿牌
        hands[0][numOfCard[0]++] = DealOneCard();         //为庄家发1张扑克牌
        ShowStatus(0);                                    //显示庄家
    }
    cout << endl;
    
    if (GetTotalScore(hands[0], numOfCard[0]) > 21) {     //庄家引爆，没有引爆的所有人赢
        for (i = 1; i <= numOfPlayer; i++) {              //依次查看每位玩家
            if (GetTotalScore(hands[i], numOfCard[i]) <= 21) {
                cout << name[i] << ",恭喜你，你赢你！" << endl;
                //玩家没有引爆
            }
            else {                                        //玩家引爆
                cout << name[i] << ",对不起，你输了！" << endl;
            }
        }
    }
    else {                                                //庄家没有引爆
        for (i = 1; i <= numOfPlayer; i++) {
            if ((GetTotalScore(hands[i], numOfCard[i]) <= 21)
                //为引爆
                && (GetTotalScore(hands[i], numOfCard[i]) > GetTotalScore(hands[0], numOfCard[0]))) {
                //总分比庄家大
                cout << name[i] << ",恭喜你，你赢了！" << endl;
            }
            else if (GetTotalScore(hands[i], numOfCard[i]) == GetTotalScore(hands[0], numOfCard[0])) {
                //总分与庄家持平
                cout << name[i] << ",唉,你打平局了！" <<endl;
            }
            else {                                        //玩家引爆或总分比庄家小，玩家输
                cout << name[i] << ",对不起，你输了！" << endl;
            }
        }
    }
}
#endif
