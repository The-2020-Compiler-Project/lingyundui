#include"标头.h"

extern token  Token[150];
extern int num ;//总Token串标号
int   p = 0;
void Program();
void  Main();
void  Variable();
void Com_sen();
void Condition();
void Assign_sen();
void E();
void T();
void F();




void Program()
{
	int typeTSize = Token[p].typeTSize;
	if (typeTSize == 3 || typeTSize == 4 || typeTSize == 5)
	{
		p++;
		if (Token[p].typeTSize == 1)
		{
			p++;
			if (Token[p].typeTSize == 16)
			{
				p++;
				if (Token[p].typeTSize == 17)
				{
					p++;
					if (Token[p].typeTSize == 18)
					{
						p++;
						Main();
						if (Token[p].typeTSize != 19)
						{
							cout << "}有错误" << endl;//
							getchar();
							exit(0);
						}
						
					}
					else
					{
						cout << "{有错误" << endl;
						getchar();
						exit(0);
					}
				}
				else
				{
					cout << ")错误" << endl;
					getchar();
					exit(0);
				}
			}
			else
			{
				cout << "(错误" << endl;
				getchar();
				exit(0);
			}




		}
		else
		{
			cout << "函数名错误！" << endl;
			getchar();
			exit(0);


		}
	}
	else {
		cout << "函数返回值类型错误！" << endl;
		getchar();
		exit(0);
	}
}



void Main()
{


	Variable();
	Com_sen();


}

void Variable()//变量定义
{
	if (Token[p].typeTSize == 3 || Token[p].typeTSize == 4 || Token[p].typeTSize == 5)
	{
		p++;
		if (Token[p].typeTSize == 1)
		{
			p++;
			while (Token[p].typeTSize == 20)
			{
				p++;
				if (Token[p].typeTSize == 1)
				{
					p++;

				}

			}

			if (Token[p].typeTSize == 21)
			{
				p++;

			}
			else
			{
				cout << "语句尾未加;" << endl;
				getchar();
				exit(0);
			}


		}
		else
		{
			cout << "标识符错误" << endl;
			getchar();
			exit(0);
		}
	}
	else
	{
		cout << "变量未定义类型" << endl;
		getchar();
		exit(0);
	}


}
void Com_sen()//复合语句
{
	if (Token[p].typeTSize == 23)
	{
		p++;
		if (Token[p].typeTSize == 16)
		{
			p++;
			Condition();
			if (Token[p].typeTSize == 17)
			{
				p++;
				if (Token[p].typeTSize == 18)
				{
					p++;
					Assign_sen();
					if (Token[p].typeTSize != 19)
					{
						cout << "条件体未加上}" << endl;
						getchar();
						exit(0);

					}
					else
					{
						p++;
					}
				}
			}

		}
	}
	else
	{


		if (Token[p].typeTSize == 24)
		{
			p++;
			if (Token[p].typeTSize == 16)
			{
				p++;
				Condition();
				if (Token[p].typeTSize == 17)
				{
					p++;
					if (Token[p].typeTSize == 18)
					{
						p++;
						Assign_sen();
						if (Token[p].typeTSize != 19)
						{
							cout << "while循环体未加}" << endl;
							getchar();
							exit(0);
						}
						else
						{
							p++;
						}
					}



				}
			}
		}
		else
		{
			Assign_sen();
		}




	}


}
void  Condition()
{
	if (Token[p].typeTSize == 1 || Token[p].typeTSize == 2)
	{
		p++;
		int c = Token[p].typeTSize;
		if (c == 6 || c == 7 || c == 8 || c == 9 || c == 10 || c == 11)
		{
			p++;
			if (Token[p].typeTSize == 1 || Token[p].typeTSize == 2)
			{
				p++;
			}
			else
			{
				cout << "右部的逻辑运算对象错误" << endl;
				getchar();
				exit(0);
			}
		}
		else
		{
			cout << "逻辑运算符错误" << endl;
			getchar();
			exit(0);
		}
	}
	else
	{
		cout << "条件错误" << endl;
		getchar();
		exit(0);

	}





}
void Assign_sen()
{
	if (Token[p].typeTSize == 1)
	{
		p++;
		if (Token[p].typeTSize == 22)
		{
			p++;
			E();
			if (Token[p].typeTSize != 21)
			{
				cout << "赋值语句未加;" << endl;
				getchar();
				exit(0);

			}
			else
			{
				p++;
			}

			

		}
	}


}
void E()//
{
	T();
	while (Token[p].typeTSize == 12 || Token[p].typeTSize == 13)
	{

		p++;
		T();
	}




}
void T()
{
	F();
	while (Token[p].typeTSize == 14 || Token[p].typeTSize == 15)
	{
		p++;
		F();

	}

}
void F()
{
	if (Token[p].typeTSize == 1 || Token[p].typeTSize == 2)
	{
		p++;
	}
	else
	{
		if (Token[p].typeTSize == 16)
		{
			p++;
			E();
			if (Token[p].typeTSize == 17)
			{
				p++;
			}
			else
			{
				cout << "赋值表达式的右括号错误" << endl;
				getchar();
				exit(0);

			}


		}
		else
		{
			cout << "赋值表达式错误" << endl;
			getchar();
			exit(0);
		}
	}


}


bool    Parse()
{
	p++;

	//read(w)
	Program();
	if (Token[p].typeTSize==19)//
	{
		
		cout << "SyntaxAnalyse is Successful!" << endl;
		cout << "***************************************************************************************************" << endl;
		cout << "生成四元式:" << endl;
		return 1;
	}
	else
	{
		cout << "fail!" << endl;
		return 0;
	}
}