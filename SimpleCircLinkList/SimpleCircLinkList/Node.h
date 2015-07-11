//
//  Node.h
//  SimpleLinkList
//
//  Created by 木木同学 on 15/4/22.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef SimpleLinkList_Node_h
#define SimpleLinkList_Node_h

//结点类模板
template <class ElemType>
struct Node
{
    //数据成员:
    ElemType data;                                    //数据域
    Node<ElemType> *next;                             //指针域
    
    
    //构造函数模板
    Node();                                           //无参数构造函数模板
    Node(ElemType item, Node<ElemType> *link = NULL);  //有参构造
};


//结点类模板的实现部分
template <class ElemType>\
Node<ElemType>::Node()
//操作结果：构造指针域为空的结点
{
    next = NULL;
}

template <class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
//操作结果：构造一个数据域为item和指针域为link的结点
{
    data = item;
    next = link;
}

#endif
