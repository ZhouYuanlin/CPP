//
//  LinkQueue.h
//  LinkQueue
//
//  Created by 木木同学 on 15/5/7.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef LinkQueue_LinkQueue_h
#define LinkQueue_LinkQueue_h

#include "Header.h"
#include "Node.h"

//链队列类模板
template <class ElemType>
class LinkQueue {
//链队列实现的数据成员：
    Node<ElemType> *front, *rear;                                //队头队尾指针
    
//辅助函数模板：
    void Init();                                                 //初始化队列

public:
//抽象数据类型方法声明及重载编译系统默认方法声明：
    LinkQueue();                                                 //无参构造函数
    virtual ~LinkQueue();                                        //析构函数
    int Length() const;                                          //求队列的长度
    bool Empty() const;                                          //判断队列是否为空
    void Clear();                                                //清空队列
    void Traverse(void (*visit)(const ElemType &)) const;        //遍历队列
    StatusCode OutQueue(ElemType &e);                            //出队列
    StatusCode InQueue(const ElemType &e);                       //入队列
    StatusCode GetHead(const ElemType &e);                       //获取队头
    LinkQueue(const LinkQueue<ElemType> &copy);                  //复制构造函数
    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy);
                                                                 //重载赋值运算符
};


//链队列类模板的实现部分
template <class ElemType>
void LinkQueue<ElemType>::Init() {
//操作结果：初始化队列
    front = rear = new Node<ElemType>;                            //生成头结点
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {
//操作结果：构造一个空队列
    Init();
}

template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
//操作结果：销毁队列
    Clear();
}

template <class ElemType>
int LinkQueue<ElemType>::Length() const {
//操作结果：返回队列长度
    int count = 0;                                                //计数器
    for (Node<ElemType> *tmpPtr = front -> next; tmpPtr != NULL; tmpPtr = tmpPtr -> next) {
        //用tmpPtr依次指向每个元素
        count++;                                                  //对队列每个元素进行计数
    }
    return count;
}

template <class ElemType>
bool LinkQueue<ElemType>::Empty() const {
//操作结果：如果队列为空，则返回true，否则返回false
    return front == rear;
}

template <class ElemType>
void LinkQueue<ElemType>::Clear() {
//操作结果：清空队列
    ElemType tmpElem;                                             //临时元素值
    while (Length() > 0) {
        //队列非空，则出列
        OutQueue(tmpElem);
    }
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
//操作结果：依次对队列的每个元素调用函数（＊ visit）
    for (Node<ElemType> *tmpPtr = front -> next; tmpPtr != NULL; tmpPtr = tmpPtr -> next) {
        //对队列每个元素调用函数（＊ visit）
        (*visit)(tmpPtr -> data);
    }
}

template <class ElemType>
StatusCode LinkQueue<ElemType>::OutQueue(ElemType &e) {
//操作结果：如果队列非空，那么删除队头元素，并用e返回其值，返回SUCCESS，
//否则返回UNDER_FLOW
    if (!Empty()) {
        //队列非空
        Node<ElemType> *tmpPtr;
        tmpPtr = front -> next;                                   //指向队列头元素
        front -> next = tmpPtr -> next;                           //front指向下一个元素
        e = tmpPtr -> data;                                       //用e返回队列头元素
        if (rear == front) {
            //表示出队前队列中只有一个元素，出队后为空队列
            rear = front;
        }
        delete tmpPtr;                                            //释放出队的结点
        return SUCCESS;
    }
    else {
        //队列为空
        return UNDER_FLOW;
    }
}

template <class ElemType>
StatusCode LinkQueue<ElemType>::InQueue(const ElemType &e) {
//操作结果：插入元素e为新的队尾，返回SUCCESS
    Node<ElemType> *tmpPtr = new Node<ElemType>(e);               //生成新结点
    rear -> next = tmpPtr;                                        //新结点追加在队尾
    rear = tmpPtr;                                                //rear指向新队尾
    return SUCCESS;
}

template <class ElemType>
StatusCode LinkQueue<ElemType>::GetHead(const ElemType &e) {
//操作结果：如果队列非空，那么用e返回队列元素，返回SUCCESS
//否则返回UNDER_FLOW
    if (!Empty()) {
        //队列非空
        Node<ElemType> *tmpPtr = front -> next;                   //指向队列头元素
        e = tmpPtr -> data;                                       //用e返回队头元素
        return SUCCESS;
    }
    else {
        //队列为空
        return UNDER_FLOW;
    }
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy) {
//操作结果：由队列copy构造新队列——复制构造函数模板
    Init();
    for (Node<ElemType> *tmpPtr = copy.front -> next; tmpPtr != NULL; tmpPtr = tmpPtr -> next) {
        //对copy队列每个元素对当前队列入队操作
        InQueue(tmpPtr -> data);
    }
}

template <class ElemType>
LinkQueue<ElemType>& LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy) {
//操作结果：将队列copy赋值给当前队列——重载赋值运算符
    if (&copy != this) {
        Clear();
        for (Node<ElemType> *tmpPtr = copy.front -> next; tmpPtr != NULL; tmpPtr = tmpPtr -> next) {\
            //对copy队列每个元素对当前队列入队操作
            InQueue(tmpPtr -> data);
        }
    }
    return *this;
}




//最小优先队列类模板
template <class ElemType>
class MinPriorityLinkQueue:public LinkQueue<ElemType> {
    
public:
//重载入队操作声明：
    StatusCode InQueue(const ElemType &e);                        //重载入队操作
};


//最小优先队列类模板的实现部分
template <class ElemType>
StatusCode MinPriorityLinkQueue<ElemType>::InQueue(const ElemType &e) {
//操作结果：插入元素e为新的队尾，返回SUCCESS
    Node<ElemType> *curPtr = LinkQueue<ElemType>::front -> next;  //指向当前结点
    Node<ElemType> *curPrePtr = LinkQueue<ElemType>::front;       //指向当前结点的前驱结点
    
    while (curPtr != NULL && curPtr -> data <= e) {
        //curPtr与curPrePtr都指向下一个元素
        curPrePtr = curPtr;
        curPtr = curPtr -> next;
    }
    
    Node<ElemType> *tmpPtr = new Node<ElemType>(e, curPtr);       //生成新结点
    curPrePtr -> next = tmpPtr;                                   //将tmpPtr插入在curPrePtr与curPtr之间
    
    if (curPrePtr == LinkQueue<ElemType>::rear) {
        //新结点插在rear的后面
        LinkQueue<ElemType>::rear = tmpPtr;                       //rear指向新队尾
    }
    return SUCCESS;
}



//最大优先链队列类模板
template <class ElemType>
class MaxPriorityLinkQueue:public LinkQueue<ElemType> {
    
public:
//重载入队操作声明：
    StatusCode InQueue(const ElemType &e);                        //重载入队操作
};


//最大优先队列类模板的实现部分
template <class ElemType>
StatusCode MaxPriorityLinkQueue<ElemType>::InQueue(const ElemType &e) {
    Node<ElemType> *curPtr = LinkQueue<ElemType>::front -> next;  //指向当前结点
    Node<ElemType> *curPrePtr = LinkQueue<ElemType>::front;       //指向当前结点的前驱
    
    while (curPtr != NULL && curPtr -> data >= e) {
        //curPrePtr与curPtr都指向下一个元素
        curPrePtr = curPtr;
        curPtr = curPtr -> next;
    }
    
    Node<ElemType> *tmpPtr = new Node<ElemType>(e, curPtr);       //生成新结点
    curPrePtr -> next = tmpPtr;                                   //将tmpPtr插入在curPrePtr与curPtr之间
    
    if (curPrePtr == LinkQueue<ElemType>::rear) {
        LinkQueue<ElemType>::rear = tmpPtr;                       //rear指向新队尾
    }
    return SUCCESS;
}

































#endif
