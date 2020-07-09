#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<string>
#include<iostream>
#include<vector>
#include<map>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define maxlen 100
typedef struct quaternary
{
	string tr[4];/*tr[0] 操作
				   tr[1] 操作数1
				   tr[2] 操作数2
				   tr[3] 结果*/
}Tac;
Tac qt[maxlen];
typedef struct Node 
{
	int count;//结点代表的变量数
	string operition;//操作
	int type;//type=0是变量，type=1是整数，type2是浮点数
	int num1;//整型常量
	double num2;//浮点常量
	string var[maxlen];//变量
	int lchild;//左孩子结点
	int rchild;//右孩子结点
}Node;
typedef struct DAG
{
	int num;
	Node node[maxlen];
}DAG;
DAG dag;

bool gettac(Tac *tac);//读取四元式(接口)
int Tac_type(Tac tac);//判断四元式类型
int getnode(string var);//获得结点序号
void creatnode(Node *n,string var);//构造叶子结点
void creatnode(Node *n,string op,int left,int right);//构造中间结点
int insertnode(Node n);//插入结点
void insertvar(int node, string var);//将值附加在结点上
void copynode(Node *node1, Node node2);//给结点赋值
void delnode(int num);//删除结点
void delid(int num);//删除结点的变量
int findnode(string op1, string op);//查找表达式
int findnode(string op1, string op2, string op);
//char *calculate(string op, string op1);//计算表达式
string calculate(string op, string op1, string op2);//计算二元表达式
int var_type(string var);//检查量类型
bool isconsnode(string var);//检查是否是常数结点
void creatDAG();//构建DAG图
void display();
string getvar(int dagn);
