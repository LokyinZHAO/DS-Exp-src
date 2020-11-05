//
// Created by Lokyin Zhao on 2020/9/29.
//

#include <iostream>
#include <sstream>
#include <string>
#include "def.h"
#include "ClassDef.h"

using namespace std;

bool IsdigitAll(string str)//用于判断输入是否全为数字
{
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int ManageSingleList(BinTreeStru &Bitree) {
    int op = 1;
    string input;
    while (op) {
        system("clear");
        cout << endl
             << "      单二叉树管理子菜单 \n"
             << "      \"" << Bitree.name<< "\" " << endl;
        cout << "-------------------------------------------------\n"
             << "\t 1.  二叉树清空\n"
             << "\t 2.  二叉树深度\n"
             << "\t 3.  查找结点\n"
             << "\t 4.  结点赋值\n"
             << "\t 5.  获取兄弟结点\n"
             << "\t 6.  插入结点\n"
             << "\t 7.  删除结点\n"
             << "\t 8.  遍历二叉树\n"
             << "\t 9.  销毁二叉树\n"
             << "\t 0.  返回上级菜单\n"
             << "-------------------------------------------------\n"
             << "请选择你的操作[0~12]:";
        cin >> input;
        if (!IsdigitAll(input)) {//输入有误
            cout << "输入错误，请重新输入！" << endl;
            cout << "键入任意键以继续" << endl;
            getchar();
            getchar();
            continue;
        }
        stringstream strStream;
        strStream << input;
        strStream >> op;//将输入的字符串转化为数字
        int outcome;//标记之后的函数返回值
        switch (op) {
            case 1: {//二叉树清空
                outcome = Bitree.ClearBiTree(Bitree.root);
                if (outcome == OK)
                    printf("成功，二叉树清空！\n");
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 1：二叉树清空

            case 2: {//二叉树深度
                int depth=Bitree.BiTreeDepth(Bitree.root);
                if (depth){
                    cout << "二叉树深度为 " << depth<<" !"<<endl;
                } else{
                    cout<<"二叉树为空！"<<endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 2：二叉树深度

            case 3: {//查找结点
                KeyType key;
                cout<<"请输入查找结点的关键字：";
                cin>>key;
                auto outcome= Bitree.LocateNode(Bitree.root,key);
                if (outcome== nullptr){
                    cout<<"未找到关键字为 "<<key<<" 的结点"<<endl;
                } else {
                    cout<<"关键字为 "<<key<<" 的结点信息: "<<outcome->data.info<<endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 3：查找结点

            case 4: {//结点赋值
                KeyType key;
                BinTreeStru::TElemType value;
                cout<<"请输入要进行赋值的结点关键字:";
                cin >> key;
                cout<<"请输入该节点的新关键字:";
                cin>>value.key;
                cout<<"请输入该节点的信息:";
                cin>>value.info;
                status outcome=Bitree.Assign(Bitree.root, key, value);
                if (outcome==OK) {
                    cout<<"赋值成功"<<endl;
                } else{
                    cout<<"赋值失败，请检查关键字是否存在或新关键字是否重复"<<endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 4：结点赋值

            case 5: {//求二叉树长度
                int len;
                outcome = Bitree.intListLength(len);
                if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树不存在！" << endl;
                else if (outcome == OK) {
                    cout << "二叉树 \"" << listName << "\" 长度为 " << len << " ！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 5:求二叉树长度

            case 6: {//获取元素
                ElemType e;
                int i;
                cout << "请输入要获取的元素序号：" << endl;
                cin >> i;
                outcome = Bitree.GetElem(i, e);
                if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树不存在！" << endl;
                else if (outcome == ERROR)
                    cout << "错误，元素序号不合法！" << endl;
                else {
                    cout << "成功，第 " << i << " 个元素为：" << e << " !" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 6：获取元素

            case 7: {//查找元素
                int i = 0;
                ElemType e;
                cout << "请输入要查找的元素：" << endl;
                cin >> e;
                outcome = Bitree.LocateElem(e, i);
                if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树为空！" << endl;
                else if (outcome == ERROR)
                    cout << "错误，未找到元素 " << e << " !" << endl;
                else {
                    cout << "成功，元素 " << e << " 的序号为 " << i << " !" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 7：查找元素

            case 8: {//获取前驱元素
                ElemType e;
                ElemType pre;
                cout << "请输入一元素以获取其前驱:" << endl;
                cin >> e;
                outcome = Bitree.PriorElem(e, pre);
                if (outcome == OK) {
                    cout << "成功，元素 " << e << " 的前驱为 " << pre << " !" << endl;
                } else if (outcome == INFEASIBLE) {
                    cout << "不可行，二叉树不存在" << endl;
                } else if (outcome == UNEXPECTED) {
                    cout << "元素 " << e << " 为二叉树第一个元素，无前驱元素" << endl;
                } else {
                    cout << "错误，元素 " << e << " 不存在" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 8:获取前驱元素

            case 9: {//获取后继元素
                ElemType e;
                ElemType next;
                cout << "请输入一元素以获取其后继:" << endl;
                cin >> e;
                outcome = Bitree.NextElem(e, next);
                if (outcome == OK) {
                    cout << "成功，元素 " << e << " 的后继为" << next << endl;
                } else if (outcome == INFEASIBLE) {
                    cout << "不可行，二叉树不存在" << endl;
                } else if (outcome == UNEXPECTED) {
                    cout << "元素 " << e << " 为二叉树最后一个元素，无后继元素" << endl;
                } else {
                    cout << "错误，元素 " << e << " 不存在" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 9:获取后继元素

            case 10: {//插入元素
                int i = 0;
                ElemType e;
                cout << "请输入要插入的元素:";
                cin >> e;
                cout << "请输入要插入的位置:";
                cin >> i;
                outcome = Bitree.ListInsert(i, e);
                if (outcome == OK) {
                    cout << "成功,元素 " << e << " 已插入位置 " << i << " ！" << endl;
                } else if (outcome == ERROR) {
                    cout << "错误，位置 " << i << " 不合法！" << endl;
                } else if (outcome == INFEASIBLE) {
                    cout << "不可行，二叉树不存在！" << endl;
                } else {//OVERFLOWED
                    cout << "扩容失败！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 10:插入元素

            case 11: {//删除元素
                int i = 0;
                ElemType e;
                cout << "请输入要删除的元素位置：";
                cin >> i;
                outcome = Bitree.ListDelete(i, e);
                if (outcome == OK)
                    cout << "成功， " << i << " 号位上的元素 " << e << " 已被删除！" << endl;
                else if (outcome == ERROR)
                    cout << "失败，位置 " << i << " 非法！" << endl;
                else {//INFEASIBLE
                    cout << "不可行，二叉树不存在！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 11:删除元素

            case 12: {//遍历二叉树
                outcome = Bitree.ListTraverse(listName);
                if (outcome == OK)
                    cout << "二叉树遍历完成！" << endl;
                else if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树不存在！" << endl;
                else {//ERROR
                    cout << "该二叉树是空表" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of 12:遍历二叉树

            case 0: {
                return 0;//exit
            }//case 0

            default: {
                cout << "输入错误，请重新输入！" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
        }//end of switch
    }//end of while
}

int main() {
    int opt = 1;
    Forest treeSet;
    string input;
    while (opt) {
        system("clear");
        cout << endl
             << "     欢迎使用整型二叉树集合管理系统！" << endl
             << "     二叉树集合操作菜单" << endl
             << "_______________________________________________" << endl
             << "\t1. 初始化二叉树集合" << endl
             << "\t2. 增加一个二叉树" << endl
             << "\t3. 移除一个二叉树" << endl
             << "\t4. 查找二叉树" << endl
             << "\t5. 保存二叉树集合文件" << endl
             << "\t6. 读取二叉树集合文件" << endl
             << "\t7. 操作指定二叉树" << endl
             << "\t8. 查看二叉树" << endl
             << "\t0. 退出系统" << endl
             << "_______________________________________________" << endl
             << "请选择你的操作[0-8]:";
        cin >> input;
        if (!IsdigitAll(input)) {//输入有误
            cout << "输入错误，请重新输入！" << endl;
            cout << "键入任意键以继续" << endl;
            getchar();
            getchar();
            continue;
        }
        stringstream strStream;
        strStream << input;
        strStream >> opt;//将输入的字符串转化为数字
        int outcome;
        switch (opt) {
            case 1: {//初始化二叉树集合
                outcome = treeSet.InitForest();
                if (outcome == OK)
                    cout << "成功，二叉树集合已初始化" << endl;
                else if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树集合已由构造函数初始化" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }

            case 2: {//增加一个二叉树
                string name;
                cout << "请输入新二叉树名称：" << endl;
                cin >> name;
                int checkRecur = treeSet.LocateTree(name);
                if (checkRecur != 0) {//检查是否有重名的二叉树
                    cout << "错误，名为 " << name << " 的二叉树已存在！" << endl;
                    cout << "键入任意键以继续" << endl;
                    getchar();
                    getchar();
                    break;
                }
                outcome = treeSet.AddTree(name);
                if (outcome == OK) {
                    cout << "成功，已添加名为 " << name << " 的二叉树！" << endl;
                } else if (outcome == ERROR) {
                    cout << "输入错误，有重复的标识符！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 3: {//移除一个二叉树
                string name;
                cout << "请输入要移除的二叉树名称：" << endl;
                cin >> name;
                outcome = treeSet.RemoveTree(name);
                if (outcome == OK)
                    cout << "成功，名为 " << name << " 的二叉树被移除！" << endl;
                else if (outcome == ERROR)
                    cout << "错误，未找到名为 " << name << " 的二叉树！" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 4: {//查找二叉树
                string name;
                cout << "请输入要查找的二叉树名称：" << endl;
                cin >> name;
                int location = treeSet.LocateTree(name);
                if (location) {
                    cout << "成功，找到名为 " << name << " 的二叉树在 " << location << " 号位！" << endl;
                } else {
                    cout << "错误，未找到名为 " << name << " 的二叉树！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 5: {//保存二叉树集合
                outcome = treeSet.SaveForest(SavePath);
                if (outcome == OVERFLOWED) {
                    cout << "打开文件失败！" << endl;
                } else if (outcome == OK) {
                    cout << "成功，文件路径为：" << SavePath << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 6: {//读取二叉树集合
                string filename = "./data/";
                outcome =treeSet.LoadForest(filename);
                if (outcome == OK)
                    cout << "二叉树集合数据读取成功！" << endl;
                else if (outcome == INFEASIBLE)
                    cout << "不可行，二叉树集合已存在！" << endl;
                else {//OVERFLOWED
                    cout << "文件打开失败！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 7: {//操作指定二叉树
                int idx;
                cout << "请输入要操作的二叉树序号：" << endl;
                cin >> idx;
                if (idx < 1 || idx > treeSet.forest.size()) {
                    cout << "错误，序号为 " << idx << " 的二叉树不存在" << endl;
                    cout << "键入任意键以继续" << endl;
                    getchar();
                    getchar();
                    break;
                } else {
                    idx--;
                    int sta = ManageSingleList(treeSet.forest[idx]);
                    if (sta == 1) {//执行了二叉树销毁
                        string name = treeSet.forest[idx].name;//记录被销毁的二叉树名称
                        treeSet.RemoveTree(name);
                        cout << "二叉树 " << name << " 已被销毁并移除，即将返回上级菜单" << endl;
                        cout << "键入任意键以继续" << endl;
                        getchar();
                        getchar();
                    }
                }
                break;
            }
            case 8: {//查看二叉树
                if (treeSet.forest.empty()) {
                    cout << "不存在任何二叉树！" << endl;
                } else {
                    cout << "存在的二叉树：" << endl;
                    for (int i = 0; i <treeSet.forest.size(); ++i) {
                        cout << i + 1 << ". " <<treeSet.forest[i].name << endl;
                    }
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 0: {
                cout << "确定退出系统（Y/N）：";
                char cmd;
                cin >> cmd;
                if (cmd == 'N') {
                    opt = 1;
                }
                break;//exit;
            }
            default: {
                cout << "输入错误，请重新输入！" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
        }//end of switch

    }//end of while

}
