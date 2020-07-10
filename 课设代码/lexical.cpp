#include"标头.h"


int endnum;
token  Token[150];
char code[10000];//存入源代码
char word[30] = { 0 };
int state = -1;//状态
int   codePointer = 0;//指向code的指针
int num = 1;//总Token串标号
int offset = 0;//区距
struct Ainfl//数组表
{
    int low;
    int up;
    int clen;
};
struct Tapel//类型表
{
    string tval;
    struct Ainfl ainfl;
};

struct Synbl//总符号表
{
    string name;
    struct Tapel tapel;
    string cat;
    int addr;
    int offset;
};
Synbl synbl[20];


void ReadAWord(int& state, char code[], char word[], int& codePointer, int& num)//判断读取当前单词
{
    int i, count = 0, number;
    char ch;
    ch = code[codePointer];
    while (ch == ' ' || ch == '\n')//使当前codepointer指向不为空的字节
    {
        codePointer++;
        ch = code[codePointer];
    }
    for (i = 0; i < 20; i++)
    {
        word[i] = '\0';
    }
    if (isLetter(code[codePointer]))//判断是否为单词
    {
        word[0] = code[codePointer];
        while (isLetter(code[codePointer]) || isDigit(code[codePointer]))
        {
            word[count] = code[codePointer];
            count++;
            codePointer++;
        }
        word[count] = '\0';
        string word_temp = word;
        if (word_temp == "int")//用于识别int类型变量
        {
            count = 0;
            string word_tapel = word;
            int codePointer_temp = codePointer;
            char sh;
            sh = code[codePointer_temp];
            while (sh == ' ' || sh == '\n')
            {
                codePointer_temp++;
                sh = code[codePointer_temp];
            }
            for (i = 0; i < 20; i++)
            {
                word[i] = '\0';
            }
            word[0] = code[codePointer_temp];
            while (isLetter(code[codePointer_temp]) || isDigit(code[codePointer_temp]))
            {
                word[count] = code[codePointer_temp];
                count++;
                codePointer_temp++;
            }
            word[count] = '\0';
            string word_name = word;
            char ah = code[codePointer_temp];
            if (ah == '[')//用于填入数组
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int ainfl_up = atoi(str.c_str());
                int ainfl_low = 0;
                int clen = ainfl_up;
                clen = clen * 4;
                int ainfl_clen = clen;
                synbl[num].name = word_name;
                synbl[num].tapel.tval = "ainfl_int";
                synbl[num].tapel.ainfl.low = ainfl_low;
                synbl[num].tapel.ainfl.up = ainfl_up;
                synbl[num].tapel.ainfl.clen = ainfl_clen;
                synbl[num].cat = 't';
                synbl[num].addr = clen;
                synbl[num].offset = offset;//改动区距
                offset = offset + clen;
                num++;
            }
            else if (ah == '=')//用于填入常量
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int consl = atoi(str.c_str());
                synbl[num].name = word_name;
                synbl[num].tapel.tval = word_tapel;
                synbl[num].cat = 'c';
                synbl[num].addr = consl;
                synbl[num].offset = offset;
                offset = offset + 4;
                num++;
            }
            else
            {
                if (word_name == "main")//用于填入函数
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//用于填入普通变量
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'v';
                    synbl[num].addr = num;
                    synbl[num].offset = offset;
                    offset = offset + 4;
                }
                num++;
            }
        }
        else if (word_temp == "char")//用于识别char类型变量
        {
            count = 0;
            string word_tapel = word;
            int codePointer_temp = codePointer;
            char sh;
            sh = code[codePointer_temp];
            while (sh == ' ' || sh == '\n')
            {
                codePointer_temp++;
                sh = code[codePointer_temp];
            }
            for (i = 0; i < 20; i++)
            {
                word[i] = '\0';
            }
            word[0] = code[codePointer_temp];
            while (isLetter(code[codePointer_temp]) || isDigit(code[codePointer_temp]))
            {
                word[count] = code[codePointer_temp];
                count++;
                codePointer_temp++;
            }
            word[count] = '\0';
            string word_name = word;
            char ah = code[codePointer_temp];
            if (ah == '[')//用于填入数组
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int ainfl_up = atoi(str.c_str());
                int ainfl_low = 0;
                int clen = ainfl_up;
                clen = clen * 1;
                int ainfl_clen = clen;
                synbl[num].name = word_name;
                synbl[num].tapel.tval = "ainfl_char";
                synbl[num].tapel.ainfl.low = ainfl_low;
                synbl[num].tapel.ainfl.up = ainfl_up;
                synbl[num].tapel.ainfl.clen = clen;
                synbl[num].cat = 't';
                synbl[num].addr = clen;
                synbl[num].offset = offset;
                offset = offset + clen;
                num++;
            }
            else if (ah == '=')//用于填入常量
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int consl = atoi(str.c_str());
                synbl[num].name = word_name;
                synbl[num].tapel.tval = word_tapel;
                synbl[num].cat = 'c';
                synbl[num].addr = consl;
                synbl[num].offset = offset;
                offset = offset + 1;
                num++;
            }
            else
            {
                if (word_name == "main")//用于填入函数
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//用于填入普通变量
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'v';
                    synbl[num].addr = num;
                    synbl[num].offset = offset;
                    offset = offset + 1;
                }
                num++;
            }
        }
        else if (word_temp == "float")//用于识别float类型符号
        {
            count = 0;
            string word_tapel = word;
            int codePointer_temp = codePointer;
            char sh;
            sh = code[codePointer_temp];
            while (sh == ' ' || sh == '\n')
            {
                codePointer_temp++;
                sh = code[codePointer_temp];
            }
            for (i = 0; i < 20; i++)
            {
                word[i] = '\0';
            }
            word[0] = code[codePointer_temp];
            while (isLetter(code[codePointer_temp]) || isDigit(code[codePointer_temp]))
            {
                word[count] = code[codePointer_temp];
                count++;
                codePointer_temp++;
            }
            word[count] = '\0';
            string word_name = word;
            char ah = code[codePointer_temp];
            if (ah == '[')//用于填入数组
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int ainfl_up = atoi(str.c_str());
                int ainfl_low = 0;
                int clen = ainfl_up;
                clen = clen * 4;
                int ainfl_clen = clen;
                synbl[num].name = word_name;
                synbl[num].tapel.tval = "ainfl_float";
                synbl[num].tapel.ainfl.low = ainfl_low;
                synbl[num].tapel.ainfl.up = ainfl_up;
                synbl[num].tapel.ainfl.clen = clen;
                synbl[num].cat = 't';
                synbl[num].addr = clen;
                synbl[num].offset = offset;
                offset = offset + clen;
                num++;
            }
            else if (ah == '=')//用于填入常量
            {
                count = 0;
                codePointer_temp++;
                word[0] = code[codePointer_temp];
                while (isDigit(code[codePointer_temp]))
                {
                    word[count] = code[codePointer_temp];
                    count++;
                    codePointer_temp++;
                }
                word[count] = '\0';
                string str = word;
                int consl = atoi(str.c_str());
                synbl[num].name = word_name;
                synbl[num].tapel.tval = word_tapel;
                synbl[num].cat = 'c';
                synbl[num].addr = consl;
                synbl[num].offset = offset;
                offset = offset + 4;
                num++;
            }
            else
            {
                if (word_name == "main")//用于填入函数
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//用于填入普通变量
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'v';
                    synbl[num].addr = num;
                    synbl[num].offset = offset;
                    offset = offset + 4;
                }
                num++;
            }
        }

    }
    else if (isDigit(code[codePointer]))//判断是否为数字
    {
        while (isDigit(code[codePointer]))
        {
            codePointer++;
        }
        if (code[codePointer] == '.')
        {
            codePointer++;
            while (isDigit(code[codePointer]))
            {
                codePointer++;
            }
        }
    }
    else if (code[codePointer] == '"')//判断是否为字符串
    {
        codePointer++;
        while (code[codePointer] != '"')
        {
            codePointer++;
        }
        codePointer++;
    }
    else if (code[codePointer] == '\'')//判断是否为单个字符
    {
        codePointer++;
        while (code[codePointer] != '\'')
        {
            codePointer++;
        }
        codePointer++;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' || ch == ',' || ch == ';' || ch == '[' || ch == ']')//判断是否为单界符
    {
        codePointer++;
    }
    else if (code[codePointer] == '>')//两个字节的运算符'>='或'>>'
    {
        if (code[codePointer + 1] == '=' || code[codePointer + 1] == '>')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '<')//两个字节的运算符'<='或'<<'
    {
        if (code[codePointer + 1] == '=' || code[codePointer + 1] == '<')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '=')//两个字节的运算符'=='
    {
        if (code[codePointer + 1] == '=')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '!')//两个字节的运算符'!='
    {
        word[0] = code[codePointer];
        if (code[codePointer + 1] == '=')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '&')//两个字节的运算符'&&'
    {
        if (code[codePointer + 1] == '&')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '|')//两个字节的运算符'||'
    {
        if (code[codePointer + 1] == '|')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '+' || code[codePointer] == '-' || code[codePointer] == '*' || code[codePointer] == '/')//两个字节的运算符'+='、'-='、'*='、'/='
    {
        if (code[codePointer + 1] == '=')
        {
            codePointer = codePointer + 2;
        }
        else
        {
            codePointer++;
        }
    }
    else if (code[codePointer] == '$')//强制结束
    {
        state = 0;
    }
    else
    {
        state = 0;
    }
}


void init1()//用于初始化
{
    ifstream fp("e:\\code.txt");//将文本读取的内容全部放入fp中
    if (!fp.is_open())//成功打开返回1，失败0
    {
        cout << "文件打开失败";
    }
    fp.seekg(0, ios::beg);//指针fp从文件开头向后移动0个字节，即指向第一个字节
    while (!fp.eof())//检测是否到达文件尾，如果到达文件尾返回非0值
    {
        fp.read((char*)&code[codePointer], 1);//每次读一个字节到code里
        codePointer++;
    }
    code[++codePointer] = '\0';//字符串结束标志
    fp.close();
    
    codePointer = 0;
}
void table()
{
    init1();
    while (state != 0)
    {
        ReadAWord(state, code, word, codePointer, num);
    }
    cout << endl;
    cout << endl;
    
    cout << "------------------------------------------------------------" << endl;
    cout << "符号表:" << endl;
    for (int i = 0; i < 10; i++)//用于测试的代码
    {
        if (synbl[i].cat == "c")
        {
            cout << '(' << i << ')' << "名称:" << synbl[i].name << ',' << "类型:" << synbl[i].tapel.tval << ','
                << "种类:" << synbl[i].cat << ',' << "值:" << synbl[i].addr << ',' << "偏移量:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "v")
        {
            cout << '(' << i << ')' << "名称:" << synbl[i].name << ',' << "类型:" << synbl[i].tapel.tval << ','
                << "种类:" << synbl[i].cat << ',' << "偏移量:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "f")
        {
            cout << '(' << i << ')' << "名称:" << synbl[i].name << ',' << "类型:" << synbl[i].tapel.tval << ','
                << "种类:" << synbl[i].cat << ',' << "偏移量:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "t")
        {
            cout << '(' << i << ')' << "名称:" << synbl[i].name << ',' << "类型:" << synbl[i].tapel.tval << ',' << "数组下界:" << synbl[i].tapel.ainfl.low << ','
                << "数组上界:" << synbl[i].tapel.ainfl.up << ',' << "数组长度:" << synbl[i].tapel.ainfl.clen << ',' << "类型:" << synbl[i].cat << ','
                << "LENL:" << synbl[i].addr << ',' << "偏移量:" << synbl[i].offset << endl;
        }
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

}




static char reserveWord[60][20] =
{
                "int","float","char","auto", "break", "bool","case","catch", "class", "const",
                "continue", "default", "define", "delete", "do", "double", "else",
                "enum","explicit","export", "extern","false","if","while",
                "friend", "goto","inline", "long", "main","namespace",
                "new", "operator", "private", "protected", "public""register",
                "return", "short", "signed", "sizeof", "static","struct", "switch",
                "template", "this", "throw", "true", "try", "typedef", "typename",
                "union", "unsigned", "using","virtual", "void","volatile"
};//关键字表
char KT[1001][20] = { "" };//用来存储的关键字表
int KTSize = 0;
char IT[1001][20] = { "" };//标识符表
int ITSize = 0;
char charT[1000] = { "" };//单个字符表
int charTSize = 0;
char ST[1001][20] = { "" };//字符串表
int STSize = 0;
char constT[1001][20] = { "" };//常数表
int constTSize = 0;
char PT[1000][20] = { "" };
int PTSize;
char PT_temp[20] = { '+','-','*','/','(',')','{','}',',',';','\'','"' };//界符表



token KTtoken[50];
token ITtoken[50];
token charTtoken[50];
token STtoken[50];
token constTtoken[50];
token PTtoken[50];


bool isLetter(char ch)//判断是否为字母
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isDigit(char ch)//判断是否为数字
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Search(char a[][20], char word[])//观察当前单词是否在表中已经存在，若不存在则加入其中
{
    for (int i = 0; a[i][0] != '\0'; i++)
    {
        if (strcmp(a[i], word) == 0)
            return i + 1;
    }
    return -1;
}

void readAWord(int& state, char code[], char word[], int& codePointer, int& num)//判断当前单词属于哪个表
{
    int i, count = 0, temp = 0, number;
    char ch;
    ch = code[codePointer];
    while (ch == ' ' || ch == '\n')//使当前codepointer指向不为空的字节
    {
        codePointer++;
        ch = code[codePointer];
    }
    for (i = 0; i < 20; i++)
    {
        word[i] = '\0';
    }
    if (isLetter(code[codePointer]))//判断是否为单词
    {
        word[0] = code[codePointer];
        while (isLetter(code[codePointer]) || isDigit(code[codePointer]))
        {
            word[count] = code[codePointer];
            count++;
            codePointer++;
        }
        word[count] = '\0';
        state = Search(reserveWord, word);
        if (state != 1 && state != 2 && state != 3&&state!=23&&state!=24)
        {
            Token[num].type = word;
            Token[num].typeTSize = 1;
            num++;
            state = Search(reserveWord, word);
            if (state == -1)
            {
                number = Search(IT, word);
                if (number == -1)
                {
                    strcpy_s(IT[ITSize++], word);
                    number = ITSize;
                }
                ITtoken[number].type = "IT";
                ITtoken[number].typeTSize = number;
            }
            else
            {
                number = Search(KT, word);
                if (number == -1)
                {
                    strcpy_s(KT[KTSize++], word);
                    number = KTSize;
                }
                KTtoken[number].type = "KT";
                KTtoken[number].typeTSize = number;
            }
        }
        else
        {
            number = Search(reserveWord, word);
            if (number == 1)
            {
                Token[num].type = "int";
                Token[num].typeTSize = 3;
                num++;
            }
            else if (number == 2)
            {
                Token[num].type = "float";
                Token[num].typeTSize = 4;
                num++;
            }
            else if (number == 3)
            {
                Token[num].type = "char";
                Token[num].typeTSize = 5;
                num++;
            }
            else if (number == 23)
            {
                Token[num].type = "if";
                Token[num].typeTSize = 23;
                num++;
            }
            else if (number == 24)
            {
                Token[num].type = "while";
                Token[num].typeTSize = 24;
                num++;
            }

            state = Search(reserveWord, word);
            if (state == -1)
            {
                number = Search(IT, word);
                if (number == -1)
                {
                    strcpy_s(IT[ITSize++], word);
                    number = ITSize;
                }
                ITtoken[number].type = "IT";
                ITtoken[number].typeTSize = number;
            }
            else
            {
                number = Search(KT, word);
                if (number == -1)
                {
                    strcpy_s(KT[KTSize++], word);
                    number = KTSize;
                }
                KTtoken[number].type = "KT";
                KTtoken[number].typeTSize = number;
            }
        }
    }
    else if (isDigit(code[codePointer]))//判断是否为数字
    {
        word[0] = code[codePointer];
        while (isDigit(code[codePointer]))
        {
            word[count] = code[codePointer];
            count++;
            codePointer++;
        }
        if (code[codePointer] == '.')
        {
            word[count] = code[codePointer];
            count++;
            codePointer++;
            while (isDigit(code[codePointer]))
            {
                word[count] = code[codePointer];
                count++;
                codePointer++;
            }
        }
        word[count] = '\0';
        Token[num].type = word;
        Token[num].typeTSize = 2;
        num++;
        state = Search(constT, word);
        if (state == -1)
        {
            strcpy_s(constT[constTSize++], word);
            state = constTSize;
        }
        constTtoken[state].type = "constT";
        constTtoken[state].typeTSize = state;
    }
    else if (code[codePointer] == '"')//判断是否为字符串
    {
        word[0] = code[codePointer];
        word[1] = '\0';
        number = Search(PT, word);
        if (number == -1)
        {
            PT[PTSize++][0] = '"';
            number = PTSize;
        }
        PTtoken[number].type = "PT";
        PTtoken[number].typeTSize = number;
        codePointer++;
        while (code[codePointer] != '"')
        {
            word[count] = code[codePointer];
            count++;
            codePointer++;
        }
        word[count] = '\0';
        state = Search(ST, word);
        if (state == -1)
        {
            strcpy_s(ST[STSize], word);
            STSize++;
            state = STSize;
        }
        STtoken[state].type = "ST";
        STtoken[state].typeTSize = state;
        PTtoken[number].type = "PT";
        PTtoken[number].typeTSize = number;
        codePointer++;
    }
    else if (code[codePointer] == '\'')//判断是否为单个字符
    {
        word[0] = code[codePointer];
        word[1] = '\0';
        number = Search(PT, word);
        if (number == -1)
        {
            PT[PTSize++][0] = '\'';
            number = PTSize;
        }
        PTtoken[number].type = "PT";
        PTtoken[number].typeTSize = number;
        codePointer++;
        for (state = 0; state < charTSize; state++)
        {
            if (code[codePointer] == charT[state])
            {
                break;
            }
        }
        if (state == charTSize)
        {
            charT[charTSize] = code[codePointer];
            charTSize++;
            state = charTSize;
        }
        charTtoken[state].type = "charT";
        charTtoken[state].typeTSize = state;
        PTtoken[number].type = "PT";
        PTtoken[number].typeTSize = number;
        codePointer = codePointer + 2;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' || ch == ',' || ch == ';')//判断是否为单界符
    {
        word[0] = code[codePointer];
        word[1] = '\0';
        number = Search(PT, word);
        for (int j = 0; j < 10; j++)
        {
            temp = j;
            if (word[0] == PT_temp[j])
                break;
        }
        Token[num].type = PT_temp[temp];
        temp += 12;
        Token[num].typeTSize = temp;
        num++;
        if (number == -1)
        {
            strcpy_s(PT[PTSize], word);
            PTSize++;
            number = PTSize;
        }
        PTtoken[number].type = "PT";
        PTtoken[number].typeTSize = number;
        codePointer++;
    }
    else if (code[codePointer] == '>')//两个字节的运算符'>='
    {
        word[0] = code[codePointer];
        if (code[codePointer + 1] == '=')
        {
            word[1] = code[codePointer + 1];
            Token[num].type= ">=";
            Token[num].typeTSize = 9;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer += 2;
        }
        else
        {
            word[1] = '\0';
            Token[num].type = ">";
            Token[num].typeTSize = 8;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer++;
        }
    }
    else if (code[codePointer] == '=')//两个字节的运算符
    {
        word[0] = code[codePointer];
        if (code[codePointer + 1] == '=')
        {
            word[1] = code[codePointer + 1];
            Token[num].type= "==";
            Token[num].typeTSize = 6;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer += 2;
        }
        else
        {
            word[1] = '\0';
            Token[num].type = "=";
            Token[num].typeTSize = 22;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer++;
        }
    }
    else if (code[codePointer] == '<')//两个字节的运算符'>='或'>>'
    {
        word[0] = code[codePointer];
        if (code[codePointer + 1] == '=')
        {
            word[1] = code[codePointer + 1];
            Token[num].type= "<=";
            Token[num].typeTSize = 11;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer += 2;
        }
        else
        {
            word[1] = '\0';
            Token[num].type = "<";
            Token[num].typeTSize = 10;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer++;
        }
    }
    else if (code[codePointer] == '!')//两个字节的运算符'!='
    {
        word[0] = code[codePointer];
        if (code[codePointer + 1] == '=')
        {
            word[1] = code[codePointer + 1];
            Token[num].type= "!=";
            Token[num].typeTSize = 7;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer += 2;
        }
        else
        {
            word[1] = '\0';
            Token[num].type = "!";
            Token[num].typeTSize = 23;
            num++;
            number = Search(PT, word);
            if (number == -1)
            {
                strcpy_s(PT[PTSize], word);
                PTSize++;
                number = PTSize;
            }
            PTtoken[number].type = "PT";
            PTtoken[number].typeTSize = number;
            codePointer++;
        }
    }
    else if (code[codePointer] == '$')//强制结束
    {
           state = 0;
           Token[num].typeTSize = 0;
           

        
    }
    else
    {
        state = 0;
    }
}
void init()
{
    ifstream fp("E:\\code.txt");//将文本读取的内容全部放入fp中
    if (!fp.is_open())//成功打开返回1，失败0
    {
        cout << "文件打开失败";
    }
    fp.seekg(0, ios::beg);//指针fp从文件开头向后移动0个字节，即指向第一个字节
    while (!fp.eof())//检测是否到达文件尾，如果到达文件尾返回非0值
    {
        fp.read((char*)&code[codePointer], 1);//每次读一个字节到code里
        codePointer++;
    }
    code[++codePointer] = '\0';//字符串结束标志
    fp.close();
    
    codePointer = 0;
    cout << "TOKEN序列如下：" << endl;
}
void readtoken()
{
    readAWord(state, code, word, codePointer, num);
    if (state != 0)
    {
        num--;
        cout << "(" << Token[num].type << "," << Token[num].typeTSize << ")" << endl;
        num++;
    }
}
void cifafenxiqizongti()//词法分析器总体
{
    init();
    while (state != 0)
    {
        readtoken();
    }
    endnum = num;
     state = -1;//状态
     num = 1;//总Token串标号
    table();



}










