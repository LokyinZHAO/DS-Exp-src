//
// Created by Lokyin Zhao on 2020/11/19.
//
#include "def.h"
#include "ClassDef.h"
#include <iostream>
#include <sstream>
#include <string>

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

int ManageSingleList(Graph &G) {
    int op = 1;
    string input;
    while (op) {
        system("clear");
        cout << endl
             << "      单图管理子菜单 \n"
             << "      \"" << G.name << "\" " << endl;
        cout << "-------------------------------------------------\n"
             << "\t 1.  销毁图\n"
             << "\t 2.  查找顶点\n"
             << "\t 3.  顶点赋值\n"
             << "\t 4.  获得第一邻接点\n"
             << "\t 5.  获得下一邻接点\n"
             << "\t 6.  插入顶点\n"
             << "\t 7.  删除顶点\n"
             << "\t 8.  插入弧\n"
             << "\t 9.  删除弧\n"
             << "\t 10. 图遍历\n"
             << "\t 11. 邻接表(DEBUG)\n"
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
            case 1: {//销毁图
                outcome = G.DestroyGraph();
                if (outcome == OK)
                    return 1;//清空后返回上级菜单
                break;
            }//end of case 1：图清空

            case 2: {//查找顶点
                KeyType key;
                cout << "请输入查找顶点的关键字：";
                cin >> key;
                auto outcome = G.LocateVex(key);
                if (outcome == -1) {
                    cout << "未找到关键字为 " << key << " 的顶点" << endl;
                } else {
                    cout << "关键字为 " << key << " 的顶点信息: " << G.G.vertices[outcome].data.info << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 2：查找顶点

            case 3: {//顶点赋值
                KeyType key;
                VertexType value;
                cout << "请输入要进行赋值的顶点关键字:";
                cin >> key;
                cout << "请输入该节点的新关键字:";
                cin >> value.key;
                cout << "请输入该节点的信息:";
                cin >> value.info;
                status outcome = G.PutVex(key, value);
                if (outcome == OK) {
                    cout << "赋值成功" << endl;
                } else {
                    cout << "赋值失败，请检查关键字是否存在或新关键字是否重复" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 4：顶点赋值

            case 4: {//获得第一邻接点
                KeyType key;
                cout << "请输入要查找的顶点关键字：";
                cin >> key;
                int outcome = G.FirstAdjVex(key);
                if (outcome != -1) {
                    cout << "关键字为 " << key << " 的顶点的第一邻接点为:" << endl
                         << "关键字:" << G.G.vertices[outcome].data.key << endl
                         << "顶点信息:" << G.G.vertices[outcome].data.info << endl;
                } else {//两种可能：关键字不存在，无第一邻接点
                    if (G.LocateVex(key) != -1) {
                        cout << "关键字为 " << key << " 的顶点无第一邻接点" << endl;
                    } else {
                        cout << "未找到关键字为 " << key << " 的顶点" << endl;
                    }

                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 5:获得第一邻接点

            case 5: {//获得下一邻接点
                cout << "请依次输入关键字以及其一个邻接点：";
                KeyType key;
                cin >> key;
                KeyType u;
                cin >> u;
                int outcome = G.NextAdjVex(key, u);
                if (outcome != -1) {
                    cout << "关键字为 " << key << " 的顶点关于关键字为 " << u << " 的结点的下一邻接点为" << endl
                         << G.G.vertices[outcome].data.key << "\t" << G.G.vertices[outcome].data.info << endl;
                } else {//ERROR
                    cout << "错误，未找到该顶点或关键字为 " << u << " 的结点为最后一个邻接点" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 5：获得下一邻接点

            case 6: {//插入顶点
                cout << "请输入要插入的顶点的关键字以及其信息:";
                VertexType newV;
                cin >> newV.key >> newV.info;
                status outcome = G.InsertVex(newV);
                if (outcome == OK) {
                    cout << "插入成功" << endl;
                } else {
                    cout << "插入失败，请检查顶点数是否超过规定大小或关键字是否重复" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 6：插入顶点

            case 7: {//删除顶点
                cout << "请输入要删除的顶点的关键字：";
                KeyType key;
                cin >> key;
                status outcome = G.DeleteVex(key);
                if (outcome == OK) {
                    cout << "删除成功" << endl;
                } else {//ERROR
                    cout << "错误，未找到关键字为 " << key << " 的顶点" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 7：删除顶点

            case 8: {//插入弧
                cout << "请输入要插入的弧的两个邻接点的关键字：";
                KeyType v, w;
                cin >> v >> w;
                status outcome = G.InsertArc(v, w);
                if (outcome == OK) {
                    cout << "插入成功" << endl;
                } else {
                    cout << "错误，请检查结点是否存在或弧是否已存在" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 8：插入弧

            case 9: {//删除弧
                cout << "请输入要删除的弧两个邻接点的关键字：";
                KeyType v, w;
                cin >> v >> w;
                status outcome = G.DeleteArc(v, w);
                if (outcome == OK) {
                    cout << "删除成功" << endl;
                } else {//ERROR
                    cout << "错误，请检查输入是否正确" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 9：删除弧

            case 10: {//遍历图
                cout << "深度优先搜索遍历：" << endl;
                G.DFSTraverse();
                cout << endl << "广度优先搜索遍历：" << endl;
                G.BFSTraverse();
                cout << endl << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }//end of case 10:遍历图

            case 11: {//邻接表
                G.AdjTabul();
                getchar();
                getchar();
                break;
            }

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
    GraphSet GraphS;
    string input;
    while (opt) {
        system("clear");
        cout << endl
             << "     欢迎使用整型图集合管理系统！" << endl
             << "     图集合操作菜单" << endl
             << "_______________________________________________" << endl
             << "\t1. 初始化图集合" << endl
             << "\t2. 增加一个图" << endl
             << "\t3. 移除一个图" << endl
             << "\t4. 查找图" << endl
             << "\t5. 保存图集合文件" << endl
             << "\t6. 读取图集合文件" << endl
             << "\t7. 操作指定图" << endl
             << "\t8. 查看图集合" << endl
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
            case 1: {//初始化图集合
                outcome = GraphS.InitGraphSet();
                if (outcome == OK)
                    cout << "成功，图集合已初始化" << endl;
                else if (outcome == INFEASIBLE)
                    cout << "不可行，图集合已初始化" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }

            case 2: {//增加一个图
                string name;
                cout << "请输入新图名称：" << endl;
                cin >> name;
                int checkRecur = GraphS.LocateGraph(name);
                if (checkRecur != 0) {//检查是否有重名的图
                    cout << "错误，名为 " << name << " 的图已存在！" << endl;
                    cout << "键入任意键以继续" << endl;
                    getchar();
                    getchar();
                    break;
                }
                outcome = GraphS.AddGraph(name);
                if (outcome == OK) {
                    cout << "成功，已添加名为 " << name << " 的图！" << endl;
                } else if (outcome == ERROR) {
                    cout << "错误，请检查输入是否正确！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 3: {//移除一个图
                string name;
                cout << "请输入要移除的图名称：" << endl;
                cin >> name;
                status outcome = GraphS.RemoveGraph(name);
                if (outcome == OK)
                    cout << "成功，名为 " << name << " 的图被移除！" << endl;
                else if (outcome == ERROR)
                    cout << "错误，未找到名为 " << name << " 的图！" << endl;
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 4: {//查找图
                string name;
                cout << "请输入要查找的图名称：" << endl;
                cin >> name;
                int location = GraphS.LocateGraph(name);
                if (location) {
                    cout << "成功，找到名为 " << name << " 的图在 " << location << " 号位！" << endl;
                } else {
                    cout << "错误，未找到名为 " << name << " 的图！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 5: {//保存图集合
                outcome = GraphS.SaveGSet();
                if (outcome == OVERFLOWED) {
                    cout << "打开文件失败！" << endl;
                } else if (outcome == OK) {
                    cout << "成功，文件路径为：" << FILE_PATH << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 6: {//读取图集合
                outcome = GraphS.LoadGSet();
                if (outcome == OK)
                    cout << "图集合数据读取成功！" << endl;
                else if (outcome == INFEASIBLE)
                    cout << "不可行，图集合已存在！" << endl;
                else {//OVERFLOWED
                    cout << "文件打开失败！" << endl;
                }
                cout << "键入任意键以继续" << endl;
                getchar();
                getchar();
                break;
            }
            case 7: {//操作指定图
                int idx;
                cout << "请输入要操作的图序号：" << endl;
                cin >> idx;
                if (idx < 1 || idx > GraphS.GSet.size()) {
                    cout << "错误，序号为 " << idx << " 的图不存在" << endl;
                    cout << "键入任意键以继续" << endl;
                    getchar();
                    getchar();
                    break;
                } else {
                    idx--;
                    int sta = ManageSingleList(GraphS.GSet[idx]);
                    if (sta == 1) {//执行了图销毁
                        string name = GraphS.GSet[idx].name;//记录被销毁的图名称
                        GraphS.RemoveGraph(name);
                        cout << "图 " << name << " 已被销毁并移除，即将返回上级菜单" << endl;
                        cout << "键入任意键以继续" << endl;
                        getchar();
                        getchar();
                    }
                }
                break;
            }
            case 8: {//查看图
                if (GraphS.GSet.empty()) {
                    cout << "不存在任何图！" << endl;
                } else {
                    cout << "存在的图：" << endl;
                    for (int i = 0; i < GraphS.GSet.size(); ++i) {
                        cout << i + 1 << ". " << GraphS.GSet[i].name << endl;
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
