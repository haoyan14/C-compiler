#ifndef INTER_H
#define INTER_H
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

enum OperandKind {opsymbol,none,addr};
struct Operand
{ 
	enum OperandKind kind; 
	int ivalue;//addr 
    string name;//var name
    int scope;
}; 
enum InterCodeKind{add,sub,divi,mul,goto_,branch,assign,mlt,slt,bne,beq,slte,mlte,and_,or_};
struct Intercode{
    enum InterCodeKind type;
    Operand *op1,*op2,*op3;

};
extern vector<Intercode*> codes;
void init_inter_code(); 

void generate_Code(enum InterCodeKind interKind,enum OperandKind operKind1,string op1name,enum OperandKind operKind2,string op2name,enum OperandKind operKind3,string op3name);
void generate_Code_b(enum InterCodeKind interKind,enum OperandKind operKind1,string op1name,enum OperandKind operKind2,int val2);
void generate_Code_j(enum InterCodeKind interKind,enum OperandKind operKind,int val);
int getsize();
void printinter();
void setivalue(int no,int ivalue);
#endif

