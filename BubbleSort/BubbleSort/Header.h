//
//  Header.h
//  BubbleSort
//
//  Created by 木木同学 on 15/2/18.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef BubbleSort_Header_h
#define BubbleSort_Header_h

#define MAX_SIZE 100

#include <iostream>

using namespace std;

//起泡排序模板类
template <class ElemType>
class DataList {
public:
    DataList(int sz = 6) : size(sz) {};                //构造函数
    virtual ~DataList() {};                            //析构函数
    void SelectSort(void);                             //起泡排序函数
    void InPut(void);                                  //输入数据
    void Show(void);                                    //显示数据
    
private:
    ElemType data[MAX_SIZE];
    int size;
    void Swap(const int mark1, const int mark2);       //交换data[mark1]与data[mark2]
};


//类模板实现部分
template <class ElemType>
void DataList<ElemType>::Swap(const int mark1, const int mark2) {
//操作结果：交换data[mark1]与data[mark2]
    ElemType temp;
    temp = data[mark1];
    data[mark1] = data[mark2];
    data[mark2] = temp;
}

template <class ElemType>
void DataList<ElemType>::SelectSort(void) {
//操作结果：选择排序
    for (int i = 0; i < size - 1; i++) {
        int currLargePos = i;                         //假设data[i]为当前的最小元素
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[currLargePos]) {
                currLargePos = j;
            }
        }
        
        if (currLargePos != i) {
            Swap(currLargePos, i);
        }
    }
}

template <class ElemType>
void DataList<ElemType>::InPut(void) {
//操作结果：输入数据元素值
    cout << "请输入元素个数(0~100之间)";
    cin  >> size;
    while (size >= 100 || size <= 0) {
        cout << "你输入的数越界！" << endl;
        cout << "请输入元素个数(0~100之间)";
        cin  >> size;
    }
    for (int i = 0; i < size; i++) {
        cout << "输入第" << i + 1 << "个数据元素：";
        cin  >>data[i];
    }
}

template <class ElemType>
void DataList<ElemType>::Show(void) {
//操作结果：显示数据元素值
    cout << "元素：";
    for (int i = 0; i < size; i++) {
        cout << data[i] <<" ";
    }
    cout << endl;
    cout << "元素个数" << size << endl;
}

#endif
