//
// Created by Lokyin Zhao on 2020/11/19.
//

#ifndef EXP_SRC_DEF_H
#define EXP_SRC_DEF_H

#include <string>
#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOWED -2
#define MAX_VERTEX_NUM 20
#define FILE_PATH "./data/"//文件保存的路径
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    std::string info;
} VertexType; //顶点类型定义

#endif //EXP_SRC_DEF_H
