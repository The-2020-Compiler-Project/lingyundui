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
	string tr[4];/*tr[0] ����
				   tr[1] ������1
				   tr[2] ������2
				   tr[3] ���*/
}Tac;
Tac qt[maxlen];
typedef struct Node 
{
	int count;//������ı�����
	string operition;//����
	int type;//type=0�Ǳ�����type=1��������type2�Ǹ�����
	int num1;//���ͳ���
	double num2;//���㳣��
	string var[maxlen];//����
	int lchild;//���ӽ��
	int rchild;//�Һ��ӽ��
}Node;
typedef struct DAG
{
	int num;
	Node node[maxlen];
}DAG;
DAG dag;

bool gettac(Tac *tac);//��ȡ��Ԫʽ(�ӿ�)
int Tac_type(Tac tac);//�ж���Ԫʽ����
int getnode(string var);//��ý�����
void creatnode(Node *n,string var);//����Ҷ�ӽ��
void creatnode(Node *n,string op,int left,int right);//�����м���
int insertnode(Node n);//������
void insertvar(int node, string var);//��ֵ�����ڽ����
void copynode(Node *node1, Node node2);//����㸳ֵ
void delnode(int num);//ɾ�����
void delid(int num);//ɾ�����ı���
int findnode(string op1, string op);//���ұ��ʽ
int findnode(string op1, string op2, string op);
//char *calculate(string op, string op1);//������ʽ
string calculate(string op, string op1, string op2);//�����Ԫ���ʽ
int var_type(string var);//���������
bool isconsnode(string var);//����Ƿ��ǳ������
void creatDAG();//����DAGͼ
void display();
string getvar(int dagn);
