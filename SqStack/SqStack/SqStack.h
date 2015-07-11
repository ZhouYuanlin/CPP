//
//  SqStack.h
//  SqStack
//
//  Created by 木木同学 on 15/4/28.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SqStack_SqStack_h
#define SqStack_SqStack_h

#include "Header.h"

template <class ElemType>
class SqStack {
protected:
//顺序栈的数据成员：
    int count;                                                //元素个数
    int maxSize;                                              //栈最大元素个数
    ElemType *elems;                                          //元素存储空间
    
//辅助函数模块：
    void Init(int size);                                      //初始化栈
    bool Full() const;                                        //判断栈是否已满
    
public:
//抽象数据类型方法声明及重载编译系统默认方法声明
    SqStack(int size = DEFAULT_SIZE);                         //构造函数模板
    virtual ~SqStack();                                       //析构函数模板
    int Length() const;                                       //求栈的长度
    bool Empty() const;                                       //判断栈是否为空
    void Clear();                                             //清空栈
    void Traverse(void (* visit)(const ElemType &)) const;    //遍历栈
    StatusCode Push(const ElemType &e);                       //入栈
    StatusCode Pop(ElemType &e);                              //出栈
    StatusCode Top(ElemType &e) const;                        //返回栈顶元素
    SqStack(const SqStack<ElemType> &copy);                   //复制构造函数模板
    SqStack<ElemType> & operator=(const SqStack<ElemType> &copy);
                                                              //重载赋值运算符
};


//顺序栈类模板实现类
template <class ElemType>
bool SqStack<ElemType>::Full() const {
//操作结果：如果栈满，则返回true，否则返回flase
    return count == maxSize;
}

template <class ElemType>
void SqStack<ElemType>::Init(int size) {
//操作结果：初始化栈为最大元素个数为size的空栈
    maxSize = size;                                           //最大元素个数
    
    if (elems != NULL) {
        delete []elems;                                       //释放存储空间
    }
    
    elems = new ElemType(maxSize);                            //分配存储空间
    count = 0;                                                //空栈元素个数为0
}

template <class ElemType>
SqStack<ElemType>::SqStack(int size) {
//操作结果：构造一个最大元素个数为size的空栈
    elems = NULL;                                             //未分配存储空间前，elems为空
    Init(size);                                               //初始化栈
}

template <class Elemtype>
SqStack<Elemtype>::~SqStack() {
//操作结果：销毁栈
    delete []elems;                                           //释放存储空间
}

template <class ElemType>
int SqStack<ElemType>::Length() const {
//操作结果：返回栈元素个数
    return count;
}

template <class ElemType>
bool SqStack<ElemType>::Empty() const {
//操作结果：如栈为空，则返回true，否则返回flase
    return count == 0;
}

template <class ElemType>
void SqStack<ElemType>::Clear() {
//操作结果：清空栈
    count = 0;
}

template <class ElemType>
void SqStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
//操作结果：从栈底到栈顶依次对栈的每个元素调用函数（＊visit）
    for (int curPosition = 1; curPosition < Length(); curPosition++) {
        //从栈底到栈顶依次对栈的每个元素调用函数（＊visit）
        (* visit)(elems[curPosition - 1]);
    }
}

template <class ElemType>
StatusCode SqStack<ElemType>::Push(const ElemType &e) {
//操作结果：将元素e追加到栈顶，如成功则返回SUCCESS，如栈已满则返回OVER_FLOW
    if (Full()) {
        //栈已满
        return OVER_FLOW;
    }
    else {
        elems[count++] = e;                                    //将元素e追加到栈顶
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SqStack<ElemType>::Top(ElemType &e) const {
//操作结果：如栈非空，用e返回栈顶元素，返回SUCCESS，否则返回UNDER_FLOW
    if (Empty()) {
        //栈空
        return UNDER_FLOW;
    }
    else {
        //栈非空，操作成功
        e = elems[count - 1];                                  //用e返回栈顶元素
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SqStack<ElemType>::Pop(ElemType &e) {
//操作结果：如果栈非空，删除栈顶元素，并用e返回，返回SUCCESS，否则返回UNDER_FLOW
    if (Empty()) {
        //栈空
        return UNDER_FLOW;
    }
    else {
        //栈非空，操作成功
        e = elems[--count];
        
        return SUCCESS;
    }
}

template <class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy) {
//操作结果：由栈copy构造新栈——复制构造函数模板
    elems = NULL;                                              //未分配存储空间前，elems为空
    Init(copy.maxSize);                                        //初始化新栈
    count = copy.count;                                        //复制栈元素个数
    for (int curPosition = 1; curPosition < copy.Length(); curPosition++) {
        //从栈底到栈顶对每个copy的元素进行复制
        elems[curPosition - 1] = copy.elems[curPosition - 1];
    }
}

template <class ElemType>
SqStack<ElemType> & SqStack<ElemType>::operator=(const SqStack<ElemType> &copy) {
//操作结果：将栈copy赋值给当前栈——重载赋值运算符
    if (&copy != this) {
        Init(copy.maxSize);                                        //初始化新栈
        count = copy.count;                                        //复制栈元素个数
        for (int curPosition = 1; curPosition < copy.Length(); curPosition++) {
            //从栈底到栈顶对每个copy的元素进行复制
            elems[curPosition - 1] = copy.elems[curPosition - 1];
        }
    }
    return this;
}

























#endif























