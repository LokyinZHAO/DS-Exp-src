//
// Created by Lokyin Zhao on 2020/11/19.
//

#ifndef EXP_SRC_DEF_H
#define EXP_SRC_DEF_H
#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

#endif //EXP_SRC_DEF_H
