#include "KeywordsTable.h"
void KeywordsTable::init(){
	for(int i=0;i<20;i++){
		m.insert(pair<string,int>(words[i],i+1));
		//m.insert(words[i],i+1);
	}
}
int KeywordsTable::get(string str){
	if(m.find(str)==m.end())return -1;
	return m[str];
}
string KeywordsTable::words[30]={"int","bool","double","float","short","long","char","for","if","else","while","break","swtich","void"
		,"return","include","continue","do","get","put"}; 
