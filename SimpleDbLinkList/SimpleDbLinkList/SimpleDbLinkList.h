//
//  SimpleDbLinkList.h
//  SimpleDbLinkList
//
//  Created by 木木同学 on 15/4/24.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SimpleDbLinkList_SimpleDbLinkList_h
#define SimpleDbLinkList_SimpleDbLinkList_h

#include "Header.h"
#include "DblNode.h"


//简单双向循环链表类模板
template <class ElemType>
class SimpleDbLinkList {
    
protected:
//循环链表实现的数据成员:
    DblNode<ElemType> *head;                   //头结点指针
    mutable int curPosition;                   //当前位置的序号
    mutable DblNode<ElemType> *curPtr;         //当前位置元素的指针
    int count;                                 //元素个数
    
//辅助函数模板
    DblNode<ElemType> * GetElemPtr(int position) const;
                                               //返回指向position个结点的指针
    void Init();                               //初始化线性表
    
public:
//抽象数据类型方法声明及重载编译系统默认方法声明：
    SimpleDbLinkList();                        //无参构造函数模板
    virtual ~SimpleDbLinkList();               //析构函数模板
    bool Empty() const;                        //判断线性表是否为空
    int Length() const;                        //求线性表长度
    void Clear();                              //清空线性表‘
    void Traverse(void (* visit)(const ElemType &)) const;
                                               //遍历线性表元素
    StatusCode GetElem(int position, ElemType &e) const;
                                               //求指定位置的元素
    StatusCode SetElem(int position, const ElemType &e);
                                               //设定指定位置的元素
    StatusCode Delete(int position, ElemType &e);
                                               //删除元素
    StatusCode Insert(int position, ElemType &e);
                                               //插入元素
    SimpleDbLinkList(const SimpleDbLinkList<ElemType> &copy);
                                               //重载复制构造函数
    SimpleDbLinkList<ElemType> & operator= (const SimpleDbLinkList<ElemType> &copy);


};


template <class ElemType>
DblNode<ElemType> * SimpleDbLinkList<ElemType>::GetElemPtr(int position) const {
    //操作结果：返回指向第position个结点的指针
    if (curPosition < position) {
        //当前位置在所查找位置之前，向后查找
        for (; curPosition < position; curPosition++) {
            curPtr = curPtr -> next;
        }
    }
    else if (curPosition > position) {
        //当前位置在所查找位置之后，向前查找
        for ( ; curPosition > position; curPosition--) {
            curPtr = curPtr -> back;
        }
    }
}

template <class ElemType>
void SimpleDbLinkList<ElemType>::Init() {
    //操作结果：初始化线性表
    head = new DblNode<ElemType>;                                   //构造头指针
    head -> next = head;                                         //空循环链表的头指针结点后继为头结点本事
    count = 0;
    curPtr = head;
    curPosition = 0;
}

template <class ElemType>
SimpleDbLinkList<ElemType>::SimpleDbLinkList() {
    //操作结果：构造一个空链表
    Init();
}

template <class ElemType>
SimpleDbLinkList<ElemType>::~SimpleDbLinkList() {
    //操作结果：销毁线性表
    Clear();                                                     //清空线性表
    delete head;                                                 //释放头结点
}

template <class ElemType>
int SimpleDbLinkList<ElemType>::Length() const {
    //操作结果：返回线性表元素个数
       return count;
}

template <class ElemType>
bool SimpleDbLinkList<ElemType>::Empty() const {
    //操作结果：如果线性表为空，则返回true，否则返回false
    return  head -> next == head;
}

template <class ElemType>
void SimpleDbLinkList<ElemType>::Clear() {
    //操作结果：清空线性表
    ElemType tmpPtr;                                             //临时元素值
    while (Length() > 0) {
        //线性表非空，则删除第一个元素
        Delete(1, tmpPtr);
    }
}

template <class ElemType>
void SimpleDbLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
    //操作结果：依次对线性表的每个元素调用函数（＊visit）
    for (DblNode<ElemType> *tmpPtr = head -> next; tmpPtr != head; tmpPtr = tmpPtr -> next) {
        //用tmpPtr依次指向每个元素
        (* visit)(tmpPtr -> data);                               //对线性表的每个元素调用函数（＊visit）
    }
}

template <class ElemType>
StatusCode SimpleDbLinkList<ElemType>::GetElem(int position, ElemType &e) const {
    //操作结果：当线性表在第position个元素时，用e返回其值，返回ENTRY_FOUND
    //否则返回NOT_PRESENT
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                           //取出指向第position个结点的指针
        e = tmpPtr -> data;                                      //用e返回第position个元素的值
        return ENTRY_FOUND;
    }
}

template <class ElemType>
StatusCode SimpleDbLinkList<ElemType>::SetElem(int position, const ElemType &e) {
    //操作结果：将线性表的第position个位置的元素赋值为e
    //position的取值范围为1<=position<=Length()
    //position合法返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                            //取出指向第position个元素的指针
        tmpPtr -> data = e;                                       //设置第position个元素的值
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SimpleDbLinkList<ElemType>::Insert(int position, ElemType &e) {
//操作结果：在线性表的第position个位置前插入元素e
//position的取值范围为1<=position<=Length()+1
//position合法返回SUCCESS，否则返回RANGE_ERROR
    if(position < 1 || position > Length() + 1) {
        //position范围错
        return RANGE_ERROR;
    }
    else  {
        //position合法
        DblNode<ElemType> *tmpPtr, *newPtr, *nextPtr;
        tmpPtr = GetElemPtr(position - 1);                           //取出第position-1个元素的指针
        nextPtr = tmpPtr -> next;                                    //nextPtr指向第position个结点
        newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);          //生成新结点
        tmpPtr -> next = newPtr;
        nextPtr -> back = newPtr;
        curPosition = position;
        curPtr = newPtr;
        count++;
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SimpleDbLinkList<ElemType>::Delete(int position, ElemType &e) {
    //操作结果：删除线性表中的第position个位置的元素，并用e返回其值
    //position的取值范围为1<=position<=Length()
    //position合法返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position-1);                            //取出第position-1个元素的指针
        tmpPtr = tmpPtr -> next;
        tmpPtr -> next -> back = tmpPtr -> back;
        tmpPtr -> back -> next = tmpPtr -> next;
        e = tmpPtr -> data;
        if (position == Length()) {
            curPtr = head;
            curPosition = 0;
        }
        else {
            curPosition = position;
            curPtr = tmpPtr -> next;
            
        }
        count--;
        delete tmpPtr;                                           //释放被删结点
        return SUCCESS;
    }
}


template <class ElemType>
SimpleDbLinkList<ElemType>::SimpleDbLinkList(const SimpleDbLinkList<ElemType> &copy) {
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
SimpleDbLinkList<ElemType> & SimpleDbLinkList<ElemType>::operator=(const SimpleDbLinkList<ElemType> &copy) {
    
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