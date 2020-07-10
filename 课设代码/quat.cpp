#include"标头.h"
#define _CRT_SECURE_NO_WARNINGS

struct tokenline
{//token列，便于调用
    struct token sstr[maxlen];
    int len;
} tokenline;


extern token  Token[150];

struct quaternary qt[100];//四元式数组
sstack sstin, sstout, ssf;

sstack::sstack() :sp(0) {}

string sstack::push(string& st)
{//入栈
    return type[++sp] = st;
}

string sstack::pop()
{//出栈
    return type[sp--];
}

void sstack::sclear()
{//清空
    sp = 0;
    return;
}

int sstack::get_sp()
{//取栈顶
    return sp;
}




int tcn = 0;
//记录新生成变量
string new_t()
{//生成中间变量
    char ch[maxlen];
    _itoa_s(tcn, ch, 10);
    string s(ch, ch + strlen(ch));
    tcn++;
    return "t" + s;
}

int tcl = 0;
//记录新序列
int new_l()
{
    return tcl++;
}

//quaternary
void set_quaternary()
{//设置四元式
    string s;
    int i;
    for (i = 0; i < maxlen; i++)
    {//第一次查找
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
        {//结束
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
        {//结束
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
        {//结束
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
{//设置整体
    string sc;
    sc = "{";
    sstin.push(sc);
    int i = 0;
    for (i; i < numt; i++)
    {
        int j = i + 1;
        int k = i;
        sstin.push(tkl.sstr[i].type);
        //依次入栈
        if (tkl.sstr[i].type == "while")
        {//读while
            string s;
            s = sstin.pop();
            ssf.push(s);
            qt[new_l()].tr[0] = "while";
            cout << "(" << tkl.sstr[i].type << ", , , )" << endl;
            //匹配while
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == ")")
                {//匹配（）条件
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
            //条件终止
        }
        else if (tkl.sstr[i].type == "if")
        {//读if
            string s;
            s = sstin.pop();
            sstout.push(s);
            ssf.push(s);
            for (j; j < numt; j++)
            {
                sstin.push(tkl.sstr[j].type);
                if (tkl.sstr[j].type == ")")
                {//匹配（）条件
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
            //匹配if
        }
        else if (tkl.sstr[i].type == ";" || tkl.sstr[i].type == ")")
        {//分割当前部分，之前语句的四元式
            string s;
            sstin.pop();
            s = ";";
            sstout.push(s);
            set_quaternary();
        }
        else if (tkl.sstr[i].type == "int" || tkl.sstr[i].type == "float")
        {//数字型赋值语句
        //int或float后的值一定是赋值内容，之后根据“，”赋值
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
                {//判断赋值
                    n = new_l();
                    qt[n].tr[0] = s;
                    qt[n].tr[1] = tkl.sstr[j + 1].type;
                    cout << "(" << qt[n].tr[0] << "," << qt[n].tr[1] << ", , )" << endl;
                    sstin.pop();
                    k = j;
                    set_quaternary();
                }
                else if (tkl.sstr[j].type == ";")
                {//结束
                    sstin.pop();
                    k = j;
                    set_quaternary();
                    ssf.pop();
                    break;
                }
                else if (tkl.sstr[j].type == "(")
                {//函数赋值
                    n = new_l();
                    qt[n].tr[0] = "func_c";
                    cout << "(" << qt[n].tr[0] << ", , , )" << endl;
                    int jn = j + 1;
                    for (jn; jn < numt; jn++)
                    {
                        sstin.push(tkl.sstr[jn].type);
                        if (tkl.sstr[jn].type == "int" || tkl.sstr[jn].type == "float")
                        {//函数初始变量
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
                        {//判断赋值结束
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
        {//字符型赋值语句
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
        {//判断各个块结束
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



