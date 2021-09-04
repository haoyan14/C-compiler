#include"dstcode.h"
void initdstcode(vector<symbol*> t){
    table=t;
    for(int i=0;i<regnums;i++){
        regs[i].var=NULL;
        regs[i].ivalue=INT_MAX;
    }
    regno=0;
    addcnt=0;
}
void getdstCode(){
    int op1,op2,res;
    int no=0;
    for(auto a:codes){
        // cout<<a->type<<"regno: "<<regno<<endl;
        intertodst[no]=dstcodes.size();
        if(baddr.find(no)!=baddr.end()){
            switch (dstcodes[baddr[no]-1]->type)
            {
            case bgtz_:
                    dstcodes[baddr[no]-1]->op2->ivalue=dstcodes.size();
                    break;
            case j_d:
                    dstcodes[baddr[no]-1]->op1->ivalue=dstcodes.size();
                    break;
            default:
                break;
            }
        }
		switch (a->type)
		{
		case add:
                if(strisdigit(a->op2->name)){
                    op2=getreg(a->op3);
                    res=getreg(a->op1);                    
                    generate_dstCode(addi_d,reg_,res,reg_,op2,cons_,atoi(a->op2->name.c_str()));
                }
                else if(strisdigit(a->op3->name)){
                    op1=getreg(a->op2);
                    res=getreg(a->op1);
                    generate_dstCode(addi_d,reg_,res,reg_,op1,cons_,atoi(a->op3->name.c_str()));
                }
                else{
                    op1=getreg(a->op2),op2=getreg(a->op3);
                    res=getreg(a->op1);
                    generate_dstCode(add_d,reg_,res,reg_,op1,reg_,op2);
                }
                break;
		case sub:
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(sub_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case mul:
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(mul_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case divi:
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(divi_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case assign:
                res=getreg(a->op1);
                if(strisdigit(a->op2->name)){//a = cons
                    generate_dstCode_cons(li_d,reg_,res,cons_,atoi(a->op2->name.c_str()));
                }
                else{
                    op1=getreg(a->op2);
                    generate_dstCode_2op(move_d,reg_,res,reg_,op1);
                }
                break;
	    case branch:
                //printf("%d: if %s goto %d\n",cnt,a->op1->name.c_str(),a->op2->ivalue);
                res=getreg(a->op1);
                generate_dstCode_2op(bgtz_,reg_,res,addr_,a->op2->ivalue);
                baddr[a->op2->ivalue]=dstcodes.size();
                break;
		case goto_:
                //printf("%d:goto %d\n",cnt,a->op1->ivalue);
                
                if(a->op1->ivalue<no){
                    generate_dstCode_1op(j_d,addr_,intertodst[a->op1->ivalue]);
                }
                else {
                    generate_dstCode_1op(j_d,addr_,0);
                    baddr[a->op1->ivalue]=dstcodes.size();
                }
                break;
		case and_:
                //printf("%d: %s = (%s & %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(and_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case or_:
                // printf("%d: %s = (%s or %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(or_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case mlt:
                // printf("%d: %s = (%s > %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(slt_d,reg_,res,reg_,op1,reg_,op2);
                break;
		case slt:
                // printf("%d: %s = (%s < %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(slt_d,reg_,res,reg_,op2,reg_,op1);
                break;
		case bne:
                // printf("%d: %s = (%s != %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(bne_d,reg_,op1,reg_,op2,addr_,dstcodes.size()+3);
                baddr[a->op1->ivalue]=dstcodes.size();
                generate_dstCode_cons(li_d,reg_,res,cons_,0);
                generate_dstCode_1op(j_d,addr_,dstcodes.size()+2);
                generate_dstCode_cons(li_d,reg_,res,cons_,1);
                addcnt+=4;
                break;
		case beq:
                // printf("%d: %s = (%s == %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());
                op1=getreg(a->op2),op2=getreg(a->op3);
                res=getreg(a->op1);
                generate_dstCode(beq_d,reg_,op1,reg_,op2,addr_,dstcodes.size()+3);
                generate_dstCode_cons(li_d,reg_,res,cons_,0);
                generate_dstCode_1op(j_d,addr_,dstcodes.size()+2);
                generate_dstCode_cons(li_d,reg_,res,cons_,1);
                addcnt+=4;
                break;
		// case slte:printf("%d: %s = (%s <= %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
		// case mlte:printf("%d: %s = (%s >= %s)\n",cnt,a->op1->name.c_str(),a->op2->name.c_str(),a->op3->name.c_str());break;
	    default:
			break;
		}

        no++;
    }
    if(baddr.find(no)!=baddr.end()){
        switch (dstcodes[baddr[no]-1]->type)
        {
        case bgtz_:
                dstcodes[baddr[no]-1]->op2->ivalue=dstcodes.size();
                break;
        case j_d:
                dstcodes[baddr[no]-1]->op1->ivalue=dstcodes.size();
                break;
        default:
            break;
        }
    }
}
bool strisdigit(string c){
    for(auto a:c){
        if(!isdigit(a))return false;
    }
    return true;
}
symbol* findsymbol(Operand* aa){
    for(auto &a:table){
        if(a->name==aa->name&&a->scope==aa->scope){
            return a;
        }
    }
    return NULL;
}
int getreg(Operand* a){
    symbol* res=findsymbol(a);
    if(res==NULL){
        int back;
        if(strisdigit(a->name)){
            int ivalue=atoi(a->name.c_str());
            for(int i=0;i<regnums;i++){
                if(regs[i].ivalue==ivalue){
                    return i;
                }
            }
            if(regs[regno].var==NULL){
                back=regno;
                regs[regno].ivalue=ivalue;
                regs[regno].var=NULL;
                generate_dstCode_2op(li_d,reg_,regno,cons_,ivalue);
                regno=(regno+1)%regnums;
                addcnt++;
                return back;
            }
            else {
                //store word back to main memory in var.offset
                back=regno;
                regs[regno].var->regnum=-1;
                generate_dstCode_2op(sw_d,reg_,regno,addr_,regs[regno].var->offset);
                regs[regno].ivalue=ivalue;
                regs[regno].var=NULL;
                generate_dstCode_2op(li_d,reg_,regno,cons_,ivalue);
                regno=(regno+1)%regnums;
                addcnt+=2;
                return back;
            }
        }
        
    }
    else if(res->regnum!=-1){
        return res->regnum;
    }
    else{
        int back;
        for(int i=0;i<regnums;i++){
            if(regs[regno].var==NULL){
                break;
            }
            else regno=(regno+1)%regnums;
        }
        if(regs[regno].var==NULL){
            back=regno;
            regs[regno].var=res;
            regs[regno].ivalue=INT_MAX;
            res->regnum=regno;
            generate_dstCode_2op(lw_d,reg_,regno,addr_,res->offset);
            regno=(regno+1)%regnums;
            addcnt++;
            return back;
        }
        else {
            //store word back to main memory in var.offset
            back=regno;
            regs[regno].var->regnum=-1;
            generate_dstCode_2op(sw_d,reg_,regno,addr_,regs[regno].var->offset);
            regs[regno].var=res;
            regs[regno].ivalue=INT_MAX;
            res->regnum=regno;
            generate_dstCode_2op(lw_d,reg_,regno,addr_,res->offset);
            regno=(regno+1)%regnums;
            addcnt+=2;
            return back;
        }
    }
}
void generate_dstCode_cons(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2){
    dstCode *code = new dstCode();
	code->type=interKind;
	code->op1=new dstOperand();
	code->op1->kind=operKind1;
	code->op1->ivalue=val1;
	code->op2=new dstOperand();
	code->op2->kind=operKind2;
	code->op2->ivalue=val2;
	dstcodes.push_back(code);
}
void generate_dstCode(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2,enum dstOperandKind operKind3,int val3){
    dstCode *code = new dstCode();
	code->type=interKind;
	code->op1=new dstOperand();
	code->op1->kind=operKind1;
	code->op1->ivalue=val1;
	code->op2=new dstOperand();
	code->op2->kind=operKind2;
	code->op2->ivalue=val2;
	code->op3=new dstOperand();
	code->op3->kind=operKind3;
	code->op3->ivalue=val3;
	dstcodes.push_back(code);
}
void generate_dstCode_2op(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1,enum dstOperandKind operKind2,int val2){
    dstCode *code = new dstCode();
	code->type=interKind;
	code->op1=new dstOperand();
	code->op1->kind=operKind1;
	code->op1->ivalue=val1;
	code->op2=new dstOperand();
	code->op2->kind=operKind2;
	code->op2->ivalue=val2;
	dstcodes.push_back(code);
}
void generate_dstCode_1op(enum dstCodeKind interKind,enum dstOperandKind operKind1,int val1){
    dstCode *code = new dstCode();
	code->type=interKind;
	code->op1=new dstOperand();
	code->op1->kind=operKind1;
	code->op1->ivalue=val1;
    dstcodes.push_back(code);
}
void printdst(){
	int cnt=0;
	for(auto a:dstcodes){
		switch (a->type)
		{
            case add_d:printf("%d :ADD  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case sub_d:printf("%d :SUB  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case addi_d:printf("%d :ADDI  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case mul_d:printf("%d :MUL  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case divi_d:printf("%d :DIV  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case move_d:printf("%d :move  %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue);break;
            case j_d:printf("%d :J  %d \n",cnt,a->op1->ivalue);break;
		    case bgtz_:printf("%d :BGTZ  %d , %d \n",cnt,a->op1->ivalue,a->op2->ivalue);break;
		    case and_d:printf("%d :AND  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case or_d:printf("%d :OR  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case slt_d:printf("%d :SLT  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case bne_d:printf("%d :BNE  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
		    case beq_d:printf("%d :BEQ  %d , %d , %d\n",cnt,a->op1->ivalue,a->op2->ivalue,a->op3->ivalue);break;
            case li_d:printf("%d :li  %d , %d \n",cnt,a->op1->ivalue,a->op2->ivalue);break;
            case lw_d:printf("%d :LW  %d , %d(0) \n",cnt,a->op1->ivalue,a->op2->ivalue);break;
            case sw_d:printf("%d :SW  %d , %d(0) \n",cnt,a->op1->ivalue,a->op2->ivalue);break;
		default:
			break;
		}
		cnt++;
	}
}
