//
//  SqQueue.h
//  SqQueue
//
//  Created by 木木同学 on 15/5/8.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SqQueue_SqQueue_h
#define SqQueue_SqQueue_h

#include "Header.h"

//顺序队列类模板
template <class ElemType>
class SqQueue {
//顺序队列实现的数据成员
protected:
    int maxSize;                                        //最大元素个数
    int count;                                          //队列中的元素个数
    ElemType *elems;                                     //队列中的元素

//辅助成员函数
    void Init(int size);                                //队列初始化
    bool Full();                                        //判断队列是否已满
    
//抽象数据类型方法声明及重载编译系统默认方法声明
public:
    SqQueue(int size = DEFAULT_SIZE);                                          //构造函数模板
    virtual ~SqQueue();                                 //析构函数
    int Length() const;                                 //求队列长度
    void Clear();                                       //清空队列
    void Traverse(void (*visit)(const ElemType &)) const;//遍历队列所有元素
    bool Empty() const;                                 //判断队列是否为空
    StatusCode OutQueue(ElemType &e);                   //出队
    StatusCode InQueue(const ElemType &e);              //进队
    StatusCode GetHead(ElemType &e) const;              //取队头
    SqQueue(const SqQueue<ElemType> &copy);             //复制构造函数
    SqQueue<ElemType> &operator=(const SqQueue<ElemType> &copy);
                                                        //重载赋值运算符
};

//顺序队列类模板的实现部分
template <class ElemType>
void SqQueue<ElemType>::Init(int size) {
//操作结果：初始化队列
    count = 0;
    maxSize = size;
    if (elems != NULL) {
        delete []elems;
    }
    elems = new ElemType[maxSize];
    
}

template <class ElemType>
bool SqQueue<ElemType>::Full() {
//操作结果：判断队列是否已满，如果满，返回true，否则返回false
    return count == maxSize;
}

template <class ElemType>
SqQueue<ElemType>::SqQueue(int size) {
//操作结果：构造一个最大元素个数为size的空队列
    elems = NULL;
    Init(size);
}

template <class ElemType>
SqQueue<ElemType>::~SqQueue() {
//操作结果：销毁队列
    delete [] elems;
}

template <class ElemType>
int SqQueue<ElemType>::Length() const {
//操作结果：返回队列的元素个数
    return count;
}

template <class ElemType>
bool SqQueue<ElemType>::Empty() const {
//操作结果：判断队列是否为空，若为空返回true，否则返回false
    return count == 0;
}

template <class ElemType>
void SqQueue<ElemType>::Clear() {
//操作结果：清空队列
    count = 0;
}

template <class ElemType>
void SqQueue<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
//操作结果：从队头到队尾依次对队列的每个元素调用函数（＊visit）
    for (int curPosition = 1; curPosition <= Length(); curPosition++) {
        (*visit)(elems(curPosition - 1));
    }
}

template <class ElemType>
StatusCode SqQueue<ElemType>::OutQueue(ElemType &e) {
//操作结果：出队列
    if (Empty()) {
        return UNDER_FLOW;
    }
    else {
        e = elems[0];
        for (int curPosition = 1; curPosition < Length(); curPosition++) {
            elems[curPosition - 1] = elems[curPosition];
        }
        count--;
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SqQueue<ElemType>::InQueue(const ElemType &e) {
//操作结果：进队
    if (Full()) {
        return OVER_FLOW;
    }
    else {
        elems[count] = e;
        count++;
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SqQueue<ElemType>::GetHead(ElemType &e) const{
//操作结果：获得队头
    if (Empty()) {
        return UNDER_FLOW;
    }
    else {
        e = elems[0];
        return SUCCESS;
    }
}

template <class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy) {
//操作结果：复制构造函数
    elems = NULL;
    Init(copy.maxSize);
    count = copy.count;
    for (int curPosition = 1; curPosition <= copy.Length(); curPosition++) {
        elems[curPosition - 1] = copy.elems[curPosition - 1];
    }
}

template <class ElemType>
SqQueue<ElemType>& SqQueue<ElemType>::operator=(const SqQueue<ElemType> &copy) {
    if (&copy != this) {
        Init(copy.maxSize);
        count = copy.count;
        for (int curPosition = 1; curPosition <= copy.Length(); curPosition++) {
            elems[curPosition - 1] = copy.elems[curPosition - 1];
        }
    }
    return *this;
}













































#endif
