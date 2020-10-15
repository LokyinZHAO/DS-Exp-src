//
// Created by Lokyin Zhao on 2020/9/29.
//

#ifndef INC_1_SEQUENCE_STRUCTURE_CLASSDEF_H
#define INC_1_SEQUENCE_STRUCTURE_CLASSDEF_H
#include <fstream>
using namespace std;
class SeqStc{   //定义一个顺序表的数据抽象
public:
	typedef struct{  //顺序表（顺序结构）的定义
		ElemType * elem;
		int length;
		int listsize;
	}SqList;
private:
	SqList L;
public:
//  func0:获取私有中的L
    SqList Get(){
        return L;
    }
//    函数说明：顺序表扩容
    status ListExpand(){
        realloc(L.elem,sizeof(ElemType)*(L.listsize+INCREMENT));
        if (L.elem== nullptr)
            return OVERFLOWED;//扩容失败
        L.listsize+=INCREMENT;
        return OK;
}
//    func1:初始化线性表
//    函数原型：status InitList()
//    功能说明：如果线性表L不存在，操作结果是构造一个空的线性表，返回OK，否则返回INFEASIBLE。
	status InitList(){
			if (L.elem==nullptr){
				L.elem=(ElemType*)malloc(sizeof(ElemType)*INIT_SIZE);
				if (L.elem==nullptr)
					return OVERFLOWED;//分配空间失败
				L.length=0;
				L.listsize=INIT_SIZE;
				return OK;      //完成初始化
			}else
				return INFEASIBLE;  //线性表已存在，不能初始化
		}//end of InitList

//    fuc2:销毁线性表
//    函数原型：status DestroyList()
//    功能说明：如果线性表L存在，该操作释放线性表的空间，使线性表成为未初始化状态，返回OK；否则对于一个未初始的线性表，是不能进行销毁操作的，返回INFEASIBLE。
	status DestroyList() {
		if (L.elem!=nullptr){//线性表存在，进行销毁
			free(L.elem);
			L.elem=nullptr;
			L.length=0;
			L.listsize=0;
			return OK;
		} else{//线性表不存在，不可行
			return INFEASIBLE;
		}
	}

//    func3：清空线性表
//    函数原型：status ClearList()
//    功能说明：若线性表L不存在，返回INFEASIBLE。否则清空线性表L，返回OK；
	status ClearList() {
		if (L.elem== nullptr)
			return INFEASIBLE;//不能对不存在的线性表清空
		else{
			L.length=0;//线性表长度清零即可
			return OK;
			}
		}

//	  func4：线性表判空
//    函数原型：status ListEmpty()
//    功能说明：若线性表L不存在，则返回INFEASIBLE；若线性表L长度为0，则返回TRUE；不为0则返回FALSE。
		status ListEmpty() const {
            if (L.elem== nullptr)
                return INFEASIBLE;//线性表不存在
            else{
                if (L.length==0)
                    return TRUE;//空线性表长度为0
                else
                    return FALSE;
            }
        }

//    func5：求线性表长度
//    函数原型：status ListLength(int& len)
//    功能说明：若线性表L不存在，返回INFEASIBLE；否则返回OK,并把长度传给引用参数len。
        status intListLength(int& len) const {
            if (L.elem== nullptr)
                return INFEASIBLE;
            else{
                len=L.length;
                return OK;
            }
        }

//      func6:获取元素
//    函数原型：status GetElem(int i,ElemType &e)
//    功能说明：若线性表L不存在，返回INFEASIBLE；若i<1或者i超过线性表L的长度，则返回ERROR；若获取成功，则将值赋给e，并返回OK。
        status GetElem(int i,ElemType& e) const {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else if (i<1||i>L.length)//i不合法
            return ERROR;
        else{
            e=L.elem[i-1];
            return OK;
        }
    }

//     func7：查找元素
//    函数原型：status LocateElem(ElemType e)
//    功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定的元素e，则查找失败，返回ERROR；若查找成功，则返回OK并将元素逻辑序号i付给引用参数。
    status LocateElem(ElemType e,int& i) const {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else{
            for ( i = 0; i < L.length; ++i) {
                if (L.elem[i]==e){
                    i++;
                    return OK;
                }
            }
            return ERROR;
        }
    }

//      func8：获得前驱元素
//    函数原型：status PriorElem(ElemType e,ElemType &pre)
//    功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的前驱，则查找失败，返回ERROR；若查找成功，则将值赋给pre，并返回OK。
    status PriorElem(ElemType cur,ElemType& pre_e) const {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else{
            if (L.elem[0]==cur){//第一个元素匹配，但无前驱
                return UNEXPECTED;
            }
            for (int i = 1; i <L.length ; ++i) {
                //遍历查找，从第二个元素开始，使得即使第一个匹配也返回ERROR
                if (L.elem[i]==cur){
                    pre_e=L.elem[i-1];
                    return OK;
                }
            }
            return ERROR;//未找到
        }
    }

//    func9：获取后继元素
//    函数原型：status NextElem(ElemType e,ElemType &next)
//    功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的后继，则查找失败，返回ERROR；若查找成功，则将值赋给next，并返回OK。
    status NextElem(ElemType cur,ElemType& next_e) const {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else{
            int i;
            for (i = 0; i < L.length - 1; ++i) {
                //不检查最后一个，即使最后一个匹配
                if (L.elem[i]==cur){
                    next_e=L.elem[i+1];
                    return OK;
                }
            }
            if (L.elem[i]==cur)
                return UNEXPECTED;  //最后一个元素
            else
                return ERROR;//未找到元素
        }
    }

//    func10:插入元素
//    函数原型：status ListInsert(int i,ElemType e)
//    功能说明：如果线性表L不存在，返回INFEASIBLE；否则在线性表L的第i个元素前插入新的元素e，插入成功返回OK，失败返回ERROR。
    status ListInsert(int i,ElemType e) {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else if (i<1||i>L.length+1)//插入位置不合法
            return ERROR;
        else{
            if (L.length==L.listsize){//即将溢出，扩容
                if (ListExpand() == OVERFLOWED)
                    return OVERFLOWED;//扩容失败
            }
            for (int j = L.length; j >=i ; --j) {//移动
                L.elem[j]=L.elem[j-1];
            }
            L.elem[i-1]=e;
            L.length++;
            return OK;
        }
    }

//    func11:删除元素
//    函数原型：status ListDelete(int i,ElemType &e)
//    功能说明：若线性表L不存在，返回INFEASIBLE；否则删除线性表L的第i个元素，若删除成功则将删除的值赋给e并返回OK，若删除失败则返回ERROR。
    status ListDelete(int i,ElemType& e) {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else if (i<1||i>L.length)//插入位置不合法
            return ERROR;
        else{
            e=L.elem[i-1];//将删除的值赋给e
            for (int j = i-1; j < L.length; ++j) {//移位
                L.elem[j]=L.elem[j+1];
            }
            L.length--;//删除后长度减一
            return OK;
        }
    }
//    func12：遍历线性表
//    函数原型：status ListTraverse(const string& name)
//    功能说明：若线性表L不存在，返回INFEASIBLE；否则输出线性表的每一个元素，并返回OK。
    status ListTraverse(const string& name) const {
        if (L.elem== nullptr)
            return INFEASIBLE;
        else{
            if (L.length==0) {
                return ERROR;
            }
            else{
                cout<<name<<":";
                for (int j = 0; j < L.length; ++j) {
                    cout<<" "<<L.elem[j];
                }
                cout<<endl;
                return OK;
            }
        }
    }

};

class MultiSq{
public:
		typedef struct{  //线性表集合的管理表定义

			typedef struct {
//              每个线性表元素包含一个线性表对象和线性表名称
				string  name;
				SeqStc L;
			} *SingleL;

			SingleL elem;
			int sqL_quantity;//顺序表数
			int sqL_size;
		}LISTS;
private:
		 LISTS SqLists;
public:
		MultiSq(){//构造函数自动初始化
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
				    SqLists.elem[SqLists.sqL_quantity].L.ListInsert(SqLists.elem[SqLists.sqL_quantity].L.Get().length+1,r);
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
            ofstream sglOutFile;//
            sglOutFile.open(filepath+SqLists.elem[i].name+".txt",ios::out|ios::trunc);//以表名命名文件
            if (sglOutFile.fail())
                return OVERFLOWED;
            if (SqLists.elem[i].L.Get().elem== nullptr)
                return INFEASIBLE;
            sglOutFile<<SqLists.elem[i].L.Get().length<<endl;//首先写入表长
            for (int j = 0; j < SqLists.elem[i].L.Get().length; ++j) {
                sglOutFile<<SqLists.elem[i].L.Get().elem[j]<<endl;//写入元素数据
            }
            sglOutFile.close();
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
            ifstream sglInFile;
            sglInFile.open(filepath+SqLists.elem[i].name+".txt",ios::in);
            if (sglInFile.fail()){  //文件打开失败
                return OVERFLOWED;}
            int len;
            sglInFile>>len;
            SqLists.elem[i].L.InitList();
            for (int j = 0; j <len ; ++j) {//写入数据
                ElemType e;
                sglInFile>>e;
                SqLists.elem[i].L.ListInsert(j+1,e);
            }
            sglInFile.close();
        }
        return OK;
		}
	};





	#endif //INC_1_SEQUENCE_STRUCTURE_CLASSDEF_H
