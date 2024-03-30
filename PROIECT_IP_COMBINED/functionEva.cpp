#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <cmath>
#include <stack>
#include "functionEva.h"
#define pi 3.14159
#define e 2.71
using namespace std;
stack<char> stiva;
stack<double> f;
int priority(char op)
{
    if((op=='+'||op=='-')||op=='^')
        return 1;
    if(op=='*'||op=='/')
        return 2;
    if(op>='a'&&op<='z')
        return 3;
    if(op=='(')
        return 4;
    return 0;
}
int codingFunction(char input[], int& i)
{
    if((input[i]=='s'&&input[i+1]=='i')&&(input[i+2]=='n'&&input[i+3]=='('))//sin
    {
        i=i+2;
        return 's';
    }
    if((input[i]=='c'&&input[i+1]=='o')&&(input[i+2]=='s'&&input[i+3]=='('))//cos
    {
        i=i+2;
        return 'o';
    }
    if((input[i]=='c'&&input[i+1]=='t')&&(input[i+2]=='g'&&input[i+3]=='('))//ctg
    {
        i=i+2;
        return 'c';
    }
    if(input[i]=='l'&&(input[i+1]=='n'&&input[i+2]=='('))//ln
    {
        i=i+1;
        return 'l';
    }
    if(input[i]=='l'&&(input[i+1]=='g'&&input[i+2]=='('))//lg
    {
        i=i+1;
        return 'g';
    }
    if(input[i]=='t'&&(input[i+1]=='g'&&input[i+2]=='('))//tg
    {
        i=i+1;
        return 't';
    }
    if(((input[i]=='a'&&input[i+1]=='r')&&(input[i+2]=='c'&&input[i+3]=='s'))&&((input[i+4]=='i'&&input[i+5]=='n')&&input[i+6]=='('))//arcsin
    {
        i=i+5;
        return 'a';
    }
    if(((input[i]=='a'&&input[i+1]=='r')&&(input[i+2]=='c'&&input[i+3]=='c'))&&((input[i+4]=='o'&&input[i+5]=='s')&&input[i+6]=='('))//arccos
    {
        i=i+5;
        return 'r';
    }
    if(((input[i]=='s'&&input[i+1]=='q')&&(input[i+2]=='r'&&input[i+3]=='t'))&&input[i+4]=='(')//sqrt
    {
        i=i+3;
        return 'q';
    }
    if(input[i]=='p'&&input[i+1]=='i')
    {
        i=i+1;
        return '#';
    }
    if(input[i]=='e')
    {
        i=i+0;
        return '%';
    }
    return -1;
}
void nrToChar(double nr, char nrChar[])
{
    int contor=0, cf,k,vN[10],vQ[10],i=-1,j=-1,aux;
    if(nr<=-0.1)
    {
        nrChar[0]='-';
        contor++;
        nr=nr*(-1);
    }
    if(int(nr)==0)
    {
        nrChar[contor]='0';
        contor++;
    }
    int n=nr;
    double q=nr-n;
    if(q>=0.1)
        while(q && i<1)
        {
            q=q*10;
            vQ[++i]=q;
            q=q-int(q);
        }
    while(n)
    {
        cf=n%10;
        vN[++j]=cf;
        n=n/10;
    }
    for(aux=j; aux>=0; aux--)
        nrChar[contor++]=vN[aux]+48;
    if(i!=-1)
    {
        nrChar[contor++]='.';
        for(aux=0; aux<=i; aux++)
            nrChar[contor++]=vQ[aux]+48;
    }
    nrChar[contor]=NULL;
}
double specificFunction(double a, char sF)
{
    switch(sF)
    {
    case 's':
        return sin(a);
    case 'o':
        return cos(a);
    case 'c':
        return 1/tan(a);
    case 't':
        return tan(a);
    case 'l':
        return log(a);
    case 'g':
        return log10(a);
    case 'a':
        return asin(a);
    case 'q':
        return sqrt(a);
    case 'r':
        return acos(a);
    }
}
double applyOp(double a, double b, char op)
{
    switch(op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a,b);
    }
}
bool coordVerf(int x, int y)
{
    if((x>=50&&y>=50)&&(x<=1000-50&&y<=700-50))
        return 1;
    else
        return 0;
}
int lenghtLine(int x1, int y1, int x2, int y2)
{
    int lenght,p1,p2;
    p1=(x1-x2)*(x1-x2);
    p2=(y1-y2)*(y1-y2);
    lenght=sqrt(p1+p2);
    return lenght;
}
double fCoords(char postfix[][10],int j, double x)
{
    int i,contor=0;
    double nr1,nr2,r,numar;
    for(i=0; i<=j; i++)
    {
        if(strchr("+-/^*abcdefghijklmnopqrstuvwyz#%",postfix[i][0])==0||strchr("+-/^*abcdefghijklmnopqrstuvwyz#%",postfix[i][1])==0)
        {
            if(postfix[i][0]=='x')
                f.push(x);
            else
            {
                contor=1;
                numar=atof(postfix[i]);
                /*numar=postfix[i][0]-48;
                while(postfix[i][contor]!=NULL)
                {
                    numar=numar*10+postfix[i][contor]-48;
                    contor++;
                }*/
                f.push(numar);
            }
        }
        else
        {
            if(postfix[i][0]=='#')
                f.push(pi);
            if(postfix[i][0]=='%')
                f.push(e);
            if(strchr("abcdefghijklmnopqrstuvwyz#%",postfix[i][0])==0)
            {
                nr1=f.top();
                f.pop();
                nr2=f.top();
                f.pop();
                f.push(applyOp(nr2,nr1,postfix[i][0]));
            }
            if((postfix[i][0]>='a'&&postfix[i][0]<='z')&&postfix[i][0]!='x')
            {
                nr1=f.top();
                f.pop();
                f.push(specificFunction(nr1,postfix[i][0]));
            }
        }
    }
    r=f.top();
    f.pop();
    return r;
}
int functionCheck(char input[])///0= Totul bine; 1= Eroare de sintaxa; 2= Vezi legenda; 3= Eroare paranteze
{
    int ct=0;
    for(int i=0; i<=strlen(input); i++)
    {
        if(strchr("+-/*()^abcdefghijklmnopqrstuvwyz",input[i])==0)
        {
            if(!isdigit(input[i-1])&&(input[i]=='0'&&input[i+1]=='0'))
                return 1;
            if(input[i]=='x'&&(input[i-1]=='x'||input[i+1]=='x'))
                return 1;
        }
        else
        {
            if(input[i]>='a'&&input[i]<='z')
            {
                char code=codingFunction(input,i);
                if(code==-1)
                    return 2;
            }
            if(strchr("+-/*^",input[i])!=0 && (strchr("+-/*^",input[i-1])!=0))
                return 1;
            if(input[i]==')'&&input[i-1]=='(')
                return 1;
            if(input[i]=='(')
                ct++;
            if(input[i]==')')
                ct--;
        }
    }
    if(ct!=0)
        return 3;
    return 0;
}
void postF(char input[],char postfix[][10], int &j)
{
    int i,contor=0,numar;
    /// Postfixare
    for(i=0; i<=strlen(input); i++)
    {
        if(strchr("+-/*()^abcdefghijklmnopqrstuvwyz",input[i])==0)
        {
            if((isdigit(input[i])&&(isdigit(input[i-1])||input[i-1]=='.'))||(input[i]=='.'||(postfix[j][0]=='-'&&isdigit(input[i]))))
            {
                postfix[j][++contor]=input[i];
            }
            else
            {
                postfix[j][++contor]=NULL;
                j++;
                contor=0;
                postfix[j][contor]=input[i];
            }
        }
        else if(input[i]==')')
        {
            while(stiva.top()!='(')
            {
                j++;
                postfix[j][0]=stiva.top();
                postfix[j][1]=NULL;
                stiva.pop();
            }
            stiva.pop();
            if(strchr("abcdefghijklmnopqrstuvwyz",input[i])!=0)
            {
                j++;
                postfix[j][0]=stiva.top();
                postfix[j][1]=NULL;
                stiva.pop();
            }
        }
        else
        {
            while((stiva.empty()==0&&stiva.top()!='(')&&priority(stiva.top())>=priority(input[i]))
            {
                j++;
                postfix[j][0]=stiva.top();
                postfix[j][1]=NULL;
                stiva.pop();
            }
            if(input[i]>='a'&&input[i]<='z')
            {
                char code=codingFunction(input,i);
                if(code=='%'||code=='#')
                {
                    postfix[j][++contor]=NULL;
                    j++;
                    contor=0;
                    postfix[j][contor]=code;
                }
                else
                    stiva.push(code);
            }
            else
            {
                if(input[i]=='-'&&(i==0||input[i-1]=='('))
                {
                    postfix[j][++contor]=NULL;
                    j++;
                    contor=0;
                    postfix[j][contor]=input[i];
                }
                else
                    stiva.push(input[i]);
            }
        }
    }
    while(stiva.empty()!=0)
    {
        postfix[j][++contor]=NULL;
        j++;
        postfix[j][0]=stiva.top();
        postfix[j][1]=NULL;
        stiva.pop();
    }
}
