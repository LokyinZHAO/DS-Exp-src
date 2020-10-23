//
// Created by Lokyin Zhao on 2020/10/16.
//

#ifndef EXP_SRC_CLASSDEF_H
#define EXP_SRC_CLASSDEF_H
#include <fstream>
#include "def.h"
#include <fstream>

using namespace std;

class LinkStru{//定义一个链表的线性表的数据抽象
public:
    typedef struct LNode{  //单链表（链式结构）结点的定义
        ElemType data;
        struct LNode *next;
    }LNode,*LinkList;
private:
    LinkList head;//头指针
    LinkStru(){
        InitList();//构造函数初始化
    }
public:
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
//函数名原型：status ListLength()
//若线性表L不存在，则返回INFEASIBLE；否则返回线性表L的长度。
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
        LinkList q=head->next;
        for (int j= 1; j <= head->data; ++j) {//依次遍历访问到第i个节点
            if (j==i){
                e=q->data;
                return OK;
            }
            q=q->next;
        }
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
        LinkList q=head ,p=head ->next;
        if (head->data==0)
            return ERROR;//空表，直接返回为"未找到元素"，不再查找
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
        LinkList p=head->next,q=p->next;//p指向首元素
        while (q!= nullptr){
            if (p->data==e){
                next=q->data;//访问后继
                return OK;
            }
            p=p->next;
            q=q->next;
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
                LinkList next=p->next;
                p->next=(LinkList)malloc(sizeof(LNode));
                p->next->data=e;
                p->next->next=next;
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
                LinkList next=p->next->next;
                e=p->next->data;
                free(p->next);
                p->next=next;
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
//函数原型：status SaveList(string filepath,string filename)
//功能说明：如果线性表L不存在，返回INFEASIBLE；否则将线性表L的全部元素写入到文件名为filename的文件中，返回OK。
    status SaveList(const string& filepath,const string& filename){
        if (head== nullptr)//线性表不存在
            return INFEASIBLE;
        ofstream outfile;
        outfile.open(filepath+filename+".txt",ios::out|ios::trunc);
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
//函数原型：status LoadList(string filepath, string filename)
//功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，返回INFEASIBLE；否则将文件名为filename的数据读入到线性表L中，返回OK。
    status LoadList(const string& filepath, const string& filename){
        if (head->data!=0)
            return INFEASIBLE;//线性表中已经有元素，不可行
        ifstream infile;
        infile.open(filepath+filename+".txt",ios::in);
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
    typedef struct{  //线性表集合的管理表定义
        typedef struct {//每个线性表元素包含一个线性表对象和线性表名称
            string  name;
            LinkStru L;
        } *SingleL;

        SingleL elem;
        int sqL_quantity;//顺序表数
        int sqL_size;
    }LISTS;

private:
    LISTS SqLists;
public:
    LinkSet(){//构造函数自动初始化
        InitMultList();
    }
    LISTS Get(){//获取该线性表集合
        return SqLists;
    }
    //func1：初始化线性表集合
    //函数原型：status InitMultList()
    //功能说明：如果线性表集合不存在，操作结果是构造一个空的线性表集合，返回OK，否则返回INFEASIBLE
    // （注意声明对象时已通过构造函数初始化）
    status InitMultList(){
        if (SqLists.elem!=nullptr)//线性表集合已存在，不能进行初始化
            return INFEASIBLE;
        SqLists.elem=(LISTS::SingleL)malloc(sizeof(LISTS::SingleL)*INIT_SIZE);
        if (SqLists.elem==nullptr)
            return OVERFLOWED;//初始化失败
        else {//成功初始化
            SqLists.sqL_quantity=0;
            SqLists.sqL_size=INIT_SIZE;
            return OK;
        }
    }

//      func2:增加一个新线性表
//      函数原型：status AddList(const string& listName)
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中增加一个新的空线性表。
    status AddList(const string& listName) {
        if (SqLists.sqL_quantity==SqLists.sqL_size){//即将溢出，扩容
            LISTS::SingleL newbase=(LISTS::SingleL)realloc(SqLists.elem,sizeof(LISTS::SingleL)*(SqLists.sqL_size+INCREMENT))
            ;
            if (newbase==nullptr)
                return OVERFLOWED;//扩容失败
            else{
                SqLists.elem=newbase;
                SqLists.sqL_size+=INCREMENT;//扩容完成
            }
        }
        //之后对新增线性表初始化
        int outcome=SqLists.elem[SqLists.sqL_quantity].L.InitList();
        if (outcome == OVERFLOWED)
            return OVERFLOWED;//分配失败
        else if (outcome==OK){
            SqLists.elem[SqLists.sqL_quantity].name=listName;
            cout<<"请输入整型线性表数据，空格隔开，以0结尾:"<<endl;//读入数据
            int r;
            cin>>r;
            while (r){
                SqLists.elem[SqLists.sqL_quantity].L.ListInsert(SqLists.elem[SqLists.sqL_quantity].L.GetHead()->data+1,r);
                cin>>r;
            }
            SqLists.sqL_quantity++;
            return OK;//成功添加
        }
    }

//      func3：移除一个线性表
//      函数原型：status RemoveList(const string& listName)
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名称为ListName的线性表，有则删除，返回OK，无则返回ERROR
    status RemoveList(const string& listName) {
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {
            if (listName==SqLists.elem[i].name){//找到
                SqLists.elem[i].name="/0";
                SqLists.elem[i].L.DestroyList();
                for (int j = i; j < SqLists.sqL_quantity; ++j) {//之后的list前移
                    SqLists.elem[j]=SqLists.elem[j+1];
                }
                SqLists.sqL_quantity--;
                return OK;
            }
        }
        return ERROR;
    }

//      func4:查找线性表
//      函数原型：int LocateList(char ListName[])
//      功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名称为ListName的线性表，有则返回线性表的逻辑序号，无则返回0。
    int LocateList(const string& listName) const {
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {
            if (SqLists.elem[i].name==listName)//found
                return i+1;
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
        outfile<<SqLists.sqL_quantity<<endl;//首先在listname写入线性表个数和每个线性表的名称
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {
            outfile<<SqLists.elem[i].name<<endl;
        }
        outfile.close();
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {//逐个线性表创建文件
            SqLists.elem[i].L.SaveList(filepath,SqLists.elem[i].name);
        }
        return OK;
    }

//      函数原型：status LoadLists(const string& filepath)
//		功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，返回INFEASIBLE；
//		否则将文件名为FileName的数据读入到线性表L中，返回OK。本实验不考虑用追加的方式读入文件数据追加到现有线性表中。
    status LoadLists(const string& filepath){
        if (SqLists.sqL_quantity!=0)
            return INFEASIBLE;//当前线性表已存在，不能加载
        ifstream infile;
        infile.open(filepath+"listname.txt", ios::in);
        if (infile.fail()){
            return OVERFLOWED;//文件打开失败
        }
        infile>>SqLists.sqL_quantity;
        if (SqLists.sqL_quantity>SqLists.sqL_size){//扩容
            LISTS::SingleL newbase=(LISTS::SingleL)realloc(SqLists.elem,sizeof(LISTS::SingleL)*(SqLists.sqL_size+INCREMENT))
            ;
            if (newbase==nullptr)
                return OVERFLOWED;//扩容失败
            else{
                SqLists.elem=newbase;
                SqLists.sqL_size+=INCREMENT;//扩容完成
            }
        }//扩容
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {
            infile>>SqLists.elem[i].name;
        }
        infile.close();
        for (int i = 0; i < SqLists.sqL_quantity; ++i) {//依次按照文件名读取
            SqLists.elem[i].L.InitList();//数组中每个元素仍然需要初始化
            SqLists.elem[i].L.LoadList(filepath,SqLists.elem[i].name);
        }
        return OK;
    }
};


#endif //EXP_SRC_CLASSDEF_H
