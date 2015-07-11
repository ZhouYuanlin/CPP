//
//  SimpleLinkList.h
//  SimpleLinkList
//
//  Created by 木木同学 on 15/4/22.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SimpleLinkList_SimpleLinkList_h
#define SimpleLinkList_SimpleLinkList_h

#include "Node.h"
#include "Header.h"

//简单线性表类模板
template <class ElemType>
class SimpleLinkList
{
protected:
//链表实现的数据成员：
    Node<ElemType> *head;                                        //头结点指针
    mutable int curPosition;                                     //当前位置的序号
    mutable Node<ElemType> *curPtr;                              //指向当前位置的指针
    int count;                                                   //元素个数
    
    
    
//辅助函数模板
    Node<ElemType> *GetElemPtr(int position) const;              //返回指向第position个结点的指针
    void Init();                                                 //初始化线性表
    
    
public:
//抽象数据类型方法声明及重载编译系统默认方法声明：
    SimpleLinkList();                                            //无参构造函数模板
    virtual ~SimpleLinkList();                                   //析构函数模板
    int Length() const;                                          //求线性表长度
    bool Empty() const;                                          //判断线性表是否为空
    void Clear();                                                //将线性表清空
    void Traverse(void (*visit)(const ElemType &)) const;        //遍历线性表
    StatusCode GetElem(int position, ElemType &e) const;         //求指点位置的元素
    StatusCode SetElem(int position, const ElemType &e);         //设定指点位置的元素值
    StatusCode Delete(int position, ElemType &e);                //删除元素
    StatusCode Insert(int position, const ElemType &e);          //插入元素
    SimpleLinkList(const SimpleLinkList<ElemType> &copy);        //复制构造函数
    SimpleLinkList<ElemType> &operator = (const SimpleLinkList<ElemType> &copy);
                                                                 //重载赋值运算符
};


template <class ElemType>
Node<ElemType> * SimpleLinkList<ElemType>::GetElemPtr(int position) const
//操作结果：返回指向第position个结点的指针
{
    
    if (curPosition > position) {
        //当前位置在所查找位置之后，只能从表头开始操作
        curPosition = 0;
        curPtr = head;
    }
    
    while (curPtr != NULL && curPosition < position) {
        //顺指针向后查找，直到tmpPtr指向第position个结点
        curPtr = curPtr -> next;
        curPosition++;
    }
    
    if (curPtr != NULL && curPosition == position) {
        //查找成功
        return curPtr;
    }
    else    return NULL;                                          //查找失败
}

template <class ElemType>
void SimpleLinkList<ElemType>::Init() {
//操作结果：初始化线性表
    head = new Node<ElemType>;                                    //构造头指针
    curPtr = head;    curPosition = 0;                            //初始化当前位置
    count = 0;                                                    //初始化元素个数
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList() {
//操作结果：构造一个空链表
    Init();
}

template <class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList() {
//操作结果：销毁线性表
    Clear();                                                      //清空线性表
    delete head;                                                  //释放头指针所指空间
}


template <class ElemType>
int SimpleLinkList<ElemType>::Length() const {
//操作结果：返回线性表元素的个数
        return count;
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Empty() const {
//操作结果：如线性表为空，则返回true，否则返回flase
    return head -> next == NULL;
}

template <class ElemType>
void SimpleLinkList<ElemType>::Clear() {
//操作结果：清空线性表
    ElemType tmpElem;                                             //临时元素值
    while (Length() > 0) {
        //线性表非空，则删除第一个元素
        Delete(1, tmpElem);
    }
}

template <class ElemType>
void SimpleLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
//操作结果：依次对线性表中的元素调用函数（＊visit）
    for (Node<ElemType> *tmpPtr = head -> next; tmpPtr != NULL; tmpPtr = tmpPtr -> next) {
        //用tmpPtr依次指向每个元素
        (* visit)(tmpPtr -> data);                                //对线性表的每个元素调用函数（＊visit）
    }
}


template <class ElemType>
StatusCode SimpleLinkList<ElemType>::GetElem(int position, ElemType &e) const {
//操作结果：当线性表存在第position个元素时，用e返回其值，返回ENTRY_FOUND
//否则返回NOT_PRESENT
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                            //取出指向第position个结点的指针
        e = tmpPtr ->data;                                        //用e返回第position个元素的值
        return ENTRY_FOUND;
    }
    return NOT_PRESENT;
}

template <class ElemType>
StatusCode SimpleLinkList<ElemType>::SetElem(int position, const ElemType &e) {
//操作结果：将线性表的第position个位置的元素赋值为e
//position的取值范围为1<=position<=Length()
//position合法时返回SUCCESS，否则返回RANGE_ERROR
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);                            //取出指向第position个结点的指针
        tmpPtr -> data = e;                                       //设置第position个元素的值
        return SUCCESS;
    }
}


template <class ElemType>
StatusCode SimpleLinkList<ElemType>::Insert(int position, const ElemType &e) {
//操作结果：在线性表的position个位置前插入元素e
    if (position < 1 || position > Length()+1) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr, *newPtr;
        tmpPtr = GetElemPtr(position - 1);                        //取出第position－1个结点指针
        newPtr = new Node<ElemType>(e, tmpPtr -> next);           //生成新结点
        tmpPtr -> next = newPtr;                                  //将tmpPtr插入到链表中
        curPosition = position;
        curPtr = newPtr;
        count++;
        return SUCCESS;
    }
}

template <class ElemType>
StatusCode SimpleLinkList<ElemType>::Delete(int position, ElemType &e) {
//操作结果：删除线性表的第position个位置的元素，并用e返回其值
//position的取值范围为1<=position<=Length()
//position合法时返回SUCCESS，否则返回RANGE_ERROER
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        Node<ElemType> *tmpPtr, *nextPtr;
        tmpPtr = GetElemPtr(position - 1);                        //取出第position－1个结点指针
        nextPtr = tmpPtr -> next;                                 //nextPtr为tmpPtr的后继
        tmpPtr -> next = nextPtr -> next;                         //删除结点
        e = nextPtr -> data;                                      //用e返回被删除结点元素值
        if (position == Length()) {
            //删除尾结点，当前结点变为头结点
            curPosition = 0;
            curPtr = head;
        }
        else {
            //删除非尾结点，当前结点变为第position个结点
            curPtr = tmpPtr -> next;
            curPosition = position;
        }
        count--;                                                  //删除成功后元素个数减1
        
        delete nextPtr;
        return SUCCESS;
    }
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy) {
//操作结果：由线性表copy构造新线性表——复制构造函数模板
    int copyLength = copy.Length();                               //copy的长度
    
    ElemType e;
    
    if (!Empty()) {
        Clear();                                                  //如果线性表不为空，则清空线性表
    }
    Init();                                                       //初始化线性表
    for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
        copy.GetElem(curPosition, e);                             //取出第curPosition个元素
        Insert(Length() + 1, e);                                  //将e插入到当前线性表
    }
    
}

template <class ElemType>
SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy) {
//操作结果：将线性表copy赋值给当前线性表——重载赋值运算符
    
    if (&copy != this) {
        int copyLength = copy.Length();                           //copy的长度
        ElemType e;
        Clear();
        Init();                                                   //初始化当前线性表
        for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
            //复制数据元素
            copy.GetELem(curPosition, e);                         //取出第curPosition个元素
            Insert(Length() + 1, e);                              //将e插入到当前线性表
        }
    }
    return *this;
}

template <class ElemType>
void MergeList(SimpleLinkList<ElemType> &la, SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc) {
//初始条件：la和lb中数据元素递增有序
//操作结果：将la和lb合并为lc，使lc中数据元素仍递增有序
    ElemType aItem, bItem;                                 //la、lb、lc中的元素
    int aLength = la.Length();                                    //la的长度
    int bLength = lb.Length();                                    //lb的长度
    
    lc.Clear();                                                   //清空线性表lc
    
    int aPosition = 1;                                            //初始化la中元素的位置
    int bPosition = 1;                                            //初始化lb中元素的位置
    
    while (aPosition <= aLength && bPosition <= bLength) {
        //取出la、lb中的数据元素进行归并
        la.GetElem(aPosition, aItem);                             //取出la中第aPosition个元素
        lb.GetElem(bPosition, bItem);                             //取出lb中第bPosition个元素
        if (aItem < bItem) {
            //归并aItem
            lc.Insert(lc.Length() + 1, aItem);                    //插入aItem到lc中
            aPosition++;                                          //指向la中下一个元素
        }
        
        else {
            //归并bItem
            lc.Insert(lc.Length() + 1, bItem);                    //插入bItem到lc中
            bPosition++;                                          //指向lb下一个数据元素
        }
    }
    
    while (aPosition <= aLength) {
        //归并la中剩余数据元素
        la.GetElem(aPosition, aItem);                                    //取出la中数据元素
        lc.Insert(lc.Length() + 1, aItem);                        //插入aItem到lc中
        aPosition++;                                              //指向la中下一个元素
    }
    while (bPosition <= bLength) {
        //归并lb中剩余数据元素
        lb.GetElem(bPosition, bItem);                                    //取出lb中数据元素
        lc.Insert(lc.Length() + 1, bItem);                        //插入bItem到lc中
        bPosition++;                                              //指向lb中下一个元素
    }
}



template <class ElemType>
void Reverse(SimpleLinkList<ElemType> &la) {
    int aLength = la.Length();
    ElemType aItem, bItem, cItem;
    for (int curPosition = 1; curPosition <= aLength / 2; curPosition++) {
        la.GetElem(curPosition, aItem);
        la.GetElem(aLength - curPosition + 1, bItem);
        cItem = aItem;
        aItem = bItem;
        bItem = cItem;
        la.SetElem(curPosition, aItem);
        la.SetElem(aLength - curPosition + 1, bItem);
    }
}























#endif
