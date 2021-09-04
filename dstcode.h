#ifndef DSTCODE_H
#define DSTCODE_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "inter.h"
#include "symbol.h"
using namespace std;
const int  regnums=10;
extern  vector<Intercode*> codes;
struct reg
{ 
    int ivalue;//const
    symbol* var;
}; 

enum dstOperandKind {reg_,addr_,cons_};
struct dstOperand
{ 
	enum dstOperandKind kind; 
	int ivalue;//reg no or  addr
}; 
enum dstCodeKind{add_d,addi_d,sub_d,divi_d,mul_d,j_d,bgtz_,move_d,li_d,slt_d,bne_d,beq_d,and_d,or_d,lw_d,sw_d};
struct dstCode{
    enum dstCodeKind type;
    dstOperand *op1,*op2,*op3;

};
static struct reg regs[regnums];
static vector<dstCode*> dstcodes;
static map<int,int> baddr;// int second int matched dstcode branch address to the first int inter no
static map<int,int> intertodst;//inter code address to dstcodeno
static int regno;//the current reg no that scanned
static int addcnt;
static vector<symbol*> table;
void initdstcode(vector<symbol*> t);

int getreg(Operand* a);//get a reg by inter operand a.name a.scope
symbol* findsymbol(Operand* a);//find symbol by inter operand a.name a.scope
void getdstCode();
void generate_dstCode(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2,enum dstOperandKind operKind3,int val3);
void generate_dstCode_1op(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1);
void generate_dstCode_2op(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2);
void generate_dstCode_cons(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2);
bool strisdigit(string c);
void printdst();

#endif


