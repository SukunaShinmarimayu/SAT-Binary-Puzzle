#include"head.h"
int WriteCNF(char filename[80],int n){     //将棋盘的初始条件的三个约束，变成cnf公式，写入文件 
	if(write(filename,n)!=OK)  return FALSE;
	if(rule_1(filename,n)!=OK) return FALSE;
	if(rule_2(filename,n)!=OK) return FALSE;
	if(rule_3(filename,n)!=OK) return FALSE;
	return OK;
}