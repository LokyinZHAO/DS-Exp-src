//
// Created by Lokyin Zhao on 2020/10/16.
//
//
// Created by Lokyin Zhao on 2020/10/16.
//
//线性表的创建
#ifndef EXP_SRC_STU01_H
#define EXP_SRC_STU01_H
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L!= nullptr)//链表已存在
        return INFEASIBLE;
    L=(LinkList)malloc(sizeof(LNode));//初始化
    L->next= nullptr;
    return OK;

    /********** End **********/
}
#endif //EXP_SRC_STU01_H

#ifndef EXP_SRC_STU10_H
#define EXP_SRC_STU10_H
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L== nullptr)
        return INFEASIBLE;
    LinkList p=L;
    for (int j = 1;p!= nullptr ; ++j) {
        if (j==i){
            LinkList next=p->next;
            p->next=(LinkList)malloc(sizeof(LNode));
            p->next->data=e;
            p->next->next=next;
            return OK;
        }
        p=p->next;
    }
    return ERROR;

    /********** End **********/
}

#endif //EXP_SRC_STU08_H

#ifndef EXP_SRC_STU11_H
#define EXP_SRC_STU11_H
#include <iostream>
#include <fstream>
using namespace std;
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L== nullptr)
        return INFEASIBLE;
    int len;
    LinkList p=L->next;
    for (len = 0; p!= nullptr ; ++len) p=p->next;
    ofstream outfile;
    outfile.open(FileName);
    if (outfile.fail()){
        cout<<"open file failed when save list!";
        exit(0);
    }
    outfile<<len<<endl;
    p=L->next;
    while (p!= nullptr){
        outfile<<p->data<<endl;
        p=p->next;
    }
    outfile.close();
    return OK;

    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L!= nullptr)
        return INFEASIBLE;
    ifstream infile;
    infile.open(FileName);
    if (infile.fail()){
        cout<<"open file failed when save list!";
        exit(0);
    }
    int len;
    infile>>len;
    InitList(L);
    for (int i = 0; i < len; ++i) {
        ElemType e;
        infile>>e;
        ListInsert(L,i+1,e  );
    }
    return OK;

    /********** End 2 **********/
}

#endif //EXP_SRC_STU08_H
