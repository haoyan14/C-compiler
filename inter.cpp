#include "inter.h"
void init_inter_code()
{
	codes.clear();
}
vector<Intercode*> codes;
//add,sub,divi,mul,
void generate_Code(enum InterCodeKind interKind,enum OperandKind operKind1,string op1name,enum OperandKind operKind2,string op2name,enum OperandKind operKind3,string op3name)
{
	Intercode *code = new Intercode();
	code->type=interKind;
	code->op1=new Operand();
	code->op1->kind=operKind1;
	code->op1->name=op1name;
	code->op2=new Operand();
	code->op2->kind=operKind2;
	code->op2->name=op2name;
	code->op3=new Operand();
	code->op3->kind=operKind3;
	code->op3->name=op3name;
	codes.push_back(code);
}
//branch
void generate_Code_b(enum InterCodeKind interKind,enum OperandKind operKind1,string op1name,enum OperandKind operKind2,int val2)
{
	Intercode *code = new Intercode();
	code->type=interKind;
	code->op1=new Operand();
	code->op1->kind=operKind1;
	code->op1->name=op1name;
	code->op2=new Operand();
	code->op2->kind=operKind2;
	code->op2->ivalue=val2;
	codes.push_back(code);
}
//jump
void generate_Code_j(enum InterCodeKind interKind,enum OperandKind operKind,int val){
	Intercode *code = new Intercode();
	code->type=interKind;
	code->op1=new Operand();
	code->op1->kind=operKind;
	code->op1->ivalue=val;
	codes.push_back(code);
}
void printinter(){
	int cnt=0;
	for(auto a:codes){
		switch (a->type)
		{
		//mlt,slt,bne,beq,slte,mlte
		case add:printf("%d: %s = %s + %s\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case sub:printf("%d: %s = %s - %s\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case mul:printf("%d: %s = %s * %s\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case divi:printf("%d: %s = %s / %s\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case assign:printf("%d: %s = %s\n",cnt,a->op1->name.c_str(),a->op2->name.c_str());break;
		case branch:printf("%d: if %s goto %d\n",cnt,a->op1->name.c_str(),a->op2->ivalue);break;
		case goto_:printf("%d:goto %d\n",cnt,a->op1->ivalue);break;
		case and_:printf("%d: %s = (%s & %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case or_:printf("%d: %s = (%s or %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case mlt:printf("%d: %s = (%s > %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case slt:printf("%d: %s = (%s < %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case bne:printf("%d: %s = (%s != %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case beq:printf("%d: %s = (%s == %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case slte:printf("%d: %s = (%s <= %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		case mlte:printf("%d: %s = (%s >= %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		default:
			break;
		}
		cnt++;
	}
}
int getsize(){return codes.size();};
void setivalue(int no,int ivalue){codes[no]->op1->ivalue=ivalue;};
