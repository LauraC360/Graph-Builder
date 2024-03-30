#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <stack>
#include <cmath>
#include "functionEva.h"
#define pi 3.14159

using namespace std;

ofstream fout("date.out");

char input[200]="",input_1[200]="",input1[30]="", input2[30]="", input3[30]="",strA[30], strB[30];;
int m_1 = 0,m = 0,sizeA, sizeB,functionsGraphed = 0,oldwindow,newwindow, window_Graph, functionWindow,line_point,j=-1;
bool incorrect = 0, cDL,started;;
char postfixAO[100][10], NR[10],postfix[100][10];
bool DarkLight; // dark = 0, light = 1
bool Language=0; // engleza = 0, 1 = romana
bool settingsChange;
float nrUnit,maxim,minim,unit,i1,i2,StgDrp=0;

struct buttons
{
    bool rad=0;
    bool mm=0;
    bool ip=0;
    bool as=0;
    bool menu=0;
} bt;

void redraw()
{
    if(Language == 0) readimagefile("images/fx_background_v1English_1.jpg",0,0,800,448);
    else readimagefile("images/fx_background_v1_RO.jpg",0,0,800,448);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);

    outtextxy(37,155,input1);
    outtextxy(37,155+30,input2);
    outtextxy(37,155+30*2,input3);

    settextstyle(0,HORIZ_DIR,1);
}

//functii pt fereastra grafului

void functionEvaluation(char input[],double a, double b)
{
    cDL=DarkLight;
    int i,contor=0,numar;
    double ex=-1,ey=-1,x,y,nr1,nr2,ratia=100/unit,r;
    maxim=-999999;
    minim=999999;

    /// Calculare coordonate
    setcolor(LIGHTMAGENTA);
    x = i1;
    do
    {
        r=fCoords(postfix,j,x);
        if(r>maxim)
            maxim=r;
        if(r<minim)
            minim=r;
        y=-r*ratia+350;
        if(ex!=-1 && ey!=-1)
        {
            if(coordVerf(ex,ey)==1)
            {
                setlinestyle(0,0,3);
                if(coordVerf(x*ratia+500+StgDrp,y)==1)
                {
                    line(ex,ey,x*ratia+500+StgDrp,y);
                }
                else
                {
                    if(y<50)
                        line(ex,ey,ex,50);
                    if(y>650)
                        line(ex,ey,ex,650);
                }
            }
            else
            {
                if(coordVerf(x*ratia+500+StgDrp,y)==1)
                {
                    setlinestyle(0,0,3);
                    if(ey<50)
                        line(x*ratia+500+StgDrp,y,x*ratia+500+StgDrp,50);
                    if(ey>650)
                        line(x*ratia+500+StgDrp,y,x*ratia+500+StgDrp,650);
                }
            }
        }
        ex=x*ratia+500+StgDrp;
        ey=y;
        x=x+(i2-i1)*0.0001;
    }
    while(x<=i2);
    setlinestyle(0,0,1);
    setcolor(WHITE);
    DarkLight=cDL;
}

void xoy(int a, int b)
{
    int clr1,clr2;
    char nrChar[100];
    double unitPx; ///De modificat aici
    unitPx=100/(unit/nrUnit);
    if(DarkLight)
    {
        setbkcolor(WHITE);
        cleardevice();
        readimagefile("images/GraphfLIGHT.jpg",0,0,1000,700);
        setcolor(LIGHTGRAY);
        clr1=0;
        clr2=7;
    }
    else
    {
        readimagefile("images/GraphfDARK.jpg",0,0,1000,700);
        setcolor(DARKGRAY);
        clr1=15;
        clr2=8;
    }
    int j=1;
    float numar=nrUnit;
    for(float i=500+StgDrp+unitPx; i<=a-50; i=i+unitPx)
    {
        line(i,50,i,b-50);
        setcolor(clr1);
        if(i>=50)
        {
            nrToChar(numar,nrChar);
            outtextxy(i-8,30,nrChar);
        }
        numar=numar+nrUnit;
        setcolor(clr2);
    }
    numar=-nrUnit;
    for(int i=500+StgDrp-unitPx; i>=50; i=i-unitPx)
    {
        line(i,50,i,b-50);
        setcolor(clr1);
        if(i<=a-50)
        {
            nrToChar(numar,nrChar);
            outtextxy(i-8,30,nrChar);
        }
        numar=numar-nrUnit;
        setcolor(clr2);
    }
    numar=-nrUnit;
    for(int i=b-350+unitPx; i<=b-50; i=i+unitPx)
    {
        line(50,i,a-50,i);
        setcolor(clr1);
        nrToChar(numar,nrChar);
        outtextxy(25,i-5,nrChar);
        numar=numar-nrUnit;
        setcolor(clr2);
    }
    numar=nrUnit;
    for(int i=b-350-unitPx; i>=50; i=i-unitPx)
    {
        line(50,i,a-50,i);
        setcolor(clr1);
        nrToChar(numar,nrChar);
        outtextxy(25,i-5,nrChar);
        numar=numar+nrUnit;
        setcolor(clr2);
    }
    setcolor(clr1);
    if(500+StgDrp-3>=50 && 500+StgDrp-3<=a-50)
        outtextxy(500+StgDrp-3,30,"0");
    outtextxy(30,b-350-10,"0");
    if(500+StgDrp>=50 && 500+StgDrp<=a-50)
        line(500+StgDrp,50,500+StgDrp,b-50);
    line(50,b-350,a-50,b-350);
    ///Marginile
    line(50,50,a-50,50);
    line(50,50,50,b-50);
    line(a-50,50,a-50,b-50);
    line(50,b-50,a-50,b-50);
    ///Coordonate
    outtextxy(660,b-36,"Coordonates:");
    outtextxy(755,b-36,"x");
    outtextxy(860,b-36,"y");
    rectangle(770,b-42,845,b-20);
    rectangle(875,b-42,950,b-20);
    ///Interval
    outtextxy(450,b-36,"Interval:");
    outtextxy(510,b-36,"a");
    outtextxy(580,b-36,"b");
    rectangle(525,b-42,575,b-20);
    rectangle(595,b-42,645,b-20);
    char nrChr[100];
    nrToChar(i1,nrChr);
    outtextxy(530,b-38,nrChr);
    nrToChar(i2,nrChr);
    outtextxy(600,b-38,nrChr);
    outtextxy(60,13,"f(x)= ");
    outtextxy(86,13,input);
}

double derive( double x0)
{
    double delta = 1.0e-6;
    double x1 = x0 - delta;
    double x2 = x0 + delta;
    double y1 = fCoords(postfix,j,x1);
    double y2 = fCoords(postfix,j,x2);
    return (y2 - y1) / (x2 - x1);
}

double second_derivative( double x, double h)
{
    return (derive(x+h) - derive(x))/h;
}

void graph(int x,int y,char input[])
{
    if(int((i2-i1)/20)*5==0)
        nrUnit=1;
    else
        nrUnit=int((i2-i1)/20)*5;
    xoy(x,y);
    functionEvaluation(input,x,y);
    if(bt.rad==1)
    {
        for(int i=50; i<=950; i++)
            if(getpixel(i,351)==LIGHTMAGENTA)
            {
                setcolor(COLOR(150,152,213));
                setlinestyle(0,0,1);
                circle(i+1,351,5);
            }
    }
    if(bt.mm==1)
    {
        float ratia=100/unit;
        setcolor(COLOR(222,194,193));
        setlinestyle(0,0,2);
        line(50,(-1)*maxim*ratia+349,950,(-1)*maxim*ratia+349);
        line(50,(-1)*minim*ratia+351,950,(-1)*minim*ratia+351);
        setlinestyle(0,0,1);
    }
    if(bt.ip==1)
    {
        double step_size=1.0e-6,ud;
        bool verf=0;
        int ct=0;
        float ratia=100/unit;
        if(DarkLight==0)
            setcolor(WHITE);
        else
            setcolor(BLACK);
        if(Language==1)
            outtextxy(70,700-36,"Se incarca...");
        else
            outtextxy(70,700-36,"Loading...");
        for(double ix=i1; ix<=i2; ix=ix+0.0000005)
        {
            double f_sd = second_derivative(ix,step_size);
            if(f_sd > -0.000001 && f_sd < 0.000001 && f_sd!=0)
            {
                verf=1;
                int in1 = ix*10000;
                double iX = (double)in1/10000;
                int in2 = fCoords(postfix,j,ix)*10000;
                double iY = (double)in2/10000;
                int coordx=iX*ratia+500+StgDrp;
                int coordy= -iY*ratia+350;
                setcolor(COLOR(177,199,180));
                circle(coordx,coordy,5);
                circle(coordx,coordy,7);
                if(fCoords(postfix,j,ix)>=fCoords(postfix,j,ix+0.00000001))
                    while(fCoords(postfix,j,ix)>fCoords(postfix,j,ix+0.00000001))
                        ix=ix+1;
                else if(fCoords(postfix,j,ix)<=fCoords(postfix,j,ix+0.00000001))
                    while(fCoords(postfix,j,ix)>fCoords(postfix,j,ix+0.00000001))
                        ix=ix+1;
            }
        }
        if(verf==0)
        {
            if(Language==1)
                outtextxy(70,700-36,"Nu exista puncte de inflexiune");
            else
                outtextxy(70,700-36,"No points of inflexion found");
        }
        else
            outtextxy(70,700-36,"                  ");
    }
    if(bt.as==1)
    {
        if(DarkLight==0)
            setcolor(WHITE);
        else
            setcolor(BLACK);
        //outtextxy(70,700-36,"Loading...");
        int ct_a = 0;
        bool h_found = 0, v_found = 0, s_found = 0;
        double f_x = 0;
        double step_size = 1.0e-6;
        float ratia=100/unit;
        cout << "Asimptote verticale: " << endl;
        for(double ix=i1; ix<=i2; ix+=0.00001)
        {
            f_x = fCoords(postfix,j,ix); //ct_a++;
            //if(ct_a%10 == 0) cout << f_x << " ";
            if(f_x == INFINITY || f_x == -INFINITY || isinf(fCoords(postfix,j,ix)) || f_x > 9000 || f_x < -9000)
            {
                if(v_found == 0)
                    v_found = 1;
                cout << ix << endl;
                //desenare asimptota
                setlinestyle(0,0,2);
                setcolor(YELLOW);
                line(ix*ratia+500+StgDrp,50,ix*ratia+500+StgDrp,650);
                setlinestyle(0,0,1);
            }
        }

        //Asimptote orizontale
        cout << "Asimptota orizontala la y = ";
        double horizontal_asymptote = fCoords(postfix,j,1e6);
        for(int i = 1; i < 1e6; i *= 10)
        {
            double y = fCoords(postfix,j,i);
            if(fabs(y - horizontal_asymptote) < 1e-6)
            {
                horizontal_asymptote = y;
                h_found = 1;
                break;
            }
        }
        if(h_found == 1)
        {
            setlinestyle(0,0,2);
            setcolor(YELLOW);
            line(50,(-1)*horizontal_asymptote*ratia+351,950,(-1)*horizontal_asymptote*ratia+351);
            setlinestyle(0,0,1);
        }

        //Asimptote oblice
        double m = (fCoords(postfix,j,1e6) - fCoords(postfix,j,-1e6)) / (1e6 - (-1e6));
        double n = fCoords(postfix,j,-1e6) - m * (-1e6);

        nrToChar(m,NR);
        strcpy(postfixAO[0],NR);
        postfixAO[1][0] = 'x';
        postfixAO[2][0] = '*';
        nrToChar(n,NR);
        strcpy(postfixAO[3],NR);
        postfixAO[4][0] = '+';

        if(m < 0.01)
        {
            s_found = 0;
        }
        else
        {
            s_found = 1;
            setlinestyle(0,0,1);
            setcolor(YELLOW);

            double ex=-1,ey=-1,x,y,nr1,nr2,ratia=100/unit,r;
            x = i1;
            do
            {
                r=fCoords(postfixAO,4,x);
                y=-r*ratia+350;
                if(ex!=-1 && ey!=-1)
                {
                    if(coordVerf(ex,ey)==1)
                    {
                        setlinestyle(0,0,3);
                        if(coordVerf(x*ratia+500+StgDrp,y)==1)
                        {
                            line(ex,ey,x*ratia+500+StgDrp,y);
                        }
                        else
                        {
                            if(y<50)
                                line(ex,ey,ex,50);
                            if(y>650)
                                line(ex,ey,ex,650);
                        }
                    }
                    else
                    {
                        if(coordVerf(x*ratia+500+StgDrp,y)==1)
                        {
                            setlinestyle(0,0,3);
                            if(ey<50)
                                line(x*ratia+500+StgDrp,y,x*ratia+500+StgDrp,50);
                            if(ey>650)
                                line(x*ratia+500+StgDrp,y,x*ratia+500+StgDrp,650);
                        }
                    }
                }
                ex=x*ratia+500+StgDrp;
                ey=y;
                x=x+0.01;
            }
            while(x<=i2);
            setlinestyle(0,0,1);
        }

        if(v_found == 0 && h_found == 0 && s_found == 0)
        {
            setcolor(BLACK);
            if(Language==1)
                outtextxy(70,700-36,"Nu exista asimptote");
            else
                outtextxy(70,700-36,"No asymptotes found");
        }
    }
    outtextxy(100,100,"");
}

void Menu();

void click(int a,int b, char input[])
{
    int mousex=0,mousey=0;
    char nrChar[100];
    float ratia,nr;
    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            continue;
        getmouseclick(WM_LBUTTONDOWN,mousex,mousey);
        int color=getpixel(mousex,mousey);
        ratia=100/unit;
        if(color==13)///Coordonate
        {
            if(DarkLight==0)
                setcolor(WHITE);
            if(DarkLight==1)
                setcolor(BLACK);
            outtextxy(780,b-38,"                ");
            outtextxy(885,b-38,"                ");
            nr=(mousex-500-StgDrp)/ratia;
            nrToChar(nr,nrChar);
            outtextxy(780,b-38,nrChar);
            nr=-(mousey-350)/ratia;
            nrToChar(nr,nrChar);
            outtextxy(885,b-38,nrChar);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=52&&mousey<=90))///Zoom in
        {
            cleardevice();
            unit=unit-(i2-i1)/50;
            ratia=100/unit;
            StgDrp=((i2-i1)/2+i1)/unit*(-100);
            i1=(50-500-StgDrp)/ratia;
            i2=(950-500-StgDrp)/ratia;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=96&&mousey<=132))///Zoom out
        {
            cleardevice();
            unit=unit+(i2-i1)/50;
            ratia=100/unit;
            StgDrp=((i2-i1)/2+i1)/unit*(-100);
            i1=(50-500-StgDrp)/ratia;
            i2=(950-500-StgDrp)/ratia;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=229&&mousey<=262))///Radacina
        {
            cleardevice();
            if(bt.rad==0)
                bt.rad=1;
            else bt.rad= 0;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=140&&mousey<=177))///Dreapta
        {
            StgDrp=StgDrp-150;
            i1=(50-500-StgDrp)/ratia;
            i2=(950-500-StgDrp)/ratia;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=184&&mousey<=220))///Stanga
        {
            StgDrp=StgDrp+150;
            i1=(50-500-StgDrp)/ratia;
            i2=(950-500-StgDrp)/ratia;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=269&&mousey<=305))///MinMax
        {
            cleardevice();
            if(bt.mm==0)
                bt.mm=1;
            else bt.mm= 0;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=313&&mousey<=345))///P inflex
        {
            cleardevice();
            if(bt.ip==0)
                bt.ip=1;
            else bt.ip= 0;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=353&&mousey<=385)) ///Asimptote
        {
            cleardevice();
            if(bt.as==0)
                bt.as=1;
            else bt.as= 0;
            graph(1000,700,input);
        }
        if((mousex>=956&&mousex<=995)&&(mousey>=0&&mousey<=40)) ///Meniu
        {
            closegraph(CURRENT_WINDOW);
            Menu();
        }
    }
}

void mainGraph()
{
    int x = 1000, y = 700;
    unit=(i2-i1)/9;
    StgDrp=((i2-i1)/2+i1)/unit*(-100);
    initwindow(x,y,"Graf");
    postF(input,postfix,j);
    graph(x,y,input);
    click(x,y,input);
}

void FunctionButton()
{
    int menuWindow = getcurrentwindow();
    initwindow(800,448,"NewFunction");
    int newwindow = getcurrentwindow();
    setcurrentwindow(newwindow);

    if(isdigit(input[0]) || isalpha(input[0]) || input[0] == '-')
    {
        for(int i=0; i<=200; ++i)
            input[i] = 0;
        for(int i=0; i<=30; ++i)
            input1[i] = 0;
        for(int i=0; i<=30; ++i)
            input2[i] = 0;
        for(int i=0; i<=30; ++i)
            input3[i] = 0;

        for(int i=0; i<=30; ++i)
            strA[i] = 0;
        for(int i=0; i<=30; ++i)
            strB[i] = 0;
    }
    cleardevice();
    redraw();

    POINT mouse;
    GetCursorPos(&mouse);

    setcolor(LIGHTGRAY);
    settextstyle(0,HORIZ_DIR,2);
    if(Language == 0) outtextxy(40,150,(char*)"Write here...");
    else outtextxy(40,150,(char*)"Scrie aici...");

    while(1)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            continue;
        GetCursorPos(&mouse);
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>180 && mouse.x<650) && (mouse.y>190 && mouse.y<400))
            {
                redraw();
                setcolor(WHITE);
                outtextxy(37,153,(char*)"|");

                char ch = getch();
                if(strchr("+-/*^.",ch) || isdigit(ch) || (ch>='a' && ch<='z') ||  ch == '(' || ch == ')')
                    input[m++] = ch;

                //afisare de control
                fout << m << "\n";
                for(int i=0; i<m; ++i)
                    fout << input[i];
                fout << "\n";

                settextstyle(0,HORIZ_DIR,2);
                outtextxy(37,155,(char*)input);

                bool prima = 0;
                while(1)
                {
                    ch = getch();
                    if(ch != KEY_RIGHT)
                    {
                        if(ch=='=')
                        {
                            int errorV;
                            errorV=functionCheck(input);
                            if(errorV!=0)
                            {
                                oldwindow=CURRENT_WINDOW;
                                initwindow(300,150,"Error");
                                setbkcolor(WHITE);
                                setcolor(BLACK);
                                readimagefile("images/erBox.jpg",0,0,300,150);
                                switch(errorV)
                                {
                                case 1:
                                {
                                    if(Language==1)
                                        outtextxy(17,75,"Eroare de sintaxa!");
                                    else
                                        outtextxy(17,75,"Sintax error!");
                                    break;
                                }
                                case 2:
                                {
                                    if(Language==1)
                                        outtextxy(17,75,"Eroare de sintaxa! Vezi legenda.");
                                    else
                                        outtextxy(17,75,"Sintax error! Check legend.");
                                    break;
                                }
                                case 3:
                                {
                                    if(Language==1)
                                        outtextxy(17,75,"Atentie! Paranteze ramase deschise.");
                                    else
                                        outtextxy(17,75,"Error! Paranthesis left open.");
                                    break;
                                }
                                }
                                int mx,my;
                                while(true)
                                {
                                    while(!ismouseclick(WM_LBUTTONDOWN))
                                        continue;
                                    getmouseclick(WM_LBUTTONDOWN,mx,my);
                                    if((mx>=235&&mx<=288)&&(my>=8&&my<=60))
                                    {
                                        closegraph(CURRENT_WINDOW);
                                        setcurrentwindow(newwindow);
                                        break;
                                    }
                                }
                            }
                        }

                        if(strchr("+-/*^.",ch) || isdigit(ch) || (ch>='a' && ch<='z') ||  ch == '(' || ch == ')')
                        {
                            if(prima == 0)
                            {
                                redraw();
                                prima = 1;
                            }
                            //adaugare in input
                            input[m++] = ch;

                            if(strlen(input)>30*3)
                            {
                                //elimin ultimului caracter din input
                                input[m] = input[m+1];
                                input[m-1] = input[m+1];
                                m--;
                            }

                            //setcolor(WHITE);
                            for(int i=0; i<30; ++i)
                                input1[i] = input[i];
                            for(int i=30; i<30*2; ++i)
                                input2[i%30] = input[i];
                            for(int i=30*2; i<30*3; ++i)
                                input3[i%30] = input[i];

                            redraw();

                            //afisare de control
                            fout << m << "\n";
                            for(int i=0; i<m; ++i)
                                fout << input[i];
                            fout << "\n";

                        }
                        else if(ch == 127 || ch == 8)
                        {
                            //stergem ultimul caracter din input
                            if(m == 0) redraw();
                            if(functionsGraphed == 0)
                            {
                                input[m] = input[m+1];
                                input[m-1] = input[m+1];
                                m--;
                            }
                            else
                            {
                                input_1[m] = input_1[m+1];
                                input_1[m-1] = input_1[m+1];
                                m--;
                            }

                            //reactualizare input-uri
                            for(int i=0; i<30; ++i)
                                input1[i] = input[i];
                            for(int i=30; i<30*2; ++i)
                                input2[i%30] = input[i];
                            for(int i=30*2; i<30*3; ++i)
                                input3[i%30] = input[i];

                            cleardevice();
                            redraw();
                            //afisare de control
                            fout << m << "\n";
                            for(int i=0; i<strlen(input); ++i)
                                fout << input[i];
                            fout << "\n";
                        }
                        else continue;
                    }
                    else
                    {
                        int errorV;
                        input[strlen(input)] = 0;
                        settextstyle(0,HORIZ_DIR,2);
                        outtextxy(40,240,(char*)"a = ");
                        if(Language == 0) outtextxy(100,240,(char*)"? type here");
                        else outtextxy(100,240,(char*)"? tasteaza aici");

                        POINT mouse;
                        GetCursorPos(&mouse);

                        int mouseX = 0, mouseY = 0;

                        while(1)
                        {
                            while(!ismouseclick(WM_LBUTTONDOWN))
                                continue;
                            getmouseclick(WM_LBUTTONDOWN,mouseX,mouseY);

                            if((mouseX>100 && mouseX<255) && (mouseY>240 && mouseY<285))
                            {
                                redraw();
                                settextstyle(0,HORIZ_DIR,2);
                                outtextxy(40,240,(char*)"a = |");
                                while(1)
                                {
                                    ch = getch();
                                    if(ch != KEY_RIGHT)
                                    {
                                        if(isdigit(ch) || ch == '.' || (sizeA == 0 && ch == '-'))
                                        {
                                            strA[sizeA++] = ch;
                                            outtextxy(100,240,(char*)strA);
                                        }
                                        else if(ch == 127 || ch == 8)
                                        {
                                            if(m == 0)
                                            {
                                                redraw();
                                                settextstyle(0,HORIZ_DIR,2);
                                                outtextxy(40,240,(char*)"a = |");
                                            }

                                            strA[sizeA] = strA[sizeA+1];
                                            strA[sizeA-1] = strA[sizeA+1];
                                            sizeA--;
                                            redraw();
                                            settextstyle(0,HORIZ_DIR,2);
                                            outtextxy(40,240,(char*)"a = ");
                                            outtextxy(100,240,(char*)strA);
                                        }
                                    }
                                    else
                                    {
                                        strA[strlen(strA)] = 0;
                                        if(strcmp(strA,"") == 0)
                                        {
                                            if(Language == 0) outtextxy(100,240,(char*)"-10.0 (standard value)");
                                            else outtextxy(100,240,(char*)"-10.0 (valoare standard)");
                                            strcat(strA,"-10.0");
                                            i1 = -10.0;
                                        }
                                        else i1 = atof(strA);
                                        break;
                                    }
                                }
                            }
                            settextstyle(0,HORIZ_DIR,2);
                            outtextxy(40,240,(char*)"a = ");
                            outtextxy(100,240,(char*)strA);

                            outtextxy(40,285,(char*)"b = ");
                            if(Language == 0) outtextxy(100,285,(char*)"? type here");
                            else outtextxy(100,285,(char*)"? tasteaza aici");
                            if((mouseX>100 && mouseX<255) && (mouseY>285 && mouseY<310))
                            {
                                redraw();
                                settextstyle(0,HORIZ_DIR,2);
                                outtextxy(40,240,(char*)"a = ");
                                outtextxy(100,240,(char*)strA);
                                if(strA == "")
                                {
                                    if(strcmp(strA,"") == 0)
                                    {
                                        if(Language == 0) outtextxy(100,240,(char*)"-10.0 (standard value)");
                                        else outtextxy(100,240,(char*)"-10.0 (valoare standard)");
                                        strcat(strA,"-10.0");
                                        i1 = -10.0;
                                    }
                                    else i1 = atof(strA);
                                }

                                settextstyle(0,HORIZ_DIR,2);
                                outtextxy(40,285,(char*)"b = |");
                                while(1)
                                {
                                    ch = getch();
                                    if(ch != KEY_RIGHT)
                                    {
                                        if(isdigit(ch) || ch == '.' || (sizeB == 0 && ch == '-'))
                                        {
                                            strB[sizeB++] = ch;
                                            outtextxy(100,285,(char*)strB);
                                        }
                                        else if(ch == 127 || ch == 8)
                                        {
                                            if(m == 0)
                                            {
                                                redraw();
                                                //redraw tot ce e la a
                                                settextstyle(0,HORIZ_DIR,2);
                                                outtextxy(40,240,(char*)"a = ");
                                                outtextxy(100,240,(char*)strA);
                                                //redraw la b
                                                settextstyle(0,HORIZ_DIR,2);
                                                outtextxy(40,285,(char*)"b = |");
                                            }

                                            strB[sizeB] = strB[sizeB+1];
                                            strB[sizeB-1] = strB[sizeB+1];
                                            sizeB--;
                                            redraw();
                                            //redraw tot ce e la a
                                            settextstyle(0,HORIZ_DIR,2);
                                            outtextxy(40,240,(char*)"a = ");
                                            outtextxy(100,240,(char*)strA);
                                            //redraw la b
                                            settextstyle(0,HORIZ_DIR,2);
                                            outtextxy(40,285,(char*)"b = ");
                                            outtextxy(100,285,(char*)strB);
                                        }
                                    }
                                    else
                                    {
                                        strB[strlen(strB)] = 0;
                                        if(strcmp(strA,"") == 0)
                                        {
                                            if(Language == 0) outtextxy(100,240,(char*)"-10.0 (standard value)");
                                            else outtextxy(100,240,(char*)"-10.0 (valoare standard)");
                                            if(strcmp(strB,"") != 0) delay(1000);
                                            strcat(strA,"-10.0");
                                            i1 = -10.0;
                                        }

                                        if(strcmp(strB,"") == 0)
                                        {
                                            if(Language == 0) outtextxy(100,285,(char*)"10.0 (standard value)");
                                            else outtextxy(100,285,(char*)"10.0 (valoare standard)");
                                            if(strcmp(strA,"") != 0) delay(1000);
                                            strcat(strB,"10.0");
                                            i2 = 10.0;
                                        }
                                        i2 = atof(strB);
                                        break;
                                    }
                                }

                                if(strcmp(strB,"") == 0)
                                {
                                    if(Language == 0) outtextxy(100,285,(char*)"10.0 (standard value)");
                                    else outtextxy(100,285,(char*)"10.0 (valoare standard)");
                                    if(strcmp(strA,"") != 0) delay(1000);
                                    strcat(strB,"10.0");
                                    i2 = 10.0;
                                }
                                else i2 = atof(strB);

                                if(i1 >= i2)
                                {
                                    outtextxy(40,320,"Incorrect interval! Tip: a<b");
                                    delay(2000);
                                    incorrect = 1;
                                }
                                if(incorrect == 0)
                                {
                                    int oldwindow = getcurrentwindow();
                                    closegraph();
                                    functionsGraphed++;
                                    mainGraph();
                                    closegraph(window_Graph);
                                    if(functionsGraphed > 0)
                                    {
                                        int oldwindow = getcurrentwindow();
                                        FunctionButton();
                                        closegraph(oldwindow);
                                    }
                                    functionWindow = getcurrentwindow();
                                    closegraph(functionWindow);
                                    return;
                                }
                            }

                        }
                        return;
                    }
                }
            }
        }
    }
    getch();
    closegraph();
}

void Settings()
{
    if(settingsChange == 0)
    {
        initwindow(800,600,"Settings");
    }

    //cleardevice();

    if(DarkLight == 0)
    {
        setbkcolor(BLACK);
        cleardevice();
        if(Language == 0) //engleza dark
        {
            readimagefile("images/window_settings_DARK.jpg",0,0,800,600);

        }
        else //romana dark
        {
            readimagefile("images/fereastra_setari_DARK.jpg",0,0,800,600);

        }
    }
    else
    {
        setbkcolor(WHITE);
        cleardevice();
        if(Language == 0) //engleza light
        {
            readimagefile("images/window_settings_LIGHT.jpg",0,0,800,600);
        }
        else //romana light
        {
            readimagefile("images/fereastra_setari_LIGHT.jpg",0,0,800,600);
        }

    }

    POINT mouse;
    GetCursorPos(&mouse);

    while(1)
    {
        GetCursorPos(&mouse);

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>370 && mouse.x<440) && (mouse.y>190 && mouse.y<250))
            {
                DarkLight = 1 - DarkLight;
                settingsChange = 1;
                Settings();
            }
            if((mouse.x>370 && mouse.x<440) && (mouse.y>345 && mouse.y<395))
            {
                Language = 1 - Language;
                settingsChange = 1;
                Settings();
            }
            if((mouse.x>60 && mouse.x<115) && (mouse.y>490 && mouse.y<560))
            {
                closegraph(CURRENT_WINDOW);
                return;
            }
        }
    }
}

void Help()
{
    initwindow(800,600,"Help");
    if(Language == 0)
    {
        readimagefile("images/windowHelpEng.jpg",0,0,800,600);
    }
    else readimagefile("images/windowHelpRO.jpeg",0,0,800,600);

    POINT mouse;
    GetCursorPos(&mouse);

    while(1)
    {
        GetCursorPos(&mouse);

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>750 && mouse.x<800) && (mouse.y>0 && mouse.y<50))
            {
                closegraph(CURRENT_WINDOW);
                return;
            }
        }
    }
    getch();
    closegraph();
}

void Exit()
{
    exit(0);
}

void Menu()
{
    initwindow(800,600,"App Menu");
    POINT mouse;
    GetCursorPos(&mouse);
    readimagefile("images/menu_v1.jpg",0,0,800,600);
    if(Language == 1)
    {
        readimagefile("images/menu_v1RO.jpg",0,0,800,600);
    }
    while(1)
    {
        GetCursorPos(&mouse);

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>300 && mouse.x<500) && (mouse.y>200 && mouse.y<250))
            {
                FunctionButton();
                for(int i=0; i<strlen(input); ++i)
                    fout << input[i];
            }
        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>300 && mouse.x<500) && (mouse.y>440 && mouse.y<490))
            {
                Exit();
            }
        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>300 && mouse.x<500) && (mouse.y>360 && mouse.y<410))
            {
                Help();
                Menu();
            }
        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if((mouse.x>300 && mouse.x<500) && (mouse.y>280 && mouse.y<330))
            {
                Settings();
                Menu();
            }
        }
    }

    getch();
    closegraph();
}

int main()
{
    DarkLight = 1;
    Language = 0;
    Menu();
    return 0;
}
