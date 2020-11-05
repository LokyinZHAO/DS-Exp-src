//
// Created by Lokyin Zhao on 2020/10/30.
//

#ifndef EXP_SRC_STU04_H
#define EXP_SRC_STU04_H

#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    ofstream outfile;
    outfile.open(FileName);
    if (outfile.fail()) {
        cout << "fail to open file" << endl;
        exit(0);
    }
    //先序非递归遍历，计算并存储在二叉树中的位置
    if (!T) return INFEASIBLE;
    stack<BiTree> s;
    stack<int> position;//标记当前结点在二叉树中的位置
    s.push(T);
    position.push(1);
    while (!s.empty()) {
        BiTree p=s.top();
        int posi=position.top();
        while (p) {
            outfile<<posi<<" "<<p->data.key<<" "<<p->data.others<<endl;
            s.push(p->lchild);//访问后向左尽头
            position.push(position.top() * 2);
            p=s.top();
            posi=position.top();
        }
        //outfile<<position.top()<<" "<<0<<" "<<"null"<<endl;//写入空指针
        s.pop();
        position.pop();//空结点退栈
        if (!s.empty()) {//访问右子树
            posi = position.top();
            p = s.top();
           // outfile << position.top() << " " << s.top()->data.key << " " << s.top()->data.others << endl;//依次写入位置，关键字，内容
            position.pop();
            s.pop();//双亲结点退栈
            s.push(p->rchild);
            position.push(posi * 2 + 1);//右子树入栈
        }
    }
    outfile << 0 << " " << 0 << " EOF" << endl;//结束标记
    outfile.close();
    return OK;
    /********** End 1 **********/
}

status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (T) return INFEASIBLE;//二叉树已存在不能读写
    ifstream infile;
    infile.open(FileName);
    if (infile.fail()) {
        cout << "fail to open file" << endl;
        exit(0);
    }
    //读文件
    stack<int> position;
    stack<BiTree> s;
    int posi;
    BiTree p=(BiTree)malloc(sizeof(BiTNode));
    infile>>posi;
    infile>>p->data.key;
    infile>>p->data.others;
    p->lchild= nullptr;
    p->rchild= nullptr;
    T=p;
    s.push(p);
    position.push(posi);
    p=(BiTree)malloc(sizeof(BiTNode));
    infile>>posi;
    infile>>p->data.key;
    infile>>p->data.others;
    p->lchild= nullptr;
    p->rchild= nullptr;
    while (!s.empty()){
        if (posi==position.top()*2){//栈顶左子树
            s.top()->lchild=p;
            s.push(p);
            position.push(posi);//入栈
            p=(BiTree)malloc(sizeof(BiTNode));
            infile>>posi;
            infile>>p->data.key;
            infile>>p->data.others;
            p->lchild= nullptr;
            p->rchild= nullptr;
        } else if (posi==(position.top()*2+1)){//栈顶右子树
            s.top()->rchild=p;
            s.push(p);
            position.push(posi);//入栈
            p=(BiTree)malloc(sizeof(BiTNode));
            infile>>posi;
            infile>>p->data.key;
            infile>>p->data.others;
            p->lchild= nullptr;
            p->rchild= nullptr;
        } else{//既不是左子树又不是右子树，开始回溯
            position.pop();
            s.pop();//退栈
        }
    }

    /********** End 2 **********/
}

#endif //EXP_SRC_STU_H
