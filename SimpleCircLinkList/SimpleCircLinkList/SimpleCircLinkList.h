//
//  SimpleCircLinkList.h
//  SimpleCircLinkList
//
//  Created by 木木同学 on 15/4/24.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SimpleCircLinkList_SimpleCircLinkList_h
#define SimpleCircLinkList_SimpleCircLinkList_h

#include "Header.h"
#include "Node.h"


//简单循环链表类模板
template <class ElemType>
class SimpleCircLinkList {
protected:
//循环实现的数据成员：
    Node<ElemType> *head;                                        //头结点指针
    mutable int curPosition;                                     //当前位置序号
    mutable Node<ElemType> *curPtr;                              //指向当前位置指针
    int count;                                                   //元素个数
    
    
//辅助函数模板：
    Node<ElemType> * GetElemPtr(int position) const;             //返回指向第position个结点的指针
    
    void Init();                                                 //初始化线性表
    
public:
//抽象数据类型方法声明及重载编译系统默认方法声明：
    SimpleCircLinkList();                                        //无参构造函数模板
    virtual ~SimpleCircLinkList();                               //析构函数模板
    int Length() const;                                          //求线性表长度
    bool Empty() const;                                          //判断线性表是否为空
    void Clear();                                                //清空线性表
    void Traverse(void (* visit)(const ElemType &)) const;       //遍历线性表
    StatusCode GetElem(int position, ElemType &e) const;         //求指定位置的元素
    StatusCode SetElem(int position, const ElemType &e);         //设置指定位置的元素值
    StatusCode Delete(int position, ElemType &e);                //删除元素
    StatusCode Insert(int position, const ElemType &e);          //插入元素
    SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy);//复制构造函数模板
    SimpleCircLinkList<ElemType> &operator=(const SimpleCircLinkList<ElemType> &copy);
                                                                 //重载赋值运算符
};


template <class ElemType>
Node<ElemType> * SimpleCircLinkList<ElemType>::GetElemPtr(int position) const {
//操作结果：返回指向第position个结点的指针
    
    while (curPosition != position) {
        curPosition = (curPosition +1) % (Length() + 1);
        curPtr = curPtr -> next;
    }
    return curPtr;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Init() {
//操作结果：初始化线性表
    head = new Node<ElemType>;                                   //构造头指针
    head -> next = head;                                         //空循环链表的头指针结点后继为头结点本事
    count = 0;
    curPtr = head;
    curPosition = 0;
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList() {
//操作结果：构造一个空链表
    Init();
}

template <class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList() {
//操作结果：销毁线性表
    Clear();                                                     //清空线性表
    delete head;                                                 //释放头结点
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Length() const {
//操作结果：返回线性表元素个数
       return count;
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const {
//操作结果：如果线性表为空，则返回true，否则返回false
    return  head -> next == head;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Clear() {
//操作结果：清空线性表
    ElemType tmpPtr;                                             //临时元素值
    while (Length() > 0) {
        //线性表非空，则删除第一个元素
        Delete(1, tmpPtr);
    }
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
//操作结果：依次对线性表的每个元素调用函数（＊visit）
    for (Node<ElemType> *tmpPtr = head -> next; tmpPtr != head; tmpPtr = tmpPtr -> next) {
        //用tmpPtr依次指向每个元素
        (* visit)(tmpPtr -> data);                               //对线性表的每个元素调用函数（＊visit）
    }
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::GetElem(int position, ElemType &e) const {
//操作结果：当线性表在第position个元素时，用e返回其值，返回ENTRY_FOUND
//否则返回NOT_PRESENT
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                           //取出指向第position个结点的指针
        e = tmpPtr -> data;                                      //用e返回第position个元素的值
        return ENTRY_FOUND;
    }
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType &e) {
//操作结果：将线性表的第position个位置的元素赋值为e
//position的取值范围为1<=position<=Length()
//position合法返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                            //取出指向第position个元素的指针
        tmpPtr -> data = e;                                       //设置第position个元素的值
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::Delete(int position, ElemType &e) {
//操作结果：删除线性表中的第position个位置的元素，并用e返回其值
//position的取值范围为1<=position<=Length()
//position合法返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr, *nextPtr;
        tmpPtr = GetElemPtr(position - 1);                        //取出第position－1个元素的指针
        nextPtr = tmpPtr -> next;                                 //nextPtr为tmpPtr的后继
        tmpPtr -> next = nextPtr -> next;                         //删除结点
        e = nextPtr -> data;                                      //用e返回删除结点元素值
        if (position == Length()) {
            curPosition = 0;
            curPtr = head;
        }
        else {
            curPosition = position;
            curPtr = tmpPtr -> next;
        }
        count--;
        
        delete nextPtr;                                           //释放被删结点
        
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::Insert(int position, const ElemType &e) {
//操作结果：在线性表的第position个位置前插入元素e
//position的取值范围为1<=position<=Length()+1
//position合法返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length() + 1) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr, *newPtr;
        tmpPtr = GetElemPtr(position - 1);                            //取出第position-1个元素的指针
        newPtr = new Node<ElemType>(e, tmpPtr -> next);               //生成新结点
        tmpPtr -> next = newPtr;                                      //将newPtr插入到链表中
        curPosition = position;
        curPtr = newPtr;
        count++;
        return SUCCESS;
    }
    
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy) {
//操作结果：重载复制构造函数模板
    int copyLength = copy.Length();                                   //copy的长度
    Init();                                                           //初始化当前线性表
    ElemType tmpPtr;
    for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
        //复制数据元素
        copy.GetElem(curPosition, tmpPtr);                            //取出第curPosition个元素
        Insert(Length() + 1, tmpPtr);                                 //将e插入到当前线性表
    }
}

template <class ElemType>
SimpleCircLinkList<ElemType> & SimpleCircLinkList<ElemType>::operator=(const SimpleCircLinkList<ElemType> &copy) {
    
    int copyLength = copy.Length();                                   //copy的长度
    Clear();                                                          //清空线性表
    ElemType tmpPtr;
    for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
        //复制数据元素
        copy.GetElem(curPosition, tmpPtr);                            //取出第curPosition个元素
        Insert(Length() + 1, tmpPtr);                                 //将e插入到当前线性表
    }
    return *this;
}






















#endif
