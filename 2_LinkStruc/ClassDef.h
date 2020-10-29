//
// Created by Lokyin Zhao on 2020/10/16.
//

#ifndef EXP_SRC_CLASSDEF_H
#define EXP_SRC_CLASSDEF_H
#include <fstream>
#include "def.h"

using namespace std;

class LinkStru{//定义一个链表的线性表的数据抽象
public:
    typedef struct LNode{  //单链表（链式结构）结点的定义
        ElemType data;
        struct LNode *next;
    }LNode,*LinkList;

    LinkStru(const string &name){//不能调用INIT初始化，因为在LinkSet中malloc出来的空间指针是垂悬指针，可能不为nullptr
        head=(LinkList)malloc(sizeof(LNode));//初始化
        head->data=0;//头节点的data域存储元素个数
        head->next= nullptr;
        linkName=name;
    }


private:
    LinkList head;//头指针
public:
    string  linkName;//线性表名称
    LinkList GetHead(){//返回头指针
        return head;
    }

//func1:初始化线性表
//函数名原型：status InitList()
//如果线性表L不存在，操作结果是构造一个空的线性表，返回OK，若分配失败返回OVERFLOWED，否则返回INFEASIBLE。
    status InitList(){
    if (head!= nullptr)
        return INFEASIBLE;
    head=(LinkList)malloc(sizeof(LNode));//初始化
    if (head== nullptr)
        return OVERFLOWED;//初始化失败
    head->data=0;//头节点的data域存储元素个数
    head->next= nullptr;
        return OK;
}
//func2：销毁线性表
//函数名原型：status DestroyList()
//如果线性表L存在，该操作释放线性表的空间，使线性表成为未初始化状态，返回OK；否则对于一个未初始的线性表，是不能进行销毁操作的，返回INFEASIBLE。
    status DestroyList(){
    if (head== nullptr)
        return INFEASIBLE;//不能对未初始化的链表销毁
    ClearList();//先清空线性表
    free(head);
    head= nullptr;
        return OK;
}
//func3:清空线性表
//函数名原型：status ClearList()
//若线性表L不存在，清空L,释放所有数据元素的结点，返回OK；若线性表L不存在，则返回INFEASIBLE。
    status ClearList(){
    if (head== nullptr )//链表不存在
        return INFEASIBLE;
    LinkList p=head->next;
    while (p!= nullptr){//依次freeL之后的节点
        LinkList q=p;
        p=p->next;
        free(q);
    }
    head->data=0;
    head->next= nullptr;
        return OK;
}
//func4:线性表判空
//函数名原型：status ListEmpty()
//若线性表L不存在，则返回INFEASIBLE；若线性表L长度为0，则返回TRUE；不为0则返回FALSE。
    status ListEmpty(){
    if (head== nullptr)//线性表不存在
        return INFEASIBLE;
    if (head->data==0)//线性表为空的标准
        return TRUE;
    else return FALSE;
}
//func5:线性表长度
//函数名原型：status ListLength(int &len)
//若线性表L不存在，则返回INFEASIBLE；否则通过引用len返回线性表L的长度，并且最终返回OK。
    status ListLength(int &len){
        if (head== nullptr)
            return INFEASIBLE;
        else {
            len=head->data;//head的data存储了线性表长度的数据
            return OK;
        }
}
//func6:获取元素
//函数原型：status GetElem(int i,ElemType &e)
//功能说明：若线性表L不存在，返回INFEASIBLE；若i<1或者i超过线性表L的长度，则返回ERROR；若获取成功，则将值赋给e，并返回OK。
    status GetElem(int i,ElemType &e){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        if (i<1||i>head->data)
            return ERROR;//i不合法
        LinkList q=head;
        for (int j= 1; j <= i; ++j) {//依次遍历访问到第i个节点
            q=q->next;
        }
        e=q->data;
        return OK;
};
//func7:查找元素
//函数原型：status LocateElem(ElemType e,int &i)
//功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定的元素e，则查找失败，返回ERROR；若查找成功，采用引用的方式返回元素序号，返回OK。
    status LocateElem(ElemType e,int &i){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        LinkList q=head->next;
        for (i = 1; i <= head->data; ++i) {
            if (q->data==e) {
                return OK;//返回
            }
            q=q->next;
        }
        return ERROR;//未找到元素e
    }
//func8:获取前驱元素
//函数原型：status PriorElem(ElemType e,ElemType &pre)
//功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的前驱，则查找失败，返回ERROR；若查找成功，则将值赋给pre，并返回OK。
    status PriorElem(ElemType e,ElemType &pre){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        if (head->data==0)
            return ERROR;//空表，直接返回为"未找到元素"，不再查找
        LinkList q=head ,p=head ->next;
        if (p->data==e)
            return UNEXPECTED;//第一个元素无前驱
        q=q->next;
        p=p->next;
        while (p!= nullptr){
            if (p->data==e){
                pre=q->data;
                return OK;
            }
            p=p->next;
            q=q->next;
        }
        return ERROR;//未找到元素
    }
//func9:获取后继元素
//函数原型：status NextElem(ElemType e,ElemType &next)
//功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的后继，则查找失败，返回ERROR；若查找成功，则将值赋给next，并返回OK。
    status NextElem(ElemType e,ElemType &next){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        if (head->data==0)
            return ERROR;//空表，直接返回为"未找到元素"，不再查找
        LinkList p=head->next;//p指向首元素，由于判断了空表，所以p首元结点一定存在，但是从
        while (p->next!= nullptr){
            if (p->data==e){
                next=p->next->data;//访问后继
                return OK;
            }
            p=p->next;
        }
        if (p->data==e)
            return UNEXPECTED;//最后一个元素匹配，但无后继
        return ERROR;//未找到
    }
//func10:插入元素
//函数原型：status ListInsert(int i,ElemType e)
//功能说明：如果线性表L不存在，返回INFEASIBLE；否则在线性表L的第i个元素前插入新的元素e，插入成功返回OK，失败返回ERROR。
    status ListInsert(int i,ElemType e){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        LinkList p=head;//TODO：不明原因在读取文件这里head有时会BAD_ACCESS访问，目测是head没成功分配
        if (i<1||i>head->data+1) return ERROR;//插入位置不合法
        for (int j = 1; j <= head->data+1; ++j) {
            if (j==i){
                LinkList newnode=(LinkList)malloc(sizeof(LNode));
                newnode->data=e;
                newnode->next=p->next;
                p->next=newnode;
                head->data++;//数目加
                return OK;//成功返回
            }
            p=p->next;
        }
    }
//func11:删除元素
//函数原型：status ListDelete(int i,ElemType &e)
//功能说明：若线性表L不存在，返回INFEASIBLE；否则删除线性表L的第i个元素，若删除成功则将删除的值赋给e并返回OK，若删除失败则返回ERROR。
    status ListDelete(int i, ElemType &e){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        LinkList p=head;
        if (i<1||i>head->data) return ERROR;//删除位置不合法
        for (int j = 1; j <= head->data ; ++j) {
            if (j==i){
                LinkList nextnode=p->next->next;
                e=p->next->data;
                free(p->next);
                p->next=nextnode;
                head->data--;//数目减
                return OK;//成功返回
            }
            p=p->next;
        }
    }
//func12:遍历线性表
//函数原型：status ListTraverse()
//功能说明：若线性表L不存在，返回INFEASIBLE；否则将元素依次输出，并返回OK。
     status ListTraverse(const string& listname){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        if (head->data==0)
            return ERROR;//空表
        LinkList p=head->next;
        cout<<listname<<":"<<endl;
        for (int i = 0; i < head->data; ++i) {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
        return OK;//成功
    }
//func13:存储文件
//函数原型：status SaveList(string filepath,)
//功能说明：如果线性表L不存在，返回INFEASIBLE；否则将线性表L的全部元素写入到文件名为filename的文件中，返回OK。
    status SaveList(const string& filepath){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        ofstream outfile;
        outfile.open(filepath+linkName+".txt",ios::out|ios::trunc);
        if (outfile.fail())
            return OVERFLOWED;//文件打开失败
        outfile<<head->data<<endl;//首先写入表长
        LinkList p=head->next;
        for (int i = 0; i < head->data; ++i) {
            outfile<<p->data<<endl;//写入元素
            p=p->next;
        }
        outfile.close();
        return OK;
    }
//func14:读取文件
//函数原型：status LoadList(string filepath)
//功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，返回INFEASIBLE；否则将文件名为filename的数据读入到线性表L中，返回OK。
    status LoadList(const string& filepath){
        if (head->data!=0)
            return INFEASIBLE;//线性表中已经有元素，不可行
        ifstream infile;
        infile.open(filepath+linkName+".txt",ios::in);
        if (infile.fail())
            return OVERFLOWED;//文件打开失败
        int len;
        infile>>len;
        for (int i = 0; i < len; ++i) {
            int r;
            infile>>r;
            ListInsert(i+1,r);//读入元素
        }
        infile.close();
        return OK;
    }
};


class LinkSet{
public:
    typedef struct LinkNode{
        LinkStru linkStru;
        struct LinkNode* next;
    }*sglLinkNode_ptr,sglLinkNode;//每个节点代表一个线性表
private:
    sglLinkNode_ptr setHead;//头节点
    int quantity;//线性表个数
public:
    LinkSet(){//构造函数自动初始化
        InitListSet();
    }

    sglLinkNode_ptr GetNode(int i){//获取该线性表的第i个节点的指针
        sglLinkNode_ptr ptr=setHead;
        for (int j = 1; j <= i; ++j) {
            ptr=ptr->next;
        }
        return ptr;//TODO:返回head不便于随机访问；最好由参数，表示第几个
    }

    int GetQuantity(){//返回个数
        return quantity;
    }
    //func1：初始化线性表集合
    //函数原型：status InitListSet()
    //功能说明：如果线性表集合不存在，操作结果是构造一个空的线性表集合，返回OK，否则返回INFEASIBLE
    // （注意声明对象时已通过构造函数初始化）
    status InitListSet(){
        if (setHead != nullptr)//线性表集合已存在，不能进行初始化
            return INFEASIBLE;
        setHead=(sglLinkNode_ptr)malloc(sizeof(sglLinkNode));
        setHead->linkStru.linkName="\0";
        setHead->next= nullptr;
        if (setHead == nullptr)
            return OVERFLOWED;//初始化失败
        else {//成功初始化
            quantity=0;
            return OK;
        }
    }

//      func2:增加一个新线性表
//      函数原型：status AddList(const string& listName,const vector<ElemType> &elem)
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中增加一个新的空线性表。
    status AddList(const string& listName,const vector<ElemType> &elem) {
        sglLinkNode_ptr newList=(sglLinkNode_ptr)malloc(sizeof(sglLinkNode));
        LinkStru newlink(listName);
        newList->linkStru=newlink;
        newList->next= nullptr;
        for (int i = 0; i < elem.size(); ++i) {//从elem容器内写入元素
            newList->linkStru.ListInsert(i+1,elem[i]);
        }
        sglLinkNode_ptr ptr=setHead;
        for (int i = 0; i < quantity; ++i) {
            ptr=ptr->next;
        }
        ptr->next=newList;//将newList加到线性表集合中
        quantity++;
        return OK;//成功添加
    }

//      func3：移除一个线性表
//      函数原型：status RemoveList(const string& listName)
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名称为ListName的线性表，有则删除，返回OK，无则返回ERROR
    status RemoveList(const string& listName) {
        sglLinkNode_ptr pre_ptr=setHead,ptr=setHead->next ;
        for (int i = 0; i < quantity; ++i) {
            if (ptr->linkStru.linkName==listName){//找到
                pre_ptr->next=ptr->next;//ptr的前驱的next指向ptr的next
                ptr->linkStru.DestroyList();//TODO:在内存查看name的string类到底需不需要释放
                free(ptr);
                quantity--;
                return OK;
            }
            ptr=ptr->next;
            pre_ptr=pre_ptr->next;
        }
        return ERROR;
//        for (int i = 0; i < quantity; ++i) {
//            if (listName==SqLists.elem[i].name){//找到
//                SqLists.elem[i].name="/0";
//                SqLists.elem[i].L.DestroyList();
//                for (int j = i; j < quantity; ++j) {//之后的list前移
//                    SqLists.elem[j]=SqLists.elem[j+1];
//                }
//                quantity--;
//                return OK;
//            }
//        }
//        return ERROR;//TODO：Delete
    }

//      func4:查找线性表
//      函数原型：int LocateList(char ListName[])
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名称为ListName的线性表，有则返回线性表的逻辑序号，无则返回0。
    int LocateList(const string& listName) const {
        sglLinkNode_ptr ptr=setHead->next;
        for (int i = 0; i < quantity; ++i) {
            if (ptr->linkStru.linkName==listName)//found
                return i+1;
            ptr=ptr->next;
        }
        return 0;//遍历后未找到
    }
//      func5：存储线性表集合
//      函数原型：status SaveLists(const string& filepath)
//      功能说明：保存线性表集合的所有数据到filename，成功返回OK，否则返回失败
//      数据存储方式：先写入线性表个数，然后每个线性表依次写入名称，长度，元素，以0表示结束
    status SaveLists(const string& filepath) const{//filepath：文件保存路径
        ofstream outfile;
        string  filename=filepath+"listname.txt";
        outfile.open(filename, ios::out | ios::trunc);
        if (outfile.fail()){//如果打开失败，可能文件夹不存在，创建
            system("mkdir data");
            outfile.open(filename, ios::out | ios::trunc);
            if (outfile.fail())
                return OVERFLOWED;//文件打开失败
        }
        outfile<<quantity<<endl;//首先在listname写入线性表个数和每个线性表的名称
        sglLinkNode_ptr ptr=setHead->next;
        for (int i = 0; i < quantity; ++i) {
            outfile<<ptr->linkStru.linkName<<endl;
            ptr->linkStru.SaveList(filepath);//每个线性表单独写一个文件
            ptr=ptr->next;
        }
        outfile.close();
        return OK;
    }

//      函数原型：status LoadLists(const string& filepath)
//		功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，返回INFEASIBLE；
//		否则将文件名为FileName的数据读入到线性表L中，返回OK。本实验不考虑用追加的方式读入文件数据追加到现有线性表中。
    status LoadLists(const string& filepath){
        if (quantity!=0)
            return INFEASIBLE;//当前线性表已存在，不能加载
        ifstream infile;
        infile.open(filepath+"listname.txt", ios::in);
        if (infile.fail()){
            return OVERFLOWED;//文件打开失败
        }
        infile>>quantity;
        sglLinkNode_ptr tail=setHead;
        for (int i = 0; i < quantity; ++i) {
            sglLinkNode_ptr ptr=(sglLinkNode_ptr)malloc(sizeof(sglLinkNode));
            string  name;
            infile>>name;
            LinkStru newlink(name);//构造函数初始化
            ptr->linkStru=newlink;
            ptr->linkStru.LoadList(filepath);
            tail->next=ptr;
            tail=tail->next;
        }
        infile.close();
        return OK;
    }
};


#endif //EXP_SRC_CLASSDEF_H
