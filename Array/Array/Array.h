//
//  Array.h
//  Array
//
//  Created by 木木同学 on 15/5/22.
//  Copyright (c) 2015年 木木同学. All rights reserved.
//

#ifndef Array_Array_h
#define Array_Array_h

#include "Header.h"

//数组类模板
template <class ElemType>
class Array {
protected:
//数组的数据成员：
    ElemType *base;                                   //数组元素基址
    int dim;                                          //数组维数
    int *bounds;                                      //数组各维长度
    int *constants;                                   //数组映像函数常亮
    
//辅助函数模板
    int Locate(int subO,va_list &va)const;            //求元素在顺序存储中的位置
    
public:
//抽象数据类型方法声明及重载编译系统默认方法声明：
    Array(int d, ...);                                //由维数d与随后的各维长度构造数组
    ~Array();                                         //析构函数模板
    ElemType &operator() (int subO, ...);             //重载函数运算符
    Array(const Array<ElemType> &copy);               //复制构造函数模板
    Array<ElemType> &operator=(const Array<ElemType> &copy);
                                                      //重载赋值运算符
};

//数组类的实现部分
template <class ElemType>
int Array<ElemType>::Locate(int subO, va_list &va) const {
    return 1;
}

template <class ElemType>
Array<ElemType>::Array(int d, ...) {
//操作结果：由维数d与随后的各维长度构造数组
    if (d < 1) {
        throw Error("维数不能小于1!");                  //抛出异常
    }
    dim = d;                                          //数组维数为d
    bounds = new int[dim];                            //分配数组各维长度存储空间
    va_list va;                                       //变长参数变量
    int elemTotal = 1;                                //元素总数
    int i;                                            //临时变量
    
    va_start(va, d);                                  //初始化变量va，用于存储变长参数信息，d为省略号左侧最右边的参数标志符
    
    for(i = 0; i < dim; i++)
    { //为各维长度赋值并计算数组总元素个数
        bounds[i] = va_arg(va, int);                  //取出变长参数的引用
        elemTotal = elemTotal * bounds[i];            //统计数组总元素个数
    }
    va_end(va);                                       //结束变长参数的引用
    
    base = new ElemType[elemTotal];                   //分配数组元素空间
    constants = new int[dim];                         //分配数组映像函数常量
    constants[dim - 1] = 1;
    for (i = dim - 2; i >= 0; i--) {
        constants[i] = bounds[i+1] * constants[i + 1];//计算数组映像函数常量
    }
}









































#endif
