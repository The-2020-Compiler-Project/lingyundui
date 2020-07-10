
#include"标头.h"

extern sstack sstin, sstout, ssf;
extern int num;
extern int endnum;
extern   token Token[150];



struct tokenline
{//token列，便于调用
    struct token sstr[maxlen];
    int len;
};




int main()
{
    int right = 1;
    
    cifafenxiqizongti();
    
    right = Parse();
    if (right == 1)
    {

        string sin;
        int numt;
        numt = endnum ;
        struct token tks;
        struct   tokenline    tkls;
        tkls.len = numt;
        for (int i = 1; i <= numt; i++)
        {
            tks.type = Token[i].type;
            tkls.sstr[i] = tks;
        }
        

        set_all(tkls, numt);
        sstin.sclear();
        sstout.sclear();
        ssf.sclear();



        rain();
        system("pause");
    }







     
}




















