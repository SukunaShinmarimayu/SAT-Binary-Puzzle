#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1        //真为1
#define FALSE 0       //假为0
#define OK 1          //Ok为1
#define ERROR 0       //ERROR为0 
#define INFEASTABLE -1     
#define OVERFLOW -2       //溢出为-2
#define CLK_TCK 18.2

//定义链表(单文字)的结点
typedef struct lNode{
	int l;//具体的变元内容          
	int mark;//标记      
	struct lNode *next;//链表的下一个结点         
}lNode,*plNode;
//定义链表(单句子)的结点
typedef struct cNode{
	int l_count; 	//文字(变元)的个数
	int flag;           //记录该子句因为flag而被删除，初始值为0 
	int mark;            //标记该子句是否被删除 ，初始值为1 
	lNode *firstl;          //第一个文字的结点
	struct cNode *next;        //下一个句子结点
}cNode,*pcNode;     
//定义链表(索引)的结点
typedef struct iNode{
	cNode *p_cnode; //第一个句子的结点      
	struct iNode *next;//下一个段落的结点
}iNode,*piNode;        
//定义链表(索引表)的结点
typedef struct index_Node{
	iNode *firstz; //储存正确的      
	iNode *firstf; //储存错误的   
} inde,*pindex;

typedef struct cnf{
	int varinum;        //变元数目
	int claunum;        //句子的数目
	cNode *firstc;      //第一个句子
	pindex Index_List;   //解的集合
}cnf,*pcnf;          
//线性表
typedef struct SqList{
	int *elem;
	int length;
}SqList;              
//函数的定义
int createCNF(pcnf *L,char filename[80]);        //创建cnf内容
int showCNF(pcnf L);     //展示cnf的元素
int InitList(pcnf L,SqList &An);
int RemoveClause(pcnf L,int flag);
int AddClause(pcnf L,int flag);
int EmptyClause(pcnf L);
int Findl(pcnf L,SqList &An);
int DPLL(pcnf L,SqList &An,int now_l);
int test(pcnf L,SqList &An);
int rule_1(char filename[80],int n);
int rule_2(char filename[80],int n);
int rule_3(char filename[80],int n);
int write(char filename[80],int n);
int WriteCNF(char filename[80],int n);
int ResWrite_1(int res,double time,SqList &An,char filename[80]);
int ResWrite_2(int res,double time,SqList &An,char filename[80]); 
