//
// Created by Lokyin Zhao on 2020/9/29.
//

#include <iostream>
#include <sstream>
#include "def.h"
#include "ClassDef.h"
using namespace std;

bool IsdigitAll(string str)//用于判断输入是否全为数字
{
    for (int i = 0; i<str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int ManageSingleList(SeqStc &sqL,const string& listName) {
    int op=1;
    string input;
    while (op){
        system("clear");
        cout<<endl
            <<"      单线性表管理子菜单 \n"
            <<"      \""<<listName<<"\" "<<endl;
        cout<<"-------------------------------------------------\n"
            <<"\t 1.  初始化线性表\n"
            <<"\t 2.  销毁线性表\n"
            <<"\t 3.  清空线性表\n"
            <<"\t 4.  线性表判空\n"
            <<"\t 5.  求线性表长度\n"
            <<"\t 6.  获取元素\n"
            <<"\t 7.  查找元素\n"
            <<"\t 8.  获取前驱元素\n"
            <<"\t 9.  获取后继元素\n"
            <<"\t10.  插入元素\n"
            <<"\t11.  删除元素\n"
            <<"\t12.  遍历线性表\n"
            <<"\t 0.  返回上级菜单\n"
            <<"-------------------------------------------------\n"
            <<"请选择你的操作[0~12]:";
        cin>>input;
        if (!IsdigitAll(input)){//输入有误
            cout<<"输入错误，请重新输入！"<<endl;
            cout<<"键入任意键以继续"<<endl;
            getchar();getchar();
            continue;
        }
        stringstream strStream;
        strStream<<input;
        strStream>>op;//将输入的字符串转化为数字
        int outcome;//标记之后的函数返回值
        switch(op){
            case 1:{//初始化线性表
                outcome = sqL.InitList();
                if(outcome == OK)
                    printf("成功，线性表已创建！\n");
                else if (outcome == INFEASIBLE)
                    cout<<"不可行，线性表已在创建时初始化！"<<endl;
                else if (outcome == OVERFLOWED)
                    cout<<"分配失败，线性表未创建！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 1：初始化线性表

            case 2: {//销毁线性表
                outcome=sqL.DestroyList();
                if (outcome == OK){
                    return 1;//返回主菜单进行完全销毁操作
                }
                else if (outcome == INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 2：销毁线性表

            case 3:{//清空线性表
                outcome=sqL.ClearList();
                if (outcome == INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                else if(outcome == OK)
                    cout<<"成功，线性表已清空！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 3：清空线性表

            case 4:{//线性表判空
                outcome=sqL.ListEmpty();
                if (outcome==INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                else if (outcome==TRUE)
                    cout<<"线性表 \""<<listName<<"\" 为空表！"<<endl;
                else
                    cout<<"线性表 \""<<listName<<"\" 不为空表！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 4：线性表判空

            case 5:{//求线性表长度
                int len;
                outcome=sqL.intListLength(len);
                if (outcome==INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                else if (outcome==OK){
                    cout<<"线性表 \""<<listName<<"\" 长度为 "<<len<<" ！"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 5:求线性表长度

            case 6:{//获取元素
                ElemType e;
                int i;
                cout<<"请输入要获取的元素序号："<<endl;
                cin>>i;
                outcome=sqL.GetElem(i,e);
                if (outcome==INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                else if (outcome==ERROR)
                    cout<<"错误，元素序号不合法！"<<endl;
                else{
                    cout<<"成功，第 "<<i<<" 个元素为："<<e<<" !"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 6：获取元素

            case 7:{//查找元素
                int i=0;
                ElemType e;
                cout<<"请输入要查找的元素："<<endl;
                cin>>e;
                outcome=sqL.LocateElem(e,i);
                if (outcome==INFEASIBLE)
                    cout<<"不可行，线性表为空！"<<endl;
                else if (outcome==ERROR)
                    cout<<"错误，未找到元素 "<<e<<" !"<<endl;
                else {
                    cout<<"成功，元素 "<<e<<" 的序号为 "<<i<<" !"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 7：查找元素

            case 8:{//获取前驱元素
                ElemType e;
                ElemType pre;
                cout<<"请输入一元素以获取其前驱:"<<endl;
                cin>>e;
                outcome=sqL.PriorElem(e,pre);
                if (outcome==OK){
                    cout<<"成功，元素 "<<e<<" 的前驱为 "<<pre<<" !"<<endl;
                } else if (outcome==INFEASIBLE){
                    cout<<"不可行，线性表不存在"<<endl;
                } else  if (outcome==UNEXPECTED){
                    cout<<"元素 "<<e<<" 为线性表第一个元素，无前驱元素"<<endl;
                }
                else{
                    cout<<"错误，元素 "<<e<<" 不存在"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 8:获取前驱元素

            case 9:{//获取后继元素
                ElemType e;
                ElemType next;
                cout<<"请输入一元素以获取其后继:"<<endl;
                cin>>e;
                outcome=sqL.NextElem(e,next);
                if (outcome==OK){
                    cout<<"成功，元素 "<<e<<" 的后继为"<<next<<endl;
                } else if (outcome==INFEASIBLE){
                    cout<<"不可行，线性表不存在"<<endl;
                } else if (outcome==UNEXPECTED){
                    cout<<"元素 "<<e<<" 为线性表最后一个元素，无后继元素"<<endl;
                }
                else{
                    cout<<"错误，元素 "<<e<<" 不存在"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 9:获取后继元素

            case 10:{//插入元素
                int i=0;
                ElemType e;
                cout<<"请输入要插入的元素:";
                cin>>e;
                cout<<"请输入要插入的位置:";
                cin>>i;
                outcome=sqL.ListInsert(i,e);
                if (outcome==OK){
                    cout<<"成功,元素 "<<e<<" 已插入位置 "<<i<<" ！"<<endl;
                } else  if (outcome==ERROR){
                    cout<<"错误，位置 "<<i<<" 不合法！"<<endl;
                } else  if(outcome==INFEASIBLE){
                    cout<<"不可行，线性表不存在！"<<endl;
                } else{//OVERFLOWED
                    cout<<"扩容失败！"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 10:插入元素

            case 11:{//删除元素
                int i=0;
                ElemType e;
                cout<<"请输入要删除的元素位置：";
                cin>>i;
                outcome=sqL.ListDelete(i,e);
                if (outcome==OK)
                    cout<<"成功， "<<i<<" 号位上的元素 " <<e<<" 已被删除！"<<endl;
                else if(outcome==ERROR)
                    cout<<"失败，位置 "<<i<<" 非法！"<<endl;
                else{//INFEASIBLE
                    cout<<"不可行，线性表不存在！"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of case 11:删除元素

            case 12:{//遍历线性表
                outcome=sqL.ListTraverse(listName);
                if (outcome==OK)
                    cout<<"线性表遍历完成！"<<endl;
                else if (outcome==INFEASIBLE)
                    cout<<"不可行，线性表不存在！"<<endl;
                else{//ERROR
                    cout<<"该线性表是空表"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }//end of 12:遍历线性表

            case 0:{
                return 0;//exit
            }//case 0

          default:{
                cout<<"输入错误，请重新输入！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
        }//end of switch
    }//end of while
}

int main() {
    int opt=1;
    MultiSq Sqs;
    string  input;
    while (opt){
        system("clear");
        cout<<endl
            <<"     欢迎使用整型线性表集合管理系统！"<<endl
            <<"     线性表集合操作菜单"<<endl
            <<"_______________________________________________"<<endl
            <<"\t1. 初始化线性表集合"<<endl
            <<"\t2. 增加一个线性表"<<endl
            <<"\t3. 移除一个线性表"<<endl
            <<"\t4. 查找线性表"<<endl
            <<"\t5. 保存线性表集合文件"<<endl
            <<"\t6. 读取线性表集合文件"<<endl
            <<"\t7. 操作指定线性表"<<endl
            <<"\t8. 查看线性表"<<endl
            <<"\t0. 退出系统"<<endl
            <<"_______________________________________________"<<endl
            <<"请选择你的操作[0-8]:";
        cin>>input;
        if (!IsdigitAll(input)){//输入有误
            cout<<"输入错误，请重新输入！"<<endl;
            cout<<"键入任意键以继续"<<endl;
            getchar();getchar();
            continue;
        }
        stringstream strStream;
        strStream<<input;
        strStream>>opt;//将输入的字符串转化为数字
        int outcome;
        switch (opt) {
            case 1:{//初始化线性表集合
                outcome=Sqs.InitMultList();
                if (outcome == OK)
                    cout<<"成功，线性表集合已初始化"<<endl;
                else if (outcome == INFEASIBLE)
                    cout<<"不可行，线性表集合已由构造函数初始化"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }

            case 2:{//增加一个线性表
                string name;
                cout<<"请输入新线性表名称："<<endl;
                cin>>name;
                int checkRecur=Sqs.LocateList(name);
                if (checkRecur!=0){//检查是否有重名的线性表
                    cout<<"错误，名为 "<<name<<" 的线性表已存在！"<<endl;
                    cout<<"键入任意键以继续"<<endl;
                    getchar();getchar();
                    break;
                }
                outcome=Sqs.AddList(name);
                if (outcome == OVERFLOWED)
                    cout<<"分配空间失败，线性表未创建！"<<endl;
                else if (outcome==OK)
                    cout<<"成功，已添加名为 "<<name<<" 的线性表！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 3:{//移除一个线性表
                string name;
                cout<<"请输入要移除的线性表名称："<<endl;
                cin>>name;
                outcome=Sqs.RemoveList(name);
                if (outcome==OK)
                    cout<<"成功，名为 "<<name<<" 的线性表被移除！"<<endl;
                else if (outcome==ERROR)
                    cout<<"错误，未找到名为 "<<name<<" 的线性表！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 4:{//查找线性表
                string name;
                cout<<"请输入要查找的线性表名称："<<endl;
                cin>>name;
                int location=Sqs.LocateList(name);
                if (location){
                    cout<<"成功，找到名为 "<<name<<" 的线性表在 "<<location<<" 号位！"<<endl;
                } else{
                    cout<<"错误，未找到名为 "<<name<<" 的线性表！"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 5:{//保存线性表集合
                string  filename="./data/";
                outcome=Sqs.SaveLists(filename);
                if (outcome == OVERFLOWED){
                    cout<<"打开文件失败！"<<endl;
                } else  if (outcome==OK){
                    cout<<"成功，文件路径为："<<filename<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 6:{//读取线性表集合
                string filename="./data/";
                outcome= Sqs.LoadLists(filename);
                if (outcome==OK)
                    cout<<"线性表集合数据读取成功！"<<endl;
                else if(outcome==INFEASIBLE)
                    cout<<"不可行，线性表集合已存在！"<<endl;
                else{//OVERFLOWED
                    cout<<"文件打开失败！"<<endl;
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 7:{//操作指定线性表
                int idx;
                cout<<"请输入要操作的线性表序号："<<endl;
                cin>>idx;
                if (idx<1||idx>Sqs.Get().sqL_quantity){
                    cout<<"错误，序号为 "<<idx<<" 的线性表不存在"<<endl;
                    cout<<"键入任意键以继续"<<endl;
                    getchar();getchar();
                    break;
                }
                else {
                    idx--;
                    int sta=ManageSingleList(Sqs.Get().elem[idx].L, Sqs.Get().elem[idx].name);
                    if (sta==1){//执行了线性表销毁
                        string  name=Sqs.Get().elem[idx].name;//记录被销毁的线性表名称
                        Sqs.RemoveList(name);
                        cout<<"线性表 "<<name<<" 已被销毁并移除，即将返回上级菜单"<<endl;
                        cout<<"键入任意键以继续"<<endl;
                        getchar();getchar();
                    }
                }
                break;
            }
            case 8:{//查看线性表
                if (Sqs.Get().sqL_quantity==0){
                    cout<<"不存在任何线性表！"<<endl;
                } else{
                    cout<<"存在的线性表："<<endl;
                    for (int i = 0; i < Sqs.Get().sqL_quantity; ++i) {
                        cout<<i+1<<". "<<Sqs.Get().elem[i].name<<"\t";
                        if (Sqs.Get().elem[i].L.Get().length!=0){
                            cout<<": ";
                            int j;
                            for (j = 0; j < Sqs.Get().elem[i].L.Get().length&&j<5; ++j) {
                                cout<<" "<<Sqs.Get().elem[i].L.Get().elem[j];
                            }
                            if (j==5&&(Sqs.Get().elem[i].L.Get().length!=5))
                                cout<<" ... ("<<Sqs.Get().elem[i].L.Get().length<<")";//大于五个元素的不再显示，并输出省略号
                        }
                        cout<<endl;
                    }
                }
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
            case 0:{
                cout<<"确定退出系统（Y/N）：";
                char cmd;
                cin>>cmd;
                if (cmd=='N'){
                    opt=1;
                }
                break;//exit;
            }
            default:{
                cout<<"输入错误，请重新输入！"<<endl;
                cout<<"键入任意键以继续"<<endl;
                getchar();getchar();
                break;
            }
        }//end of switch

    }//end of while

}
