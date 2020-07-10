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
//中间代码优化

void set_all(struct tokenline tkl, int numt);
void creatDAG();//构建DAG图
void display();

//词法分析相关函数
bool isLetter(char ch);
bool isDigit(char ch);
int Search(char a[][20], char word[]);
void init();
void readtoken();
void cifafenxiqizongti();
//语法分析相关函数
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


//四元式生成相关

struct token
{
	
	int   typeTSize;
	string name;
	string type;
};




class sstack
{//栈
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
{//四元式
	string tr[4];
	//int ip;
};
















