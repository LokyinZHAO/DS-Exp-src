//
// Created by Lokyin Zhao on 2020/11/19.
//

#ifndef EXP_SRC_CLASSDEF_H
#define EXP_SRC_CLASSDEF_H

#include <queue>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Graph {//定义单个无向图的类
public:
    typedef enum {
        DG, DN, UDG, UDN
    } GraphKind;

    typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号
        struct ArcNode *nextarc;       //下一个表结点指针
    } ArcNode;

    typedef struct VNode {                //头结点及其数组类型定义
        VertexType data;        //顶点信息
        ArcNode *firstarc = nullptr;         //指向第一条弧
    } VNode, AdjList[MAX_VERTEX_NUM];

    typedef struct {  //邻接表的类型定义
        AdjList vertices;         //头结点数组
        int vexnum = 0, arcnum = 0;      //顶点数、弧数
        GraphKind kind;        //图的类型
    } ALGraph;

    ALGraph G;//图的邻接表
    string name;//图名称

    //func1:创建无向图
    //功能说明：根据顶点序列V和关系对序列VR构造一个无向图G（要求无向图G中各顶点关键字具有唯一性）。
    status CreateCraph(VertexType V[], KeyType VR[][2]) {
        if (G.vexnum != 0) {//图已存在
            return INFEASIBLE;
        }
        G.kind = UDG;//无向图
        G.vexnum = 0;
        for (int i = 0; V[i].key != -1; ++i) {//求出顶点数（函数中对数组的实际长度是不可见的，不能使用sizeof
            G.vexnum++;
        }
        G.arcnum = 0;
        for (int i = 0; VR[i][0] != -1; ++i) {//求出弧的数量
            G.arcnum++;
        }
        //首先检查输入是否正确
        if (G.vexnum > 20)//顶点数超过规定大小
            return ERROR;

        for (int i = 0; i < G.vexnum; ++i) {//初始化邻接表,输入顶点数据
            G.vertices[i].data = V[i];
            G.vertices[i].firstarc = nullptr;
        }
        for (int i = 0; i < G.vexnum; ++i) {//检查关键字唯一
            for (int j = i + 1; j < G.vexnum; ++j) {
                if (G.vertices[i].data.key == G.vertices[j].data.key)
                    return ERROR;//关键字不唯一
            }
        }
        for (int i = 0; i < G.arcnum; ++i) {//依次将VR中的数据输入到邻接表中
            int head = -1;//标记弧头地址(为方便区分定义VR[j][1]为弧头）
            int tail = -1;//标记弧尾地址
            for (int j = 0; j < G.vexnum; ++j) {
                if (G.vertices[j].data.key == VR[i][1]) {
                    head = j;
                }
                if (G.vertices[j].data.key == VR[i][0]) {
                    tail = j;
                }
            }
            if (head == -1 || tail == -1) {//弧的端点不存在
                return ERROR;
            }
            for (int j = 0; j < G.vexnum; ++j) {
                if (G.vertices[j].data.key == VR[i][0]) {//匹配到弧尾
                    //插入方式：后进先出
                    auto newArc = (ArcNode *) malloc(sizeof(ArcNode));
                    newArc->adjvex = head;
                    newArc->nextarc = G.vertices[j].firstarc;
                    G.vertices[j].firstarc = newArc;
                }
                if (G.vertices[j].data.key == VR[i][1]) {//匹配到弧头
                    auto newArc = (ArcNode *) malloc(sizeof(ArcNode));
                    newArc->adjvex = tail;
                    newArc->nextarc = G.vertices[j].firstarc;
                    G.vertices[j].firstarc = newArc;
                }
            }

        }
        return OK;
    }

    //func2:销毁图
    //功能说明：将邻接表表示的无向图销毁，并释放所有表结点的空间。
    status DestroyGraph() {
        {
            for (int i = 0; i < G.vexnum; ++i) {
                ArcNode *p = G.vertices[i].firstarc;
                while (p) {
                    ArcNode *deletion = p;
                    p = p->nextarc;
                    free(deletion);
                }
                G.vertices[i].firstarc = nullptr;
            }
            G.vexnum = 0;
            G.arcnum = 0;
        }
        return OK;
    }

    //func3:查找顶点
    //功能说明：u是和G中顶点关键字类型相同的给定值；根据u查找顶点，成功时返回关键字为u的顶点位置序号（简称位序），否则返回-1
    int LocateVex(KeyType u) const {
        for (int i = 0; i < G.vexnum; ++i) {
            if (G.vertices[i].data.key == u) {
                return i;
            }
        }
        return -1;
    }

    //func4:顶点赋值
    //功能说明：u是和G中顶点关键字类型相同的给定值；操作结果是对关键字为u的顶点赋值value（要求关键字具有唯一性）。成功赋值返回OK，否则返回ERROR。
    status PutVex(KeyType u, VertexType value) {
        for (int i = 0; i < G.vexnum; ++i) {
            if (G.vertices[i].data.key == value.key && value.key != u)
                return ERROR;
        }
        for (int i = 0; i < G.vexnum; ++i) {
            if (G.vertices[i].data.key == u) {
                G.vertices[i].data = value;
                return OK;
            }
        }
        return ERROR;//未找到关键字
    }

    //func5:获得第一邻接点
    //功能说明：u是和G中顶点关键字类型相同的给定值；返回关键字为u的顶点第一个邻接顶点位置序号（简称位序），否则返回-1。
    int FirstAdjVex(KeyType u) const {
        int location = LocateVex(u);
        if (location != -1 && G.vertices[location].firstarc) {
            return G.vertices[location].firstarc->adjvex;
        }
        return -1;
    }

    //func6:获得下一邻接点
    //功能说明：v和w是G中两个顶点的位序，v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
    int NextAdjVex(KeyType v, KeyType w) const {
        int location = LocateVex(v);
        int w_location = LocateVex(w);
        if (location != -1 && G.vertices[location].firstarc) {
            ArcNode *arc_ptr = G.vertices[location].firstarc;
            while (arc_ptr->nextarc != nullptr) {//只需检查到倒数第二个结点
                if (arc_ptr->adjvex == w_location) {
                    return arc_ptr->nextarc->adjvex;
                }
                arc_ptr = arc_ptr->nextarc;
            }
            return -1;
        }
        return -1;
    }

    //func7:插入顶点
    //功能说明：在图G中插入新顶点关v（要求关键字具有唯一性）。成功赋值返回OK，否则返回ERROR。
    status InsertVex(VertexType v) {
        if (G.vexnum == 20)//超出上限
            return ERROR;
        for (int i = 0; i < G.vexnum; ++i) {//检查关键词重复
            if (G.vertices[i].data.key == v.key)
                return ERROR;
        }
        G.vertices[G.vexnum].data = v;
        G.vertices[G.vexnum].firstarc = nullptr;
        G.vexnum++;
        return OK;
    }

    //func8:删除顶点
    //功能说明：v是和G中顶点关键字类型相同的给定值；操作结果是在图G中删除关键字v对应的顶点以及相关的弧。成功赋值返回OK，否则返回ERROR。
    status DeleteVex(KeyType v) {
        int location = LocateVex(v);
        if (location == -1)//不存在顶点v
            return ERROR;
        if (G.vexnum == 1 && location == 0)//删除唯一的顶点
            return ERROR;
        ArcNode *p = G.vertices[location].firstarc;
        if (p) {//该节点有弧
            while (p) {
                int w = G.vertices[p->adjvex].data.key;
                p = p->nextarc;
                DeleteArc(v, w);//删除弧,free()
            }
        }//此时v顶点已经没有弧，删除v
        for (int i = 0; i < G.vexnum; ++i) {//对各个顶点进行修改，如果该顶点有弧与位序大于location的，位序--
            p = G.vertices[i].firstarc;
            if (p) {
                while (p) {
                    if (p->adjvex > location)
                        p->adjvex--;
                    p = p->nextarc;
                }
            }
        }
        for (int i = location; i < G.vexnum; ++i) {//移动
            G.vertices[i] = G.vertices[i + 1];
        }
        G.vexnum--;
        return OK;
    }

    //func9:插入弧
    //功能说明：v、w是和G中顶点关键字类型相同的给定值；操作结果是在图G中增加弧<v,w>。成功赋值返回OK，否则返回ERROR。
    status InsertArc(KeyType v, KeyType w) {
        int v_loc = LocateVex(v);
        int w_loc = LocateVex(w);
        if (v_loc == -1 || w_loc == -1) {
            return ERROR;//结点不存在
        }
        auto p = G.vertices[v_loc].firstarc;
        while (p) {
            if (p->adjvex == w_loc)
                return ERROR;//弧已经存在
            p = p->nextarc;
        }
        auto newArc = (ArcNode *) malloc(sizeof(ArcNode));
        newArc->nextarc = G.vertices[v_loc].firstarc;
        newArc->adjvex = w_loc;
        G.vertices[v_loc].firstarc = newArc;
        newArc = (ArcNode *) malloc(sizeof(ArcNode));
        newArc->nextarc = G.vertices[w_loc].firstarc;
        newArc->adjvex = v_loc;
        G.vertices[w_loc].firstarc = newArc;
        return OK;
    }

    //func10:删除弧
    //功能说明：v、w是和G中顶点关键字类型相同的给定值；操作结果是在图G中删除弧<v,w>。成功赋值返回OK，否则返回ERROR。
    status DeleteArc(KeyType v, KeyType w) {
        int v_loc = LocateVex(v);
        int w_loc = LocateVex(w);
        if (v_loc == -1 || w_loc == -1) {
            return ERROR;//顶点不存在
        }
        if (!G.vertices[v_loc].firstarc || !G.vertices[w_loc].firstarc)//顶点无弧
            return ERROR;
        ArcNode *p = G.vertices[v_loc].firstarc;
        int v_flag = 0, w_flag = 0;
        if (p->adjvex == w_loc) {
            G.vertices[v_loc].firstarc = p->nextarc;
            free(p);
            v_flag = 1;
        } else {
            while (p->nextarc) {//删除
                if (p->nextarc->adjvex == w_loc) {//匹配
                    ArcNode *deletion = p->nextarc;
                    p->nextarc = deletion->nextarc;
                    free(deletion);
                    v_flag = 1;
                    break;
                }
                p = p->nextarc;
            }
        }
        p = G.vertices[w_loc].firstarc;
        if (p->adjvex == v_loc) {
            G.vertices[w_loc].firstarc = p->nextarc;
            free(p);
            w_flag = 1;
        } else {
            while (p->nextarc) {//删除
                if (p->nextarc->adjvex == v_loc) {//匹配
                    ArcNode *deletion = p->nextarc;
                    p->nextarc = deletion->nextarc;
                    free(deletion);
                    w_flag = 1;
                    break;
                }
                p = p->nextarc;
            }
        }
        if (!v_flag || !w_flag)//不存在这样的弧
            return ERROR;
        return OK;
    }

    //func11:深度优先搜索遍历
    //功能说明：对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次。
    bool visited[MAX_VERTEX_NUM];

    void visit(VertexType v) const {
        cout << v.key << " " << v.info << " ";
    }

    status DFSTraverse() {
        // 请在这里补充代码，完成本关任务
        /********** Begin *********/
        for (int i = 0; i < G.vexnum; ++i) {
            visited[i] = false;
        }
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited[i]) {
                DFS(i);
            }
        }
    }

    void DFS(int i) {
        visited[i] = true;
        visit(G.vertices[i].data);
        for (int w = FirstAdjVex(G.vertices[i].data.key);
             w >= 0; w = NextAdjVex(G.vertices[i].data.key, G.vertices[w].data.key)) {
            if (!visited[w]) DFS(w);
        }
    }

    //func12:广深度优先搜索遍历
    //功能说明：对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次。
    status BFSTraverse() {

        for (int i = 0; i < G.vexnum; ++i) {
            visited[i] = false;
        }
        std::queue<int> queue;
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited[i]) {
                visited[i] = true;
                visit(G.vertices[i].data);//标记访问后立即访问
                queue.push(i);//进队
                while (!queue.empty()) {
                    int u = queue.front();
                    queue.pop();
                    for (int w = FirstAdjVex(G.vertices[u].data.key);
                         w >= 0; w = NextAdjVex(G.vertices[u].data.key, G.vertices[w].data.key)) {
                        if (!visited[w]) {
                            visited[w] = true;
                            visit(G.vertices[w].data);
                            queue.push(w);
                        }
                    }

                }
            }
        }
        return OK;
    }

    //func13:存储图
    //功能说明：函数SaveGraph实现将图G写到文件名为FileName的文件中，返回OK；
    status SaveGraph() const
//将图的数据写入到文件FileName中
    {
        using namespace std;
        string FileName = FILE_PATH;
        ofstream outfile;
        outfile.open(FileName + name + ".txt", ios::out | ios::trunc);
        if (outfile.fail()) {//如果打开失败，可能文件夹不存在，创建
            system("mkdir data");
            outfile.open(FileName, ios::out | ios::trunc);
            if (outfile.fail()) {
                return OVERFLOW;
            }//文件打开失败
        }
        //按照邻接表存储
        outfile << G.vexnum << " " << G.arcnum << endl;
        for (int i = 0; i < G.vexnum; ++i) {
            outfile << G.vertices[i].data.key << " " << G.vertices[i].data.info << endl;
            for (int w = FirstAdjVex(G.vertices[i].data.key);
                 w >= 0; w = NextAdjVex(G.vertices[i].data.key, G.vertices[w].data.key)) {
                outfile << w << endl;
            }
            outfile << "-1" << endl;
        }
        outfile << "-1 -1" << endl;
        outfile.close();
        return OK;
        /********** End 1 **********/
    }

    //func14:读取图
    //功能说明：函数 LoadGraph读入文件名为FileName的结点数据，创建无向图的邻接表。
    status LoadGraph(string FileName) {
        using namespace std;
        ifstream infile;
        infile.open(FileName);
        infile >> G.vexnum >> G.arcnum;
        G.kind = UDG;
        for (int i = 0; i < G.vexnum; ++i) {
            infile >> G.vertices[i].data.key >> G.vertices[i].data.info;
            int arc;
            infile >> arc;
            if (arc != -1) {
                G.vertices[i].firstarc = (ArcNode *) malloc(sizeof(ArcNode));
                G.vertices[i].firstarc->adjvex = arc;
                G.vertices[i].firstarc->nextarc = nullptr;
                infile >> arc;
            }
            ArcNode *p = G.vertices[i].firstarc;
            while (arc != -1) {
                ArcNode *newArc = (ArcNode *) malloc(sizeof(ArcNode));
                newArc->adjvex = arc;
                newArc->nextarc = nullptr;
                p->nextarc = newArc;
                p = newArc;
                infile >> arc;
            }
        }
        infile.close();
        return OK;
    }

    status  AdjTabul(){
        for (int i = 0; i < G.vexnum; ++i) {
            cout<<G.vertices[i].data.key<<" "<<G.vertices[i].data.info<<":";
            if (G.vertices[i].firstarc){
                cout<<" "<<G.vertices[i].firstarc->adjvex;
                ArcNode *p=G.vertices[i].firstarc->nextarc;
                while (p){
                    cout<<" "<<p->adjvex;
                    p=p->nextarc;
                }
            }
            cout<<endl;
        }
    }
};

class GraphSet {//定义无向图集合的类
public:
    vector<Graph> GSet;//利用向量容器对多个图进行管理

    //func1：初始化图集合
    //功能说明：如果森林不存在，操作结果是构造一个空的二叉树顺序表集合，返回OK，否则返回INFEASIBLE
    // （注意声明对象时已通过构造函数初始化）
    status InitGraphSet() {
        if (!GSet.empty()) {//已经存在图不可初始化
            return INFEASIBLE;
        }
        return OK;//vector自动初始化
    }

    //func2:增加一个图
    //功能说明：向Gset中新增加一个图
    status AddGraph(const string &GName) {
        Graph newG;
        VertexType V[MAX_VERTEX_NUM];
        KeyType VR[100][2];
        cout << "请输入顶点信息,以 -1 -1 结束：" << endl;
        VertexType V_in;
        cin >> V_in.key >> V_in.info;//读入顶点数据
        int i = 0;
        while (V_in.key != -1) {
            V[i] = V_in;
            i++;
            cin >> V_in.key >> V_in.info;
        }
        V[i] = V_in;
        cout << "请输入边信息,以 -1 -1结束：" << endl;
        i = 0;
        KeyType k_in[2];
        cin >> k_in[0] >> k_in[1];
        while (k_in[0] != -1) {
            VR[i][0] = k_in[0];
            VR[i][1] = k_in[1];
            i++;
            cin >> k_in[0] >> k_in[1];
        }
        VR[i][0] = k_in[0];
        VR[i][1] = k_in[1];
        newG.name = GName;
        if (newG.CreateCraph(V, VR) == OK) {
            GSet.push_back(newG);
            return OK;
        } else
            return ERROR;
    }

    //func3:移除一个图
    //功能说明：在集合中查找名为GName的图，有则删除，返回OK，否则返回ERROR
    status RemoveGraph(const string &treeName) {
        for (auto iter = GSet.begin(); iter != GSet.end(); iter++) {//利用容器的迭代器
            if (iter->name == treeName) {//找到
                iter->DestroyGraph();//销毁
                GSet.erase(iter);//删除
                return OK;
            }
        }
        return ERROR;//未找到
    }

    //func4:查找图
    //功能说明：在集合中查找名为GName的图，有则返回位序，否则返回0
    int LocateGraph(const string &GName) const {
        for (int i = 0; i < GSet.size(); ++i) {
            if (GName == GSet[i].name) {//找到
                return i + 1;
            }
        }
        return 0;//未找到
    }

    //func5：存储图集合
    //功能说明：将图集合中的所有数据存储到指定位置，每个图以其名字单独成一个文件
    status SaveGSet() const {
        ofstream outfile;
        string filepath = FILE_PATH;
        outfile.open(filepath + "TreeName.txt", ios::out | ios::trunc);
        if (outfile.fail()) {//如果打开失败，可能文件夹不存在，创建
            system("mkdir data");
            outfile.open(filepath + "TreeName.txt", ios::out | ios::trunc);
            if (outfile.fail())
                return OVERFLOWED;//文件打开失败
        }
        outfile << GSet.size() << endl;//首先写入元素个数
        for (int i = 0; i < GSet.size(); ++i) {
            outfile << GSet[i].name << endl;
            GSet[i].SaveGraph();
        }
        outfile.close();
        return OK;
    }

    //func6:读取图集合
    //功能说明：从指定路径中按照存储方式读取图集合
    status LoadGSet() {
        if (GSet.size())
            return INFEASIBLE;//集合中已经有数据，不可行
        ifstream infile;
        string filepath = FILE_PATH;
        infile.open(filepath + "TreeName.txt", ios::in);
        if (infile.fail()) {
            return OVERFLOWED;
        }
        int quantity;
        infile >> quantity;
        for (int i = 0; i < quantity; ++i) {
            Graph newG;
            infile >> newG.name;
            newG.LoadGraph(filepath + newG.name + ".txt");
            GSet.push_back(newG);
        }
        infile.close();
        return OK;
    }
};

#endif //EXP_SRC_CLASSDEF_H
