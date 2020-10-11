//
// Created by Lokyin Zhao on 2020/9/29.
//

#ifndef INC_1_SEQUENCE_STRUCTURE_DEF_H
#define INC_1_SEQUENCE_STRUCTURE_DEF_H

#include <cstdio>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define OK 1    //函数正常返回
#define ERROR 0 //函数错误，不正常返回
#define INFEASIBLE -1   //不可行
#define OVERFLOWED -2     //溢出或申请空间失败
#define UNEXPECTED -3      //其他不正常情况

#define INIT_SIZE 20
#define INCREMENT  10

typedef  int status;
typedef int ElemType; //数据元素类型定义



#endif //INC_1_SEQUENCE_STRUCTURE_DEF_H


//test