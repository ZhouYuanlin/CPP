//
//  SqList.h
//  LinearList
//
//  Created by 木木同学 on 15/4/11.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef __LinearList__SqList__
#define __LinearList__SqList__

#include "Header.h"
//顺序表类模板

template <class ElemType>
class SqList
{
protected:
//顺序表实现的数据成员
    int count;                                                  //元素个数
    int maxSize;                                                //顺序表最大元素个数
    ElemType *elems;                                            //元素存储空间
    
    
//辅助函数模板
    bool Full() const;                                          //判断线性表是否已满
    void Init(int size);                                        //初始化线性表
    
public:
//抽象数据类型方法声明及重载函数编译系统默认方法声明
    SqList(int size = DEFAULT_SIZE);                            //构造函数模板
    virtual ~SqList();                                          //析构函数模板
    int Length() const;                                         //求线性表长度
    bool Empty() const;                                         //判断线性表是否为空
    void Clear();                                               //清空线性表
    void Traverse(void (* Visit) (const ElemType &)) const;     //遍历线性表
    StatusCode GetElem(int position, ElemType &e) const;        //求指点位置的元素
    StatusCode SetElem(int position, const ElemType &e);        //设置指定位置的元素值
    StatusCode Delete(int position, ElemType &e);               //删除元素
    StatusCode Insert(int position, const ElemType &e);         //插入元素
    SqList(const SqList<ElemType> &copy);                       //复制构造函数模板
    SqList<ElemType> &operator = (const SqList<ElemType> &copy);//重载赋值运算符
};

template <class ElemType>
bool SqList<ElemType>::Full() const
//操作结果：如线性表已满，则返回true，否则返回false
{
    return count == maxSize;
}

template <class ElemType>
void SqList<ElemType>::Init(int size)
//操作结果：初始化线性表为最大元素个数为size的空线性表
{
    maxSize = size;                           //最大元素个数
    if (elems != NULL) {
        delete []elems;                       //释放存储空间
    }
    elems = new ElemType[maxSize];            //分配存储空间
    count = 0;                                //空线性表元素个数为0
}

template <class ElemType>
SqList<ElemType>::SqList(int size)
//操作结果：构造一个最大元素个数为size的空顺序表
{
    elems = NULL;                             //未分配存储空间前，elems为空
    Init(size);                               //初始化线性表
}

template <class ElemType>
SqList<ElemType>::~SqList()
//操作结果：销毁线性表
{
    delete []elems;                           //释放存储空间
}


template <class ElemType>
int SqList<ElemType>::Length() const
//操作结果：返回线性表元素个数
{
    return count;
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
//操作结果：如线性表为空，则返回true，否则返回false
{
    return count == 0;
}

template <class ElemType>
void SqList<ElemType>::Clear()
//操作结果：清空线性表
{
    count = 0;
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
//操作结果：依次对线性表的每个元素调用函数（＊visit）
{
    for (int curPosition = 1; curPosition <= Length(); curPosition++) {
        //对线性表的每个元素调用函数（＊visit）
        (*Visit)(elems[curPosition - 1]);
    }
}

template <class ElemType>
StatusCode SqList<ElemType>::GetElem(int position, ElemType &e) const
//操作结果：当线性表存在第position个元素时，用e返回其值，返回ENTPRY_FOUND，否则返回NOT_PRESENT
{
    if (position < 1 || position > Length()) {
        //position范围错
        return NOT_PRESENT;                     //元素不存在
    }
    else {
        //position合法
        e = elems[position - 1];
        return ENTRY_FOUND;                     //元素存在
    }
}

template <class ElemType>
StatusCode SqList<ElemType>::SetElem(int position, const ElemType &e)
//操作结果：将线性表第position个位置的元素赋值为e
//position的取值范围为1<=position<=Length()
//position合法时函数返回SUCCESS，否则函数返回RANGE_ERROER
{
    if (position < 1 || position > Length()) {
        //position范围错
        return RANGE_ERROR;                     //位置错
    }
    else {
        //position合法
        elems[position - 1] = e;
        return SUCCESS;                         //成功
    }
}


template <class ElemType>
StatusCode SqList<ElemType>::Insert(int position, const ElemType &e)
//操作结果：在线性表的第position个位置前插入元素e
//如线性表已满，则返回OVER_FLOW
//如position合法，则返回SUCCESS，否则返回RANGE_ERROR
{
    int len = Length();
    ElemType tmp;
    if (Full()) {
        //线性表已满返回OVER_FLOW
        return OVER_FLOW;
    }
    else if (position < 1 || position > len + 1) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //成功
        count++;                                 //插入元素后个数将自增1
        for (int curPosition = len; curPosition >= position; curPosition--) {
            //插入位置之后的元素右移
            GetElem(curPosition, tmp);
            SetElem(curPosition + 1, tmp);
        }
        SetElem(position, e);                    //将e赋值到position位置处
        return SUCCESS;                          //插入成功
    }
}

template <class ElemType>
StatusCode SqList<ElemType>::Delete(int position, ElemType &e)
//操作结果：删除线性表的第position个位置的元素，并用e返回其值
//position的取值范围为1<=position<=Length()
//position合法时间返回SUCCESS，否则返回RANGE_ERROR
{
    int len = Length();
    ElemType tmp;
    if (position < 1 || position >= len) {
        //position范围错
        return RANGE_ERROR;
    }
    else {
        //position合法
        GetElem(position, e);
        for (int curPosition = position + 1; curPosition <= len; curPosition++) {
            //被删除元素依次左移
            GetElem(curPosition, tmp);
            SetElem(curPosition - 1, tmp);
        }
        count--;                                 //删除后元素个数将自减1
        return SUCCESS;
    }
}


template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType>&copy)
//操作结果：有线性表copy构造新线性表——复制构造函数模板
{
    int copyLength = copy.Length();              //copy的长度
    ElemType e;
    elems = NULL;                                //未分配存储空间前，elems为空
    Init(copy.maxSize);                          //初始化新线性表
    for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
        copy.GetELem(curPosition, e);            //取出第curPosition个元素
        Insert(Length() + 1, e);                 //将e插入到当前的线性表
    }
}


template <class ELemType>
SqList<ELemType> &SqList<ELemType>::operator = (const SqList<ELemType> &copy)
//操作结果：将当前线性表copy赋值给当前线性表——重载赋值运算符
{
    if (&copy != this) {
        int copyLength = copy.Length();          //copy的长度
        ELemType e;
        Init(copy.maxSize);                      //初始化当前线性表
        for (int curPosition = 1; curPosition <= copyLength; curPosition++) {
            //复制数据元素
            copy.GetElem(curPosition, e);        //取出第position个元素
            Insert(Length() + 1, e);             //将元素插入到当前线性表中
        }
    }
    return *this;
}



template <class ElemType>
void Different(const SqList<ElemType> &la, const SqList<ElemType> &lb, SqList<ElemType> &lc)
//操作结果：用lc返回la和lb表示的集合差集
//方法：在la中取元素，在lb中进行查找，如果未在lb中出现，将其插入到lc
{
    lc.Clear();                                  //清空lc
    
    ElemType aItem, bItem;
    
    for (int aPosition = 1; aPosition <= la.Length(); aPosition++) {
        
        la.GetElem(aPosition, aItem);            //取出la中的一个元素；
        bool isExist = false;                    //表示aItem是否在lb中出现
        
        for (int bPosition = 1; bPosition <= lb.Length(); bPosition++) {
            lb.GetElem(bPosition, bItem);        //取出lb中的一个元素
            
            if (bItem == aItem) {
                isExist = true;                  //aItem同时在la和lb中出现，置isExist为true
                break;                           //退出内层循环
            }
        }
        if (!isExist) {
            //aItem在la中出现，而在lb中未出现，将其插入到lc中
            lc.Insert(lc.Length() + 1, aItem);
        }
    }
}


template <class ElemType>
void Adjust(SqList<ElemType> &la)
//操作结果：将la调整为左右两部份，左边所有元素为奇数，右边所有元素为偶数，
//并要求算法的时间复杂度为O(n)
{
    int leftPosition = 1, rightPosition = la.Length();
    ElemType aItem, bItem;
    while (leftPosition < rightPosition) {
        la.GetElem(leftPosition, aItem);
        la.GetElem(rightPosition, bItem);
        if (aItem % 2 == 1) {
            leftPosition ++;
        }
        else if (bItem % 2 == 0) {
            rightPosition--;
        }
        else {
            la.SetElem(leftPosition++, bItem);
            //bItem置换la的第leftPosition个元素，并且leftPosition＋＋
            la.SetElem(rightPosition--, aItem);
            //aItem置换la的第rightPosition个元素，并且rightPosition－－
        }
        
    }
}


#endif /* defined(__LinearList__SqList__) */
