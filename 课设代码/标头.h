#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<string>
#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<stack>
#include<bitset>
#include<cmath>
#include<set>
#include<list>
#include<deque>
#include<queue>
#include<sstream>
#include <fstream>
#define maxlen   100




using namespace std;
//�м�����Ż�

void set_all(struct tokenline tkl, int numt);
void creatDAG();//����DAGͼ
void display();

//�ʷ�������غ���
bool isLetter(char ch);
bool isDigit(char ch);
int Search(char a[][20], char word[]);
void init();
void readtoken();
void cifafenxiqizongti();
//�﷨������غ���
void PROGRAM();
void  Main();
void  Variable();
void Com_sen();
void Condition();
void Assign_sen();
void E();
void T();
void F();
bool  Parse();
void  rain();


//��Ԫʽ�������

struct token
{
	
	int   typeTSize;
	string name;
	string type;
};




class sstack
{//ջ
private:
	string type[maxlen];
	int sp;
public:
	sstack();
	string pop();
	string push(string& st);
	void sclear();
	int get_sp();
};
struct quaternary
{//��Ԫʽ
	string tr[4];
	//int ip;
};
















