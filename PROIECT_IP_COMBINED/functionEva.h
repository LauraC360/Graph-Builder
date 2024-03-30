#ifndef function_Evaluation_h
#define function_Evaluation_h
int priority(char op);
int codingFunction(char input[], int& i);
void unitDesign(char unitPoz[100][100],char unitNeg[100][100],int a, int b, int unit);
void nrToChar(double nr, char nrChar[100]);
double specificFunction(double a, char sF);
double applyOp(double a, double b, char op);
bool coordVerf(int x, int y);
int lenghtLine(int x1, int y1, int x2, int y2);
int functionCheck(char input[]);
void postF(char input[],char postfix[][10], int &j);
double fCoords(char postfix[][10],int j, double x);
#endif // function_Evaluation_h
