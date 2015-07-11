//
//  Header.h
//  Utility
//
//  Created by 木木同学 on 15/2/18.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef Utility_Header_h
#define Utility_Header_h

#include <iostream>                          //标准流操作
#include <string>                            //标准串和操作
#include <limits>                            //极限
#include <cmath>                             //数学函数
#include <fstream>                           //文件输入输出
#include <cctype>                            //字符处理
#include <ctime>                             //日期和时间函数
#include <cstdlib>                           //标准库
#include <cstdio>                            //标准输入输出
#include <iomanip>                           //输入输出流格式设置
#include <cstdarg>                           //支持变长函数参数
#include <cassert>                           //支持断言

using namespace std;                         //标准库包含在命名空间std中

//自定义各种状态枚举
enum StatusCode {
    SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};

#define DEFAULT_SIZE 100                     //默认元素个数
#define DEFAULT_INFINITY 1000000             //默认无穷大

//操作结果：从输入流inStream中跳过空格、换行符及制表符获取一字符
static char Getchar(istream &inStream = cin) {
    char ch;                                 //临时变量
    while ((ch = (inStream).peek() != EOF) && ((ch = (inStream).get()) == ' '
                                              || ch == '\t'));
        
    return ch;
}
    
//操作结果：当用户肯定回答（yes）时返回true；当用户否定回答时（no）返回false
static bool UserSaysYes() {
    char ch;                                 //接收用户回答字符
    bool initialResponse = true;             //初始回答为true
    
    do {                                     //循环直到用户输入恰当的回答为止
        if (initialResponse) {
            cout << "(y, n)?";
        }
        else {
            cout << "用y或n回答：";
        }
        
        ch = Getchar();
        initialResponse = false;
    } while (toupper(ch) != 'Y' && toupper(ch) != 'N');
    
    while (Getchar() !='\n');                //跳过当前行后面的字符
    
    if (toupper(ch) == 'Y') return true;
    else  return false;
    
    
}
        
//定时器类Timer
class Timer {
private:
    clock_t startTime;                       //起始时间
    
public:
    Timer() {                                //构造函数
        startTime = clock();
    }
    virtual ~Timer() {};                     //析构函数
    
    double ElapsedTime() {                   //返回已过的时间
        clock_t endTime = clock();           //结束时间
        return (double)(endTime - startTime) / (double)CLK_TCK;
                                             //返回从Timer对象启动或最后一次调用reset()后所使
                                             //用的cup时间
    }
    void Reset() { startTime = clock(); };    //重置开始时间
};

//通用异常类
class Error {
private:
    char message[DEFAULT_SIZE];     //异常信息
    
public:
    Error(char mes[] = "一般性异常！") {       //构造函数
        strcpy(message, mes);                //复制异常信息
    }
    
    virtual ~Error(void) {};                 //析构函数
    void Show() const {
        cout << message << endl;             //显示异常信息
    }
};

//操作结果：生成0～n－1之间的随机数
static int GetRand(int n) {
    srand((unsigned)time(NULL));             //设置当前时间为随机数种子
    return rand() % (n);
}

//操作结果：生成随机数
static int GetRand() {
    srand((unsigned)time(NULL));             //设置当前时间为随机数种子
    return rand();
}

//操作结果：生成期望值为expectValue泊松随机数
static int GetPoissionRand(double expectValue) {
    double x = (rand() - 1) / (double)(RAND_MAX);
                                             //x均匀分布于（0，1）
    int k = 0;
    double p = exp(-expectValue);
    double s = 0;
    
    while (s <= x) {
        s += p;
        k++;
        p = p * expectValue / k;
    }
    return k - 1;
}

//操作结果：交换e1、e2之值
template <class ElemType>
void Swap(ElemType &e1, ElemType &e2) {
    ElemType temp;
    temp = e1;
    e1 = e2;
    e2 = temp;
}

//操作结果：显示数组elem的各数据元素值
template <class ElemType>
void Display(ElemType elem[], int n) {
    for (int i = 0; i < n; i++) {
        cout << elem[i] << "  ";
    }
    cout << endl;
}

//操作结果：显示数据元素
template <class ElemType>
void Write(ElemType &e) {
    cout << e << "  ";
}
#endif
