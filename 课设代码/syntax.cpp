#include"��ͷ.h"

extern token  Token[150];
extern int num ;//��Token�����
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
							cout << "}�д���" << endl;//
							getchar();
							exit(0);
						}
						
					}
					else
					{
						cout << "{�д���" << endl;
						getchar();
						exit(0);
					}
				}
				else
				{
					cout << ")����" << endl;
					getchar();
					exit(0);
				}
			}
			else
			{
				cout << "(����" << endl;
				getchar();
				exit(0);
			}




		}
		else
		{
			cout << "����������" << endl;
			getchar();
			exit(0);


		}
	}
	else {
		cout << "��������ֵ���ʹ���" << endl;
		getchar();
		exit(0);
	}
}



void Main()
{


	Variable();
	Com_sen();


}

void Variable()//��������
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
				cout << "���βδ��;" << endl;
				getchar();
				exit(0);
			}


		}
		else
		{
			cout << "��ʶ������" << endl;
			getchar();
			exit(0);
		}
	}
	else
	{
		cout << "����δ��������" << endl;
		getchar();
		exit(0);
	}


}
void Com_sen()//�������
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
						cout << "������δ����}" << endl;
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
							cout << "whileѭ����δ��}" << endl;
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
				cout << "�Ҳ����߼�����������" << endl;
				getchar();
				exit(0);
			}
		}
		else
		{
			cout << "�߼����������" << endl;
			getchar();
			exit(0);
		}
	}
	else
	{
		cout << "��������" << endl;
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
				cout << "��ֵ���δ��;" << endl;
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
				cout << "��ֵ���ʽ�������Ŵ���" << endl;
				getchar();
				exit(0);

			}


		}
		else
		{
			cout << "��ֵ���ʽ����" << endl;
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
		cout << "������Ԫʽ:" << endl;
		return 1;
	}
	else
	{
		cout << "fail!" << endl;
		return 0;
	}
}