#include <iostream>

#include "lexical_analyzer.h"
#include "grammer_analyzer.h"
#include "semantic_analyzer.h"
#include "dstcode.h"
#include "inter.h"
#include <vector>
#include <string> 
#include <fstream> 
using namespace std;
void printtable(vector<symbol*> aa){
	for(auto &a:aa){
		cout<<"name: "<<a->name<<"  off:"<<a->offset<<"  regnum:"<<a->regnum<<" scope: "<<a->scope<<" type: "<<a->type<<endl;
	}
}
int main(){
	lexical_analyzer la;
	la.lexical_analyzer_do("in.txt");
	grammer_analyzer ga("grammer.txt");
	// ga.printpro();
	ga.getfirst();
	ga.getfollow();
	ga.gettable();
	ga.analyse("lexical.txt",la);
//	ga.printtree();
	init_inter_code();
	semantic_analyzer sa(ga.getroot());
	sa.createtable(sa.getroot(),0);
	printinter();
	initdstcode(sa.gettable());
	getdstCode();
	printdst();
//	printtable(sa.gettable());
	return 0;
}
