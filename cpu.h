#ifndef CPU_H__
#define CPU_H__

#include <iostream>
#include <fstream>

using namespace std;


int gtuAtoi(char *str);
bool isNumber(char isNum);
int findEndIndex(char *str);
bool isEndOfLine(char isEnd);
void printAllReg(int registerArray[]);
int findConstantIndex(char *str, int index);
int findEndOfConstIndex(char *str, int index);
int findRegisterNumber(char *line, int startIndex);
int gtuStrNCmp(char *str, char *srchStr, int index);
bool check(char *str, int startIndex, int endIndex);
int jmpInstruction(char *line, int registerArray[]);
int addInstruction(char *line, int registerArray[]);
int subInstruction(char *line, int registerArray[]);
int movInstruction(char *line, int registerArray[]);
int prnInstruction(char *line, int registerArray[]);
void readFile(int numOfReadLine, ifstream &inpStream, char *line);
int organizCpu(char *line, int registerArray[], ifstream &inpStream, int option);



#endif
