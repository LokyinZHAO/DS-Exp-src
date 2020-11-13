//
// Created by Lokyin Zhao on 2020/11/5.
//

#ifndef EXP_SRC_CLASSDEF_H
#define EXP_SRC_CLASSDEF_H

#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


class BinTreeStru {
public:
    typedef struct {
        KeyType key = 0;//唯一标识符
        string info;//结点的其他信息
    } TElemType; //二叉树结点类型定义

    typedef struct BiTNode {  //二叉链表结点的定义
        TElemType data;
        BiTNode *lchild{nullptr}, *rchild{nullptr};
    } BiTNode, *BiTree;

    BiTree root;//根结点指针
    string name;//树名称


    BinTreeStru() {//构造函数直接初始化
        root = (BiTree) malloc(sizeof(BiTNode));
        root->lchild = nullptr;
        root->rchild = nullptr;
    }


    //func1：创建一个二叉树
    //功能说明：根据带空子树的二叉树先序遍历序列definition构造二叉链表（要求二叉树T中各结点关键字具有唯一性）。根指针指向根结点，不需要在根结点之上再增加头结点。
private:
    int creatorCount = 0;//definition下标
public:
    status BiTreeCreator(const string &treeName, BiTree &T,
                         const vector<TElemType> &definition) {//调用CreateBiTree，并处理definition下标
        creatorCount = 0;
        return CreateBiTree(treeName, T, definition);
    }

    status CreateBiTree(const string &treeName, BiTree &T, const vector<TElemType> &definition) {
        if (creatorCount == 0) {//首先对二叉树名称赋值
            name = treeName;
        }
        if (definition[creatorCount].key == 0) {
            T = nullptr;
            creatorCount++;
            return OK;
        }
        T = (BiTree) malloc(sizeof(BiTNode));
        T->data = definition[creatorCount++];
        CreateBiTree(name, T->lchild, definition);
        CreateBiTree(name, T->rchild, definition);
        return OK;
    }

    //func2:二叉树清空
    //功能说明：将二叉树T置空，并释放所有结点的空间。
    status ClearBiTree(BiTree &T) {
        //后序递归遍历清空
        if (T->lchild) {
            ClearBiTree(T->lchild);
        }
        if (T->rchild) {
            ClearBiTree(T->rchild);
        }
        free(T);
        T = nullptr;
        return OK;
    }

    //func3:求二叉树深度
    //功能说明：求二叉树T深度并返回深度值。
    int BiTreeDepth(BiTree T) {
        if (T == nullptr) {
            return 0;
        } else {//比较左右子树深度
            int lDepth = BiTreeDepth(T->lchild);
            int rDepth = BiTreeDepth(T->rchild);
            return lDepth > rDepth ? ++lDepth : ++rDepth;//返回+1（自身有深度）
        }
    }

    //func4:查找结点
    //功能说明：e是和T中结点关键字类型相同的给定值；根据e查找符合条件的结点，返回该结点指针，如无关键字为e的结点，返回NULL。
    BiTree LocateNode(BiTree T, KeyType e) {
        //前序递归遍历
        if (T == nullptr) {
            return nullptr;
        }
        if (T->data.key == e) {
            return T;
        } else {
            BiTree check;
            if (check = LocateNode(T->lchild, e)) {
                return check;
            } else if (check = LocateNode(T->rchild, e)) {
                return check;
            }
        }
        return nullptr;//遍历后未找到
    }

    //func4.1:查找双亲结点
    //功能说明：e是和T中结点关键字类型相同的给定值；根据e查找符合条件的结点，返回该结点的双亲，如无关键字为e的结点，返回NULL。
    BiTree LocateParent(BiTree T, KeyType e) {
        using namespace std;
        stack<BiTree> s;//栈容器
        s.push(T);
        while (!s.empty()) {//非递归中序
            BiTree p;
            while (p = s.top()) {
                s.push(p->lchild);
            }
            s.pop();//空指针退栈
            if (!s.empty()) {
                p = s.top();
                s.pop();
                if (p->lchild)
                    if (p->lchild->data.key == e)
                        return p;
                if (p->rchild)
                    if (p->rchild->data.key == e)
                        return p;
                s.push(p->rchild);
            }
        }
        return nullptr;//根结点也会返回null
    }

    //func5:结点赋值
    //功能说明：e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点，将结点值修改成value，返回OK（要求结点关键字保持唯一性）。如果查找失败，返回ERROR。
    status Assign(BiTree &T, KeyType e, TElemType value) {
        BiTree locate = LocateNode(T, e);
        if ((locate == nullptr) || (LocateNode(T, value.key) && locate != LocateNode(T, value.key)))//未找到e或者替换后重复均错误
            return ERROR;
        else {
            locate->data = value;
            return OK;
        }
    }

    //func6:获得兄弟结点
    //功能说明：e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点的兄弟结点，返回其兄弟结点指针。如果查找失败，返回NULL。
    BiTree GetSibling(BiTree T, KeyType e) {
        BiTree locate_parent = LocateParent(T, e);
        if (locate_parent) {
            if (!(locate_parent->lchild && locate_parent->rchild)) {//无兄弟
                return nullptr;
            }
            if (locate_parent->lchild->data.key == e) {
                return locate_parent->rchild;
            } else {
                return locate_parent->lchild;
            }
        } else
            return nullptr;
    }

    //func7:插入结点
    //功能说明：e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回ERROR。
    status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
        if (LocateNode(T, c.key) != nullptr)
            return ERROR;//有关键字重复
        BiTree insertion = LocateNode(T, e);
        if (insertion == nullptr)
            return ERROR;//未找到
        if (LR == 0) {//左侧
            BiTree tree = (BiTree) malloc(sizeof(BiTNode));
            tree->rchild = insertion->lchild;
            tree->lchild = nullptr;
            tree->data = c;
            insertion->lchild = tree;
        } else if (LR == 1) {//右
            BiTree tree = (BiTree) malloc(sizeof(BiTNode));
            tree->lchild = nullptr;
            tree->rchild = insertion->rchild;
            tree->data = c;
            insertion->rchild = tree;
        } else if (LR == -1) {//根
            BiTree tree = (BiTree) malloc(sizeof(BiTNode));
            tree->lchild = nullptr;
            tree->rchild = T;
            tree->data = c;
            T = tree;
        }
        return OK;
        /********** End **********/
    }

    //func8:删除结点
    //功能说明：e是和T中结点关键字类型相同的给定值。删除T中关键字为e的结点；同时，如果关键字为e的结点度为0，删除即可；如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；如关键字为e的结点度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树。
    //成功删除结点后返回OK，否则返回ERROR。
    status DeleteNode(BiTree &T, KeyType e) {
        BiTree root = (BiTree) malloc(sizeof(BiTNode));
        root->lchild = T;//创建一个根的指针，便于查找parent
        BiTree parent = LocateParent(root, e);
        if (!parent) return ERROR;//未找到
        if (parent->lchild) {
            if (parent->lchild->data.key == e) {//左子树是被删除的结点
                if (parent->lchild->lchild == nullptr && parent->lchild->rchild == nullptr) {//degree=0
                    free(parent->lchild);
                    parent->lchild = nullptr;
                    if (parent == root) {//如果是删除跟结点，需要将T重新指向
                        T = parent->lchild;
                    }
                    return OK;
                } else if (parent->lchild->lchild != nullptr && parent->lchild->rchild != nullptr) {//degree=2
                    BiTree p = parent->lchild->lchild;
                    while (p->rchild) {
                        p = p->rchild;
                    }//左子树的最右结点
                    p->rchild = parent->lchild->rchild;//e的右子树作为e的左子树中最右结点的右子树
                    BiTree tobefree = parent->lchild;
                    parent->lchild = parent->lchild->lchild;
                    free(tobefree);
                    if (parent == root) {
                        T = parent->lchild;
                    }
                    return OK;
                } else {//degree=1
                    BiTree tobefree = parent->lchild;
                    if (parent->lchild->lchild) {//被删除的结点有左子树
                        parent->lchild = parent->lchild->lchild;
                    } else {
                        parent->lchild = parent->lchild->rchild;
                    }
                    free(tobefree);
                    if (parent == root) {
                        T = parent->lchild;
                    }
                    return OK;
                }
            }
        }
            else {//左子树是被删除的结点
                if (parent->rchild->lchild == nullptr && parent->rchild->rchild == nullptr) {//degree=0
                    free(parent->rchild);
                    parent->rchild = nullptr;
                    if (parent == root) {
                        T = parent->lchild;
                    }
                    return OK;
                } else if (parent->rchild->lchild != nullptr && parent->rchild->rchild != nullptr) {//degree=2
                    BiTree p = parent->rchild->lchild;
                    while (p->rchild) {
                        p = p->rchild;
                    }//左子树的最右结点
                    p->rchild = parent->rchild->rchild;//e的右子树作为e的左子树中最右结点的右子树
                    BiTree tobefree = parent->rchild;
                    parent->rchild = parent->rchild->lchild;
                    free(tobefree);
                    if (parent == root) {
                        T = parent->lchild;
                    }
                    return OK;
                } else {//degree=1
                    BiTree tobefree = parent->rchild;
                    if (parent->rchild->lchild) {//被删除的结点有左子树
                        parent->rchild = parent->rchild->lchild;
                    } else {
                        parent->rchild = parent->rchild->rchild;
                    }
                    free(tobefree);
                    if (parent == root) {
                        T = parent->lchild;
                    }
                    return OK;
                }

            }
    }

    //func9：先序遍历
    //功能说明：对二叉树T进行先序遍历，Visit是一个函数指针的形参（可使用该函数对结点操作），对每个结点调用函数Visit访问一次且一次。
    status PreOrderTraverse(BiTree T) {
        if (T != nullptr) {
            cout << T->data.key << "," << T->data.info << " ";
            PreOrderTraverse(T->lchild);
            PreOrderTraverse(T->rchild);
            return OK;
        } else return OK;
    }

    //func10:中序遍历
    //功能说明：对二叉树T进行中序遍历，Visit是一个函数指针的形参（可使用该函数对结点操作），对每个结点调用函数Visit访问一次且一次。
    status InOrderTraverse(BiTree T) {
        //中序非递归
        stack<BiTree> s;
        s.push(T);
        while (!s.empty()) {
            BiTree p = s.top();
            while (p) {//向左走到尽头
                s.push(p->lchild);
                p = s.top();
            }
            s.pop();//空指针退栈
            if (!s.empty()) {//访问结点与其右子树
                p = s.top();
                cout << p->data.key << "," << p->data.info << " ";
                s.pop();
                s.push(p->rchild);
            }
        }
        return OK;
    }

    //func11:后序遍历
    //功能说明：对二叉树T进行后序遍历，Visit是一个函数指针的形参（可使用该函数对结点操作），对每个结点调用函数Visit访问一次且一次。
    status PostOrderTraverse(BiTree T) {
        if (T != nullptr) {
            PostOrderTraverse(T->lchild);
            PostOrderTraverse(T->rchild);
            cout << T->data.key << "," << T->data.info << " ";
            return OK;
        } else return OK;
    }

    //func12：按层遍历
    //功能说明：对二叉树T进行按层遍历，Visit是一个函数指针的形参（可使用该函数对结点操作），对每个结点调用函数Visit访问一次且一次。
    status LevelOrderTraverse(BiTree T) {
        queue<BiTree> q;//创建队列容器
        if (T) q.push(T);
        while (!q.empty()) {
            BiTree p = q.front();
            q.pop();//:=Dequeue
            cout << p->data.key << "," << p->data.info << " ";
            if (p->lchild)
                q.push(p->lchild);//Inqueue
            if (p->rchild)
                q.push(p->rchild);
        };
    }

    //func13：存储二叉树
    //功能说明：将二叉树结点的数据以二叉树名称命名的txt文件写到filePath中
    status SaveBiTree(BiTree T, string filePath) const {
        ofstream outfile;
        outfile.open(filePath + name + ".txt");
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
            BiTree p = s.top();
            int posi = position.top();
            while (p) {
                outfile << posi << " " << p->data.key << " " << p->data.info << endl;
                s.push(p->lchild);//访问后向左尽头
                position.push(position.top() * 2);
                p = s.top();
                posi = position.top();
            }
            s.pop();
            position.pop();//空结点退栈
            if (!s.empty()) {//访问右子树
                posi = position.top();
                p = s.top();
                position.pop();
                s.pop();//双亲结点退栈
                s.push(p->rchild);
                position.push(posi * 2 + 1);//右子树入栈
            }
        }
        outfile << 0 << " " << 0 << " EOF" << endl;//结束标记
        outfile.close();
        return OK;
    }

    //func14:读取二叉树
    //功能说明：将filePath中的txt文件读取，创建二叉树
    status LoadBiTree(string FileName) {
        if (root->rchild && root->lchild) return INFEASIBLE;//二叉树已存在不能读写
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
        BiTree p = (BiTree) malloc(sizeof(BiTNode));
        infile >> posi;
        infile >> p->data.key;
        infile >> p->data.info;
        p->lchild = nullptr;
        p->rchild = nullptr;
        root = p;
        s.push(p);
        position.push(posi);
        p = (BiTree) malloc(sizeof(BiTNode));
        infile >> posi;
        infile >> p->data.key;
        infile >> p->data.info;
        p->lchild = nullptr;
        p->rchild = nullptr;
        while (!s.empty()) {
            if (posi == position.top() * 2) {//栈顶左子树
                s.top()->lchild = p;
                s.push(p);
                position.push(posi);//入栈
                p = (BiTree) malloc(sizeof(BiTNode));
                infile >> posi;
                infile >> p->data.key;
                infile >> p->data.info;
                p->lchild = nullptr;
                p->rchild = nullptr;
            } else if (posi == (position.top() * 2 + 1)) {//栈顶右子树
                s.top()->rchild = p;
                s.push(p);
                position.push(posi);//入栈
                p = (BiTree) malloc(sizeof(BiTNode));
                infile >> posi;
                infile >> p->data.key;
                infile >> p->data.info;
                p->lchild = nullptr;
                p->rchild = nullptr;
            } else {//既不是左子树又不是右子树，开始回溯
                position.pop();
                s.pop();//退栈
            }
        }
    }
};//class BinTreeStru


class Forest {//多个二叉树的集合,通过容器vector管理多个二叉树
public:
    vector<BinTreeStru> forest;

    //func1：初始化森林
    //功能说明：如果森林不存在，操作结果是构造一个空的二叉树顺序表集合，返回OK，否则返回INFEASIBLE
    // （注意声明对象时已通过构造函数初始化）
    status InitForest() {
        if (!forest.empty()) {//已经存在树不可初始化
            return INFEASIBLE;
        }
        return OK;//vector自动初始化
    }

    //func2:增加一个二叉树
    //功能说明：Lists是一个以顺序表形式管理的二叉树的集合，在集合中增加一个新的二叉树。
    status AddTree(const string &treeName) {
        BinTreeStru newTree;
        vector<BinTreeStru::TElemType> definition;
        cout << "请输入二叉树带空子树的先序遍历结点序列,每个结点对应一个整型的关键字和一个字符串，当关键字为0时，表示空子树，为-1表示输入结束：" << endl;
        BinTreeStru::TElemType input;
        cin >> input.key >> input.info;
        while (input.key != -1) {//从输入流中读入定义到defination中
            definition.push_back(input);
            cin >> input.key >> input.info;
        }
        definition.push_back(input);//将-1输入definition中
        for (int i = 0; definition[i].key != -1; ++i) {
            if (definition[i].key != 0) {
                for (int j = i + 1; definition[j].key != -1; ++j) {
                    if (definition[i].key == definition[j].key)
                        return ERROR;//有重复的标识符
                }
            }
        }
        newTree.BiTreeCreator(treeName, newTree.root, definition);
        forest.push_back(newTree);//将新建立的二叉树加到顺序遍末尾
        return OK;
    };

    //func3:移除一个二叉树
    //功能说明：在二叉树集合中查找名为treeName的二叉树，有则删除，返回OK，否则返回ERROR
    status RemoveTree(const string &treeName) {
        for (auto iter = forest.begin(); iter != forest.end(); iter++) {//利用容器的迭代器
            if (iter->name == treeName) {//找到
                forest.erase(iter);//删除
                return OK;
            }
        }
        return ERROR;//未找到
    }

    //func4:查找二叉树
    //功能说明：在二叉树集合中查找名称为ListName的二叉树，有则返回二叉树的逻辑序号，无则返回0。
    int LocateTree(const string &treeName) {
        for (int i = 0; i < forest.size(); ++i) {
            if (treeName == forest[i].name) {
                return i + 1;//找到
            }
        }
        return 0;//未找到
    }

    //func5:存储森林
    //功能说明:将forest所有元素存储在filePath下
    status SaveForest(const string &filepath) const {
        ofstream outfile;
        outfile.open(filepath + "TreeName.txt", ios::out | ios::trunc);
        if (outfile.fail()) {//如果打开失败，可能文件夹不存在，创建
            system("mkdir data");
            outfile.open(filepath + "TreeName.txt", ios::out | ios::trunc);
            if (outfile.fail())
                return OVERFLOWED;//文件打开失败
        }
        outfile << forest.size() << endl;//首先写入元素个数
        for (int i = 0; i < forest.size(); ++i) {
            outfile << forest[i].name << endl;
            forest[i].SaveBiTree(forest[i].root, filepath);
        }
        outfile.close();
        return OK;
    }

    //func6:读取森林
    //功能说明：从filePath中读取森林数据
    status LoadForest(const string &filepath) {
        if (forest.size())
            return INFEASIBLE;//森林中有数据，不可行
        ifstream infile;
        infile.open(filepath + "TreeName.txt", ios::in);
        if (infile.fail()) {
            return OVERFLOWED;
        }
        int quantity;
        infile >> quantity;
        for (int i = 0; i < quantity; ++i) {
            BinTreeStru newTree;
            infile >> newTree.name;
            newTree.LoadBiTree(filepath + newTree.name + ".txt");
            forest.push_back(newTree);
        }
        infile.close();
        return OK;
    }
};

#endif //EXP_SRC_CLASSDEF_H
