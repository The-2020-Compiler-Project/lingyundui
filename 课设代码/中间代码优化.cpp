#include"中间代码优化.h"
using namespace std;

int main()
{
	creatDAG();
	display();
	system("pause");
}
void creatDAG()
{
	Tac tac;
	Node node;
	int op1, op2, op1n, op2n;
	int type;
	string temp;
	int newleft, newright;
	while (gettac(&tac))
	{
		newleft = newright = 0;
		/*如果node(B)无定义，则构造一标记为B的叶结点并定义node(B)为这个结点*/
		if (getnode(tac.tr[1]) == 0)
		{
			creatnode(&node,tac.tr[1]);
			insertnode(node);
			newleft = 1;
		}
		type = Tac_type(tac);
		/*如果当前四元式是0型，则记node(B)的值为n;,转1
		  如果当前四元式是1型，则转2.(1);
		  如果当前四元式是2型，则如果node(C)无定义，则构造一标记为C
		  的叶结点并定义node(C)为这个结点,转3.(1);*/
		switch (type)
		{
		case 0:
			/*1.如果node(A)无定义,则把A附加在结点n上并令node(A)=n;否则先把A从node(A)结点上
			的附加标识符集中删除(如果node(A)是叶结点，则其标记A不删除),把A附加到新结点n上
			并令node(A)=n,结束，处理下一四元式*/
			op1 = getnode(tac.tr[1]);
			if ((op1n) = getnode(tac.tr[3]) != 0)
				delid(op1n);
			insertvar(op1, tac.tr[3]);
			break;
		case 1:
			/*2.(1)如果Node(B)是标记为常数的叶结点,转2.(2),否则转2.(3)*/
			if (isconsnode(tac.tr[1]) != 0)
			{
				/*2.(2)执行op B,令新得到的常量为P,如果node(B)是处理当前四元式时新构造出来的结点
				则删除它。如果node(P)无定义，则构造一用P做标记的叶结点n=node(P)*/
				if (newleft == 1)
				{
					delnode(getnode(tac.tr[1]));
				}
				if (getnode(temp) == 0)
				{
					creatnode(&node,temp);
					op1n = insertnode(node);
				}
			}
			else
				/*2.(3)检查DAG中是否已有一结点，其唯一后继为node(B)，且标记为op(即公共表达式)。
				如果没有，则构造该结点n,否则将已有结点设为n*/
			{
				if ((op1n = findnode(tac.tr[1], tac.tr[0])) == 0)
				{
					creatnode(&node,tac.tr[0], getnode(tac.tr[1]), 0);
					op1n = insertnode(node);
				}
				/*同1*/
				if (op2n = getnode(tac.tr[3]) != 0)
					delid(op2n);
				insertvar(op1n, tac.tr[3]);
				break;
		case 2:
			if (getnode(tac.tr[2]) == 0)
			{
				creatnode(&node,tac.tr[2]);
				insertnode(node);
				newright = 1;
			}
			/*3.(1)如果Node（B)和node(C)都是标记为常数的叶结点，则转3.(2),否则转3.(3)*/
			if ((isconsnode(tac.tr[1]) != 0) && (isconsnode(tac.tr[2]) != 0))
			{/*3.(2)执行B op C,令新得到的常数为P，如果node(B)或node(C)是处理当前四元式
			 时新构造出来的结点，则删除它。如果node(P)无定义，则构造一用P做标记的叶结点
			 n,设Node(P)=n*/
				temp = calculate(tac.tr[0], tac.tr[1], tac.tr[2]);
				if (newleft == 1)
					delnode(getnode(tac.tr[1]));
				if (newright == 1)
					delnode(getnode(tac.tr[2]));
				if (getnode(temp) == 0)
				{
					creatnode(&node,temp);
					op1n = insertnode(node);
				}
			}
			else
			{
				/*3.(3)检查DAG中是否已有一结点，其左后继为node(B),右后继为node(C)，且标记
				为op。如果没有，则构造该结点n,否则就把已有的结点作为它的结点并设该结点为n*/
				if ((op1n = findnode(tac.tr[1], tac.tr[2], tac.tr[0])) == 0)
				{
					op1 = getnode(tac.tr[1]);
					op2 = getnode(tac.tr[2]);
					creatnode(&node,tac.tr[0], op1, op2);
					op1n = insertnode(node);
				}
				/*同1*/
				if ((op2n = getnode(tac.tr[3])) != 0)
					delid(op2n);
				insertvar(op1n, tac.tr[3]);
				break;

			}

			}
		}
	}
	
}
bool gettac(Tac *tac)//读取四元式(根据接口修改)
{
	static int con = 0;
	if (qt[con].tr[0] == "\0")//终止(根据接口修改)
		return false;
	for (int i = 0; i < 4; i++)
	{
		tac->tr[i] = qt[con].tr[i];
	}
	con++;
	return true;
}
int Tac_type(Tac tac)//判断四元式类型(待修改)
{
	if (tac.tr[0] == "=")
		return 0;
	if (tac.tr[2] == "\0")
		return 1;
	else
		return 2;
}

int getnode(string var)//获得结点序号
{
	int i, j;
	if (dag.num == 0)return 0;
	for (i = 1; i <= dag.num; i++)
	{
		switch (dag.node[i].type)
		{
		case 0:
			for (j = 0; j < dag.node[i].count; j++)
			{
				if (dag.node[i].var[j] == var)
					return i;
			}
			break;
		case 1:
			if (dag.node[i].num1 == atoi(var.c_str()))
				return i;
			break;
		case 2:
			if (dag.node[i].num2 == atof(var.c_str()))
				return i;
			break;
		default:
			break;
		}
		
	}
	return 0;
}
void creatnode(Node *n, string var)//构造叶子结点
{
	switch (var_type(var))
	{
	case 0:
		n->type = 0;
		n->count = 1;
		n->num1 = 0;
		n->num2 = 0;
		n->var[0] = var;
		break;
	case 1:
		n->type = 1;
		n->count = 0;
		n->num1 = atoi(var.c_str());
		n->num2 = 0;
		break;
	case 2:
		n->type = 2;
		n->count = 0;
		n->num1 = 0;
		n->num2 = atof(var.c_str());
		break;

	}
	n->operition = " ";
	n->lchild = n->rchild = 0;
}
void creatnode(Node *n, string op, int left, int right)//构造中间结点
{
	n->count = 0;
	n->type = 0;
	n->operition = op;
	n->lchild = left;
	n->rchild = right;
}
int insertnode(Node n)//插入结点
{
	dag.num = dag.num + 1;
	copynode(&(dag.node[dag.num]),n);
	return dag.num;
}
void insertvar(int node, string var)//将值附加在结点上
{
	dag.node[node].var[dag.node[node].count] = var;
	dag.node[node].count++;
	
}
void copynode(Node *node1, Node node2)//给结点赋值
{
	node1->count = node2.count;
	for (int i = 0; i < node2.count; i++)
	{
		node1->var[i] = node2.var[i];
	}
	node1->num1 = node2.num1;
	node1->num2 = node2.num2;
	node1->type = node2.type;
	node1->operition = node2.operition;
	node1->lchild = node2.lchild;
	node1->rchild = node2.rchild;
}
int findnode(string op1, string op)//查找表达式
{
	int op_1 = getnode(op1);
	for (int i = 1; i < dag.num; i++)
		if ((dag.node[i].lchild == op_1) && (dag.node[i].operition == op))
			return i;
	return 0;
}
int findnode(string op1,string op2,string op)
{
	int op_1 = getnode(op1);
	int op_2 = getnode(op2);
	for (int i = 1; i < dag.num; i++)
		if ((dag.node[i].lchild == op_1) && (dag.node[i].rchild == op_2) && (dag.node[i].operition == op))
			return i;
	return 0;
}
void delnode(int num)//删除结点
{
	int i, j;
	for(i=1;i<=dag.num;i++)
		if (i == num)
		{
			for (j = i; j <= dag.num; j++)
				copynode(&(dag.node[j]), dag.node[j + 1]);
		}
}
void delid(int num)//删除结点的变量
{
	int i;
	for (i = 0; i < dag.node[num].count; i++)
		dag.node[num].var[i] = "";
	dag.node[num].count = 0;
}
/*string calculate(string op, string op1)//计算表达式
{
	string temp;
	if (op == "!")
	{
		temp = to_string(!atoi(op1.c_str()));
	}
	return temp;
}*/
 string calculate(string op, string op1, string op2)//计算二元表达式
{
	int type = var_type(op1) > var_type(op2) ? var_type(op1) : var_type(op2);
	string temp;
	if (op == "+")
	{
		switch (type)
		{
		case 1:temp=to_string(atoi(op1.c_str()) + atoi(op2.c_str()));
			break;
		case 2:temp = to_string(atof(op1.c_str()) + atof(op2.c_str()));
			break;
		}
	}
	else if (op == "-")
	{
		switch (type)
		{
		case 1:temp = to_string(atoi(op1.c_str()) - atoi(op2.c_str()));
			break;
		case 2:temp = to_string(atof(op1.c_str()) - atof(op2.c_str()));
			break;
		}
	}
	else if (op == "*")
	{
		switch (type)
		{
		case 1:temp = to_string(atoi(op1.c_str()) * atoi(op2.c_str()));
			break;
		case 2:temp = to_string(atof(op1.c_str()) * atof(op2.c_str()));
			break;
		}
	}
	else if (op == "/")
	{
		switch (type)
		{
		case 1:temp = to_string(atoi(op1.c_str()) / atoi(op2.c_str()));
			break;
		case 2:temp = to_string(atof(op1.c_str()) / atof(op2.c_str()));
			break;
		}
	}
	return temp;
}
int var_type(string var)
{
	int i, type;
	for (i = 0; i < var.size(); i++)
	{
		if (!isdigit(var[i]))
		{
			if (var[i] == '.')
			{
				type = 2; break;
			}
			type = 0;
			break;
		}
		else
			type = 1;
	}
	return type;
}
bool isconsnode(string var)
{
	int i, j;
	if (var_type(var)) 
		return true;
	for (i = 1; i <= dag.num; i++)
	{
		if (dag.node[i].type > 0)
		{
			for(j=0;j<dag.node[i].count;j++)
				if (dag.node[i].var[j] == var)
				{
					return true;
				}
		}
	}
	return false;
}
void display()
{
	int i, j;
	int count = 0;
	for (i = 1; i <= dag.num; i++)
	{
		if (dag.node[i].type > 0 && dag.node[i].count == 1)
		{
			switch (dag.node[i].type)
			{
			case 1:
				cout << "(" << ++count << ")" << dag.node[i].var[0] << "=" << dag.node[i].num1 << endl;
				break;
			case 2:
				cout << "(" << ++count << ")" << dag.node[i].var[0] << "=" << dag.node[i].num2 << endl;
				break;
			}
		}
		else if (dag.node[i].count >= 1 && dag.node[i].lchild != 0 && dag.node[i].rchild != 0)
		{
			cout << "(" << ++count << ")" << dag.node[i].var[0] << "=" << getvar(dag.node[i].lchild) << dag.node[i].operition << getvar(dag.node[i].rchild) << endl;
			if(dag.node[i].count>1)
				for (j = 1; j < dag.node[i].count; j++)
				{
					cout << "(" << ++count << ")" << dag.node[i].var[j] << "=" << dag.node[i].var[j - 1] << endl;
				}
		}
	}
}
string getvar(int dagn)
{
	string temp;
	if (dag.node[dagn].type == 0)
		temp = dag.node[dagn].var[0];
	if (dag.node[dagn].type == 1)
		temp = to_string(dag.node[dagn].num1);
	if (dag.node[dagn].type == 2)
		temp = to_string(dag.node[dagn].num2);
	return temp;
}