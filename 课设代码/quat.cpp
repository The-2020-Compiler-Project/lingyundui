#include"��ͷ.h"
#define _CRT_SECURE_NO_WARNINGS

struct tokenline
{//token�У����ڵ���
    struct token sstr[maxlen];
    int len;
} tokenline;


extern token  Token[150];

struct quaternary qt[100];//��Ԫʽ����
sstack sstin, sstout, ssf;

sstack::sstack() :sp(0) {}

string sstack::push(string& st)
{//��ջ
    return type[++sp] = st;
}

string sstack::pop()
{//��ջ
    return type[sp--];
}

void sstack::sclear()
{//���
    sp = 0;
    return;
}

int sstack::get_sp()
{//ȡջ��
    return sp;
}




int tcn = 0;
//��¼�����ɱ���
string new_t()
{//�����м����
    char ch[maxlen];
    _itoa_s(tcn, ch, 10);
    string s(ch, ch + strlen(ch));
    tcn++;
    return "t" + s;
}

int tcl = 0;
//��¼������
int new_l()
{
    return tcl++;
}

//quaternary
void set_quaternary()
{//������Ԫʽ
    string s;
    int i;
    for (i = 0; i < maxlen; i++)
    {//��һ�β���
        s = sstin.pop();
        sstout.push(s);
        if (s == "*" || s == "/")
        {
            int n = new_l();
            qt[n].tr[0] = sstout.pop();
            qt[n].tr[1] = sstin.pop();
            qt[n].tr[2] = sstout.pop();
            qt[n].tr[3] = new_t();
            sstin.push(qt[n].tr[3]);
            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << "," << qt[n].tr[2] << "," << qt[n].tr[3] << ")" << endl;
            /*
            for(int i=0;i<numt;i++)
            {
                if(synbl[i].name==qt[n].tr[1])
                {
                    num=num+1;
                    synbl[num].name=qt.[n].tr[3];
                    synbl.[num].tval=synbl[i].tapel.tval;
                }
            }
            */
        }
        else if (s == "{" || s == ";" || s == "(")
        {//����
            s = sstout.pop();
            sstin.push(s);
            break;
        }
    }
    for (i = 0; i < maxlen; i++)
    {
        s = sstout.pop();
        sstin.push(s);
        if (s == "{" || s == ";" || s == "(")
        {//����
            s = sstin.pop();
            sstout.push(s);
            break;
        }
    }
    for (i = 0; i < maxlen; i++)
    {
        s = sstin.pop();
        sstout.push(s);
        if (s == "+" || s == "-" || s == "=" || s == "!=" || s == ">" || s == "<" || s == "<=" || s == ">=" || s == "==")
        {
            int n = new_l();
            qt[n].tr[0] = sstout.pop();
            qt[n].tr[1] = sstin.pop();
            qt[n].tr[2] = sstout.pop();
            qt[n].tr[3] = new_t();
            sstin.push(qt[n].tr[3]);
            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << "," << qt[n].tr[2] << "," << qt[n].tr[3] << ")" << endl;
            /*
            for(int i=0;i<numt;i++)
            {
                if(synbl[i].name==qt[n].tr[1])
                {
                    num=num+1;
                    synbl[num].name=qt.[n].tr[3];
                    synbl.[num].tval=synbl[i].tapel.tval;
                }
            }
            */
        }
        else if (s == "{" || s == ";")
        {//����
            s = sstout.pop();
            sstin.push(s);
            break;
        }
        else if (s == "(")
        {
            sstout.pop();
            s = sstout.pop();
            sstin.push(s);
            break;
        }
    }
    return;
}

void set_all(struct tokenline tkl, int numt)
{//��������
    string sc;
    sc = "{";
    sstin.push(sc);
    int i = 0;
    for (i; i < numt; i++)
    {
        int j = i + 1;
        int k = i;
        sstin.push(tkl.sstr[i].type);
        //������ջ
        if (tkl.sstr[i].type == "while")
        {//��while
            string s;
            s = sstin.pop();
            ssf.push(s);
            qt[new_l()].tr[0] = "while";
            cout << "(" << tkl.sstr[i].type << ", , , )" << endl;
            //ƥ��while
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == ")")
                {//ƥ�䣨������
                    sstin.pop();
                    k = j;
                    s = ";";
                    sstout.push(s);
                    set_quaternary();
                    break;
                }
            }
            sstin.pop();
            qt[new_l()].tr[0] = "do";
            cout << "(do" << ", , , )" << endl;
            //������ֹ
        }
        else if (tkl.sstr[i].type == "if")
        {//��if
            string s;
            s = sstin.pop();
            sstout.push(s);
            ssf.push(s);
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == ")")
                {//ƥ�䣨������
                    sstin.pop();
                    k = j;
                    s = ";";
                    sstout.push(s);
                    set_quaternary();
                    break;
                }
            }

            s = sstin.pop();
            int n = new_l();
            qt[n].tr[0] = "if";
            qt[n].tr[1] = s;
            cout << "(if" << "," << s << ", , )" << endl;
            //ƥ��if
        }
        else if (tkl.sstr[i].type == ";" || tkl.sstr[i].type == ")")
        {//�ָǰ���֣�֮ǰ������Ԫʽ
            string s;
            sstin.pop();
            s = ";";
            sstout.push(s);
            set_quaternary();
        }
        else if (tkl.sstr[i].type == "int" || tkl.sstr[i].type == "float")
        {//�����͸�ֵ���
        //int��float���ֵһ���Ǹ�ֵ���ݣ�֮����ݡ�������ֵ
            string s;
            s = sstin.pop();
            int n = new_l();
            qt[n].tr[0] = s;
            string sr;
            sr = tkl.sstr[i + 1].type;
            qt[n].tr[1] = sr;
            ssf.push(sr);
            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == ",")
                {//�жϸ�ֵ
                    n = new_l();
                    qt[n].tr[0] = s;
                    qt[n].tr[1] = tkl.sstr[j + 1].type;
                    cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                    sstin.pop();
                    k = j;
                    set_quaternary();
                }
                else if (tkl.sstr[j].type == ";")
                {//����
                    sstin.pop();
                    k = j;
                    set_quaternary();
                    ssf.pop();
                    break;
                }
                else if (tkl.sstr[j].type == "(")
                {//������ֵ
                    n = new_l();
                    qt[n].tr[0] = "func_c";
                    cout << "(" << qt[n].tr[0] << ", , , )" << endl;
                    int jn = j + 1;
                    for (jn; jn < numt; jn++)
                    {
                        sstin.push(tkl.sstr[jn].type);
                        if (tkl.sstr[jn].type == "int" || tkl.sstr[jn].type == "float")
                        {//������ʼ����
                            string sr;
                            sr = sstin.pop();
                            n = new_l();
                            qt[n].tr[0] = sr;
                            qt[n].tr[1] = tkl.sstr[j + 1].type;
                            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                        }
                        else if (tkl.sstr[jn].type == "char")
                        {
                            string sr;
                            sr = sstin.pop();
                            n = new_l();
                            qt[n].tr[0] = sr;
                            qt[n].tr[1] = tkl.sstr[j + 2].type;
                            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                        }
                        else if (tkl.sstr[jn].type == ",")
                        {
                            sstin.pop();
                            set_quaternary();
                        }
                        else if (tkl.sstr[jn].type == ")")
                        {//�жϸ�ֵ����
                            sstin.pop();
                            string sr;
                            sr = ";";
                            sstout.push(sr);
                            if (jn != j + 1)
                            {
                                set_quaternary();
                            }
                            k = jn;
                            n = new_l();
                            qt[n].tr[0] = "end_c";
                            cout << "(" << qt[n].tr[0] << ", , , )" << endl;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if (tkl.sstr[i].type == "char")
        {//�ַ��͸�ֵ���
            string s;
            s = sstin.pop();
            int n = new_l();
            qt[n].tr[0] = s;
            string sr;
            sr = tkl.sstr[i + 1].type;
            qt[n].tr[1] = sr;
            ssf.push(sr);
            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == "'")
                {
                    sstin.pop();
                }
                else if (tkl.sstr[j].type == ",")
                {
                    n = new_l();
                    qt[n].tr[0] = s;
                    qt[n].tr[1] = tkl.sstr[j + 1].type;
                    cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                    sstin.pop();
                    k = j;
                    set_quaternary();
                }
                else if (tkl.sstr[j].type == ";")
                {
                    sstin.pop();
                    k = j;
                    set_quaternary();
                    break;
                }
                else if (tkl.sstr[j].type == "(")
                {
                    n = new_l();
                    qt[n].tr[0] = "func_c";
                    cout << "(" << qt[n].tr[0] << ", , , )" << endl;
                    int jn = j + 1;
                    for (jn; jn < numt; jn++)
                    {
                        sstin.push(tkl.sstr[jn].type);
                        if (tkl.sstr[jn].type == "int" || tkl.sstr[jn].type == "float")
                        {
                            string sr;
                            sr = sstin.pop();
                            n = new_l();
                            qt[n].tr[0] = sr;
                            qt[n].tr[1] = tkl.sstr[j + 1].type;
                            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                        }
                        else if (tkl.sstr[jn].type == "char")
                        {
                            string sr;
                            sr = sstin.pop();
                            n = new_l();
                            qt[n].tr[0] = sr;
                            qt[n].tr[1] = tkl.sstr[j + 2].type;
                            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                        }
                        else if (tkl.sstr[jn].type == ",")
                        {
                            sstin.pop();
                            set_quaternary();
                        }
                        else if (tkl.sstr[jn].type == ")")
                        {
                            sstin.pop();
                            string sr;
                            sr = ";";
                            sstout.push(sr);
                            if (jn != j + 1)
                            {
                                set_quaternary();
                            }
                            k = jn;
                            n = new_l();
                            qt[n].tr[0] = "end_c";
                            cout << "(" << qt[n].tr[0] << ", , , )" << endl;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if (tkl.sstr[i].type == "}")
        {//�жϸ��������
            string s;
            s = ssf.pop();
            int n = new_l();
            qt[n].tr[0] = "end";
            qt[n].tr[1] = s;
            cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
        }
        i = k;
    }
    return;
}

/*
int check_t(int numt)
{
for(int n=0;n<tcl;n++)
    if(qt[n].tr[0]=="="||qt[n].tr[0]=="<"||qt[n].tr[0]==">"||qt[n].tr[0]==">="||qt[n].tr[0]=="<="||qt[n].tr[0]=="!="||s=="+"||s=="-"||s=="*"||s=="/")
    {
        for(int i=0;i<num;i++)
        {
            if(synbl[i].name==qt[n].tr[1])
            {
                for(int j=0;j<num;j++)
                {
                    if(synbl[j].name==qt[n].tr[2])
                    {
                        if(synbl[i].tapel.tval!=synbl[j].tapel.tval)
                        {
                            cout<<"error"<<endl;
                        }
                    }
                }
            }
        }
    }
return 0;
}
*/



