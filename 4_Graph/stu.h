//
// Created by Lokyin Zhao on 2020/11/19.
//

#ifndef EXP_SRC_STU04_H
#define EXP_SRC_STU04_H

int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data.key == u) {
            return i;
        }
    }
    return -1;
    /********** End **********/
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int v_loc = LocateVex(G, v);
    int w_loc = LocateVex(G, w);
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
    /********** End **********/
}

status DeleteVex(ALGraph &G, KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
// 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location = LocateVex(G, v);
    if (location == -1)//不存在顶点v
        return ERROR;
    if (G.vexnum == 1 && location == 0)//删除唯一的顶点
        return ERROR;
    ArcNode *p = G.vertices[location].firstarc;
    if (p) {//该节点有弧
        while (p) {
            int w = G.vertices[p->adjvex].data.key;
            p = p->nextarc;
            DeleteArc(G, v, w);//删除弧,free()
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

    /********** End **********/
}


bool visited[MAX_VERTEX_NUM];

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location=LocateVex(G,u);
    if(location!=-1&&G.vertices[location].firstarc){
        return G.vertices[location].firstarc->adjvex;
    }
    return -1;
    /********** End **********/
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location=LocateVex(G,v);
    int w_location=LocateVex(G,w);
    if (location!=-1&&G.vertices[location].firstarc){
        ArcNode* arc_ptr=G.vertices[location].firstarc;
        while (arc_ptr->nextarc!= nullptr){//只需检查到倒数第二个结点
            if (arc_ptr->adjvex==w_location){
                return arc_ptr->nextarc->adjvex;
            }
            arc_ptr=arc_ptr->nextarc;
        }
        return -1;
    }
    return -1;
    /********** End **********/
}
void visit(VertexType v);
void DFS(ALGraph &G, int i);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    return OK;
}

    void DFS(ALGraph &G, int i) {
        visited[i]= true;
        visit(G.vertices[i].data);
        for (int w=FirstAdjVex(G,G.vertices[i].data.key);w>=0;w=NextAdjVex(G,G.vertices[i].data.key,w)) {
            if (!visited[w]) DFS(G,w);
        }
/********** End **********/
}

#include <queue>
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i]= false;
    }
    std::queue<int> queue;
    for (int i = 0; i < G.vexnum; ++i) {
        if(!visited[i]){
            visited[i]= true;
            visit(G.vertices[i].data);//标记访问后立即访问
            queue.push(i);//进队
            while (!queue.empty()){
                int u=queue.front();
                queue.pop();
                for (int w=FirstAdjVex(G,G.vertices[u].data.key);w>=0;w=NextAdjVex(G,G.vertices[u].data.key,G.vertices[w].data.key)) {
                    if (!visited[w]) {
                        visited[w]= true;
                        visit(G.vertices[w].data);
                        queue.push(w);
                    }
                }

            }
        }
    }
    return OK;
    /********** End **********/
}

#include <fstream>
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    using namespace std;
    ofstream outfile;
    outfile.open(FileName, ios::out | ios::trunc);
    if (outfile.fail()) {//如果打开失败，可能文件夹不存在，创建
        system("mkdir data");
        outfile.open(FileName, ios::out | ios::trunc);
        if (outfile.fail()) {
            return OVERFLOW;
        }//文件打开失败
    }
    //按照邻接表存储
    outfile<<G.vexnum<<endl;
    for (int i = 0; i < G.vexnum; ++i) {
        outfile<<G.vertices[i].data.key<<" "<<G.vertices[i].data.others<<endl;
        for (int w=FirstAdjVex(G,G.vertices[i].data.key);w>=0;w=NextAdjVex(G,G.vertices[i].data.key,G.vertices[w].data.key)) {
            outfile<<w<<endl;
        }
        outfile<<"-1"<<endl;
    }
    outfile<<"-1 -1"<<endl;
    outfile.close();
    return OK;
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    using namespace std;
    ifstream infile;
    infile.open(FileName);
    infile>>G.vexnum;
    for (int i = 0; i < G.vexnum; ++i) {
        infile>>G.vertices[i].data.key>>G.vertices[i].data.others;
        int arc;
        infile>>arc;
        if (arc!=-1){
            G.vertices[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
            G.vertices[i].firstarc->adjvex=arc;
            G.vertices[i].firstarc->nextarc= nullptr;
            infile>>arc;
        }
        ArcNode *p=G.vertices[i].firstarc;
        while (arc!=-1){
            ArcNode* newArc=(ArcNode*)malloc(sizeof(ArcNode));
            newArc->adjvex=arc;
            newArc->nextarc= nullptr;
            p->nextarc=newArc;
            p=newArc;
            infile>>arc;
        }
    }
    infile.close();
    return OK;
    /********** End 2 **********/
}
#endif //EXP_SRC_STU_H
