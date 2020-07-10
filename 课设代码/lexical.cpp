#include"��ͷ.h"


int endnum;
token  Token[150];
char code[10000];//����Դ����
char word[30] = { 0 };
int state = -1;//״̬
int   codePointer = 0;//ָ��code��ָ��
int num = 1;//��Token�����
int offset = 0;//����
struct Ainfl//�����
{
    int low;
    int up;
    int clen;
};
struct Tapel//���ͱ�
{
    string tval;
    struct Ainfl ainfl;
};

struct Synbl//�ܷ��ű�
{
    string name;
    struct Tapel tapel;
    string cat;
    int addr;
    int offset;
};
Synbl synbl[20];


void ReadAWord(int& state, char code[], char word[], int& codePointer, int& num)//�ж϶�ȡ��ǰ����
{
    int i, count = 0, number;
    char ch;
    ch = code[codePointer];
    while (ch == ' ' || ch == '\n')//ʹ��ǰcodepointerָ��Ϊ�յ��ֽ�
    {
        codePointer++;
        ch = code[codePointer];
    }
    for (i = 0; i < 20; i++)
    {
        word[i] = '\0';
    }
    if (isLetter(code[codePointer]))//�ж��Ƿ�Ϊ����
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
        if (word_temp == "int")//����ʶ��int���ͱ���
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
            if (ah == '[')//������������
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
                synbl[num].offset = offset;//�Ķ�����
                offset = offset + clen;
                num++;
            }
            else if (ah == '=')//�������볣��
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
                if (word_name == "main")//�������뺯��
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//����������ͨ����
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
        else if (word_temp == "char")//����ʶ��char���ͱ���
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
            if (ah == '[')//������������
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
            else if (ah == '=')//�������볣��
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
                if (word_name == "main")//�������뺯��
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//����������ͨ����
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
        else if (word_temp == "float")//����ʶ��float���ͷ���
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
            if (ah == '[')//������������
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
            else if (ah == '=')//�������볣��
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
                if (word_name == "main")//�������뺯��
                {
                    synbl[num].name = word_name;
                    synbl[num].tapel.tval = word_tapel;
                    synbl[num].cat = 'f';
                }
                else//����������ͨ����
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
    else if (isDigit(code[codePointer]))//�ж��Ƿ�Ϊ����
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
    else if (code[codePointer] == '"')//�ж��Ƿ�Ϊ�ַ���
    {
        codePointer++;
        while (code[codePointer] != '"')
        {
            codePointer++;
        }
        codePointer++;
    }
    else if (code[codePointer] == '\'')//�ж��Ƿ�Ϊ�����ַ�
    {
        codePointer++;
        while (code[codePointer] != '\'')
        {
            codePointer++;
        }
        codePointer++;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' || ch == ',' || ch == ';' || ch == '[' || ch == ']')//�ж��Ƿ�Ϊ�����
    {
        codePointer++;
    }
    else if (code[codePointer] == '>')//�����ֽڵ������'>='��'>>'
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
    else if (code[codePointer] == '<')//�����ֽڵ������'<='��'<<'
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
    else if (code[codePointer] == '=')//�����ֽڵ������'=='
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
    else if (code[codePointer] == '!')//�����ֽڵ������'!='
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
    else if (code[codePointer] == '&')//�����ֽڵ������'&&'
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
    else if (code[codePointer] == '|')//�����ֽڵ������'||'
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
    else if (code[codePointer] == '+' || code[codePointer] == '-' || code[codePointer] == '*' || code[codePointer] == '/')//�����ֽڵ������'+='��'-='��'*='��'/='
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
    else if (code[codePointer] == '$')//ǿ�ƽ���
    {
        state = 0;
    }
    else
    {
        state = 0;
    }
}


void init1()//���ڳ�ʼ��
{
    ifstream fp("e:\\code.txt");//���ı���ȡ������ȫ������fp��
    if (!fp.is_open())//�ɹ��򿪷���1��ʧ��0
    {
        cout << "�ļ���ʧ��";
    }
    fp.seekg(0, ios::beg);//ָ��fp���ļ���ͷ����ƶ�0���ֽڣ���ָ���һ���ֽ�
    while (!fp.eof())//����Ƿ񵽴��ļ�β����������ļ�β���ط�0ֵ
    {
        fp.read((char*)&code[codePointer], 1);//ÿ�ζ�һ���ֽڵ�code��
        codePointer++;
    }
    code[++codePointer] = '\0';//�ַ���������־
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
    cout << "���ű�:" << endl;
    for (int i = 0; i < 10; i++)//���ڲ��ԵĴ���
    {
        if (synbl[i].cat == "c")
        {
            cout << '(' << i << ')' << "����:" << synbl[i].name << ',' << "����:" << synbl[i].tapel.tval << ','
                << "����:" << synbl[i].cat << ',' << "ֵ:" << synbl[i].addr << ',' << "ƫ����:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "v")
        {
            cout << '(' << i << ')' << "����:" << synbl[i].name << ',' << "����:" << synbl[i].tapel.tval << ','
                << "����:" << synbl[i].cat << ',' << "ƫ����:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "f")
        {
            cout << '(' << i << ')' << "����:" << synbl[i].name << ',' << "����:" << synbl[i].tapel.tval << ','
                << "����:" << synbl[i].cat << ',' << "ƫ����:" << synbl[i].offset << endl;
        }
        else if (synbl[i].cat == "t")
        {
            cout << '(' << i << ')' << "����:" << synbl[i].name << ',' << "����:" << synbl[i].tapel.tval << ',' << "�����½�:" << synbl[i].tapel.ainfl.low << ','
                << "�����Ͻ�:" << synbl[i].tapel.ainfl.up << ',' << "���鳤��:" << synbl[i].tapel.ainfl.clen << ',' << "����:" << synbl[i].cat << ','
                << "LENL:" << synbl[i].addr << ',' << "ƫ����:" << synbl[i].offset << endl;
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
};//�ؼ��ֱ�
char KT[1001][20] = { "" };//�����洢�Ĺؼ��ֱ�
int KTSize = 0;
char IT[1001][20] = { "" };//��ʶ����
int ITSize = 0;
char charT[1000] = { "" };//�����ַ���
int charTSize = 0;
char ST[1001][20] = { "" };//�ַ�����
int STSize = 0;
char constT[1001][20] = { "" };//������
int constTSize = 0;
char PT[1000][20] = { "" };
int PTSize;
char PT_temp[20] = { '+','-','*','/','(',')','{','}',',',';','\'','"' };//�����



token KTtoken[50];
token ITtoken[50];
token charTtoken[50];
token STtoken[50];
token constTtoken[50];
token PTtoken[50];


bool isLetter(char ch)//�ж��Ƿ�Ϊ��ĸ
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

bool isDigit(char ch)//�ж��Ƿ�Ϊ����
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

int Search(char a[][20], char word[])//�۲쵱ǰ�����Ƿ��ڱ����Ѿ����ڣ������������������
{
    for (int i = 0; a[i][0] != '\0'; i++)
    {
        if (strcmp(a[i], word) == 0)
            return i + 1;
    }
    return -1;
}

void readAWord(int& state, char code[], char word[], int& codePointer, int& num)//�жϵ�ǰ���������ĸ���
{
    int i, count = 0, temp = 0, number;
    char ch;
    ch = code[codePointer];
    while (ch == ' ' || ch == '\n')//ʹ��ǰcodepointerָ��Ϊ�յ��ֽ�
    {
        codePointer++;
        ch = code[codePointer];
    }
    for (i = 0; i < 20; i++)
    {
        word[i] = '\0';
    }
    if (isLetter(code[codePointer]))//�ж��Ƿ�Ϊ����
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
    else if (isDigit(code[codePointer]))//�ж��Ƿ�Ϊ����
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
    else if (code[codePointer] == '"')//�ж��Ƿ�Ϊ�ַ���
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
    else if (code[codePointer] == '\'')//�ж��Ƿ�Ϊ�����ַ�
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
        ch == '{' || ch == '}' || ch == ',' || ch == ';')//�ж��Ƿ�Ϊ�����
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
    else if (code[codePointer] == '>')//�����ֽڵ������'>='
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
    else if (code[codePointer] == '=')//�����ֽڵ������
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
    else if (code[codePointer] == '<')//�����ֽڵ������'>='��'>>'
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
    else if (code[codePointer] == '!')//�����ֽڵ������'!='
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
    else if (code[codePointer] == '$')//ǿ�ƽ���
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
    ifstream fp("E:\\code.txt");//���ı���ȡ������ȫ������fp��
    if (!fp.is_open())//�ɹ��򿪷���1��ʧ��0
    {
        cout << "�ļ���ʧ��";
    }
    fp.seekg(0, ios::beg);//ָ��fp���ļ���ͷ����ƶ�0���ֽڣ���ָ���һ���ֽ�
    while (!fp.eof())//����Ƿ񵽴��ļ�β����������ļ�β���ط�0ֵ
    {
        fp.read((char*)&code[codePointer], 1);//ÿ�ζ�һ���ֽڵ�code��
        codePointer++;
    }
    code[++codePointer] = '\0';//�ַ���������־
    fp.close();
    
    codePointer = 0;
    cout << "TOKEN�������£�" << endl;
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
void cifafenxiqizongti()//�ʷ�����������
{
    init();
    while (state != 0)
    {
        readtoken();
    }
    endnum = num;
     state = -1;//״̬
     num = 1;//��Token�����
    table();



}










