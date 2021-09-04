#include "lexical_analyzer.h"
void lexical_analyzer::lexical_analyzer_do(string path){
    instream = fopen(path.c_str(), "r");
    char ch;
    //cout<<"记号序列"<<endl;
	state=0;
	do{
	switch(state){
		case 0:
			nowstring="";
			ch = fgetc(instream);
			if(ch == ' ' || ch == '\n' || ch == '\t'){
				while(ch == ' ' || ch == '\n' || ch == '\t'){
					if(ch=='\n')linesum++;
					ch=fgetc(instream);
				}
			}
			if(ch=='0')state=19;
			else if(isdigit(ch))state=2;
			else if(isletter(ch)||ch=='_')state=1;
			else switch(ch){
				case '<':state=8;break;
				case '>':state=9;break;
				case '=':state=10;break;
				case '+':state=11;break;
				case '-':state=12;break;
				case '*':state=0;out<<"(33,-,"<<linesum<<")";s.insert(33);sum++;break;
				case '/':state=13;break;
				case '(':state=0;out<<"(24,-,"<<linesum<<")";s.insert(24);sum++;break;
				case ')':state=0;out<<"(25,-,"<<linesum<<")";s.insert(25);sum++;break;
				case '!':state=16;break;
				case '[':state=0;out<<"(26,-,"<<linesum<<")";s.insert(26);sum++;break;
				case ']':state=0;out<<"(27,-,"<<linesum<<")";s.insert(27);sum++;break;
				case '{':state=0;out<<"(36,-,"<<linesum<<")";s.insert(36);sum++;break;
				case '}':state=0;out<<"(37,-,"<<linesum<<")";s.insert(37);sum++;break;
				case '&':state=0;out<<"(45,-,"<<linesum<<")";s.insert(45);sum++;break;
				case '|':state=0;out<<"(23,-,"<<linesum<<")";s.insert(23);sum++;break;
				case '.':state=22;break;
				case '"':state=17;break;
				case '\'':state=23;break;
				case '#':state=0;out<<"(39,-,"<<linesum<<")";s.insert(39);sum++;break;
				case ';':state=0;out<<"(32,-,"<<linesum<<")";s.insert(32);sum++;break; 
				case ',':state=0;out<<"(52,-,"<<linesum<<")";s.insert(52);sum++;break; 
			}
			break;
		case 1://标识符 or 关键字 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isletter(ch)||isdigit(ch)||ch=='_')state=1;
			else{
				fseek(instream, -1, SEEK_CUR);
				state=0;
				int key=k.get(nowstring);
				if(key!=-1){// keyword
					printkey(key,linesum);
					s.insert(key);
					sum++;
				}
				else if(nowstring=="true"||nowstring=="false"){
					ct.insert(nowstring);
					printconst(ct.get(nowstring),linesum);
					s.insert(46);
					sum++;
				}
				else{//identifier 
					i.insert(nowstring);
					printidentifier(i.get(nowstring),linesum);
					s.insert(21);
					sum++;
				}
			}
			break;
		case 2://数值常数 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch)){
				state=2;
			}
			else if(isletter(ch)&&ch!='E'){
				error(&ch,linesum);
				state=0;
			}
			else switch(ch){
				case '.':state=3;break;
				case 'E':state=5;break;
				default:
				fseek(instream, -1, SEEK_CUR);
				state=0;
				ct.insert(nowstring);
				printconst(ct.get(nowstring),linesum);
				s.insert(46);
				sum++;
				break;
			}
			break;
		case 3://小数点 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch))state=4;
			else {
				error(&ch,linesum);
				state=0;
			}
			break; 
		case 4://小数
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch))state=4;
			else switch(ch){
				case 'E':state=5;break;
				default:
				fseek(instream, -1, SEEK_CUR);
				state=0;
				ct.insert(nowstring);
				printconst(ct.get(nowstring),linesum);
				s.insert(46);
				sum++;
				break;
			}
			break; 
		case 5://指数状态 :读到E 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch))state=7; 
			else switch(ch){
				case '+':state=6;break;
				case '-':state=6;break;
				default:
				error(&ch,linesum);
				state=0;
				break;
			}
			break;
		case 6://指数状态：E后面跟正负号
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch))state=7; 
			else {
				error(&ch,linesum);
				state=0;
			}
			break;
		case 7://指数
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch))state=7; 
			else {
				fseek(instream, -1, SEEK_CUR);
				state=0;
				ct.insert(nowstring);
				printconst(ct.get(nowstring),linesum);
				s.insert(46);
				sum++;
			}
			break;
		case 8:// <状态 
			nowstring+=ch;
			ch=fgetc(instream);
			switch(ch){
				case '='://<=
					nowstring+=ch;
					state=0;
					printother(40,linesum);
					s.insert(40);
					sum++;
					break;
				case '>'://<>
					nowstring+=ch;
					state=0;
					printother(38,linesum);
					s.insert(38);
					sum++;
					break;
				default://<
					fseek(instream, -1, SEEK_CUR);
					state=0;
					printother(30,linesum);
					s.insert(30);
					sum++;
					break;
			}
			break;
		case 9:// >状态 
			nowstring+=ch;
			ch=fgetc(instream);
			switch(ch){
				case '='://>=
					nowstring+=ch;
					state=0;
					printother(42,linesum);
					s.insert(42);
					sum++;
					break;
				default://<
					fseek(instream, -1, SEEK_CUR);
					state=0;
					printother(41,linesum);
					s.insert(41);
					sum++;
					break;
			}
			break;
		case 10:// =状态
			nowstring+=ch;
			ch=fgetc(instream);
			switch(ch){
				case '='://==
					nowstring+=ch;
					state=0;
					printother(29,linesum);
					s.insert(29);
					sum++;
					break;
				default://=
					fseek(instream, -1, SEEK_CUR);
					state=0;
					printother(28,linesum);
					s.insert(28);
					sum++;
					break;
			}
			break;
		case 11:// +状态 
			nowstring+=ch;
			ch=fgetc(instream);
			switch(ch){
				case '='://+=
					nowstring+=ch;
					state=0;
					printother(48,linesum);
					s.insert(48);
					sum++;
					break;
				case '+'://++
					nowstring+=ch;
					state=0;
					printother(23,linesum);
					s.insert(23);
					sum++;
					break;
				default://+
					fseek(instream, -1, SEEK_CUR);
					state=0;
					printother(43,linesum);
					s.insert(43);
					sum++;
					break;
			}
			break;
		case 12:// -状态 
			nowstring+=ch;
			ch=fgetc(instream);
			switch(ch){
				case '='://-=
					nowstring+=ch;
					state=0;
					printother(49,linesum);
					s.insert(49);
					sum++;
					break;
				case '-'://--
					nowstring+=ch;
					state=0;
					printother(45,linesum);
					s.insert(45);
					sum++;
					break;
				default://-
					fseek(instream, -1, SEEK_CUR);
					state=0;
					printother(44,linesum);
					s.insert(44);
					sum++;
					break;
			}
			break;
		case 13:// /状态
			nowstring+=ch;
			ch=fgetc(instream);
			if(ch=='/')state=14;
			else if(ch=='*')state=15;
			else {
				fseek(instream, -1, SEEK_CUR);
				state=0;
				printother(34,linesum);
				s.insert(34);
				sum++;
			}
			break;
		case 14://  //状态 
		 	ch=fgetc(instream);
			while(ch!='\n')ch=fgetc(instream);
			if(ch=='\n'){
				linesum++;
				state=0;
			}
			break;
		case 15:// /*状态
			ch=fgetc(instream);
			while(ch!='*')
			{
				if(ch=='\n')linesum++;
				ch=fgetc(instream);			
			}
			ch=fgetc(instream);
			if(ch=='/')state=0;
			else {
				if(ch=='\n')linesum++;
				state=15;
			}
			break;
		case 16://!状态
			nowstring+=ch;
			ch=fgetc(instream);
			if(ch=='='){
				nowstring+=ch;
				state=0;
				printother(50,linesum);
				s.insert(50);
				sum++;
			}
			else {
				fseek(instream,-1,SEEK_CUR); 
				 state=0;
				 printother(31,linesum);
				 s.insert(31);
				 sum++;
			}
			break;
		case 17:// "状态
			nowstring+=ch;
			ch=fgetc(instream);
			while(ch!='"'){
				if(ch=='\n'){
					error(&ch,linesum);
					linesum++;
					state=0;
					break;
				}
				nowstring+=ch;
				ch=fgetc(instream);
			}
			if(ch=='"')state=18;
			break;
		case 18:// ""状态 
			nowstring+=ch;
			ct.insert(nowstring);
			printconst(ct.get(nowstring),linesum);
			s.insert(46);
			sum++;
			state=0;
			break;
		case 19:// 八进制或十六进制
			nowstring+=ch;
			ch=fgetc(instream);
			if(ch=='x'||ch=='X'){
				state=20;
			}
			else if (isdigit(ch)){
				if(ch>='0'&&ch<'8')
				state=21;
				else {
					error(&ch,linesum);
					state=0;
				}
			}
			else {
				if(isletter(ch)){
					error(&ch,linesum);
					state=0;
				}
				else{
					fseek(instream,-1,SEEK_CUR); 
					state=0;
					ct.insert(nowstring);
					printconst(ct.get(nowstring),linesum);
					s.insert(46);
					sum++;
				}
			} 
			break;
		case 20://十六进制 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch)||(ch>='a'&&ch<='f')){
				state=20;
			}
			else if(isletter(ch)){
				error(&ch,linesum);
				state=0;
			}
			else {
				fseek(instream,-1,SEEK_CUR); 
				state=0;
				ct.insert(nowstring);
				printconst(ct.get(nowstring),linesum);
				s.insert(46);
				sum++;
			}
			break;
		case 21://八进制 
			nowstring+=ch;
			ch=fgetc(instream);
			if(ch>='0'&&ch<='7'){
				state=21;
			}
			else if(isdigit(ch)||isletter(ch)){
				error(&ch,linesum);
				state=0;
			}
			else {
				fseek(instream,-1,SEEK_CUR); 
				state=0;
				ct.insert(nowstring);
				printconst(ct.get(nowstring),linesum);
				s.insert(46);
				sum++;
			}
			break;
		case 22://.开头的浮点数 
			nowstring+=ch;
			ch=fgetc(instream);
			if(isdigit(ch)){
				state=2;
				break;
			} 
			else{
				error(&ch,linesum);
				state=0;
			}
		case 23://字符常量
			nowstring+=ch;
			ch=fgetc(instream);
			if(ch=='\\'){
				while(ch!='\''){
					if(ch=='\n'){
						error(&ch,linesum);
						linesum++;
						state=0;
						break;
					}
					nowstring+=ch;
					ch=fgetc(instream);
				}
			}
			else {
				if(ch=='\n'){
					error(&ch,linesum);
					linesum++;
					state=0;
					break;
				}
				nowstring+=ch;
				ch=fgetc(instream);
			}
			if(ch=='\'')state=24;
			else {
				error(&ch,linesum);
				state=0;
				break;
			}
			break;
		case 24:
			nowstring+=ch;
			ct.insert(nowstring);
			printconst(ct.get(nowstring),linesum);
			s.insert(46);
			sum++;
			state=0;
			break;
		}
	}while(ch!=EOF);
	//cout<<endl<<"语句行数:"<<linesum<<endl<<"单词总数:"<<sum<<endl;
	/*s.printhelp();
	ct.printhelp();
	i.printhelp();*/
    fclose(instream);
    out.close();
	return ;
}
bool lexical_analyzer::isletter(char c){
	return ((c>='a'&&c<='z')||(c<='Z'&&c>='A'));
}
bool lexical_analyzer::isdigit(char c){
	return (c>='0'&&c<='9');
}
void lexical_analyzer::error(char* ch,int line){//读到错误字符后继续读入直到新字符开始 
	int flag=0;
	//cout<<endl<<"第"<<line+1<<"行出错！"<<endl;
	while(*ch != ' ' && *ch != '\n' && *ch != '\t'){
		if(*ch=='\n')linesum++;
		*ch=fgetc(instream);
		if(isletter(*ch)||isdigit(*ch)||*ch=='_'){
			flag=1;
		}
		else break;
	}
	if(flag)fseek(instream, -1, SEEK_CUR);//此时多读了一个字符，需要退回 
}
void lexical_analyzer::printkey(int key,int line){
	out<<"("<<key<<","<<"-"<<","<<line<<")";
	//cout<<"("<<key<<","<<"-"<<")";
}
void lexical_analyzer::printidentifier(int no,int line){
	out<<"("<<21<<","<<no<<","<<line<<")";
	//cout<<"("<<21<<","<<no<<")";
}
void lexical_analyzer::printconst(int no,int line){
	out<<"("<<46<<","<<no<<","<<line<<")";
	//cout<<"("<<46<<","<<no<<")";
}
void lexical_analyzer::printother(int no,int line){
	out<<"("<<no<<","<<"-"<<","<<line<<")";
	//cout<<"("<<no<<","<<"-"<<")";
}
string lexical_analyzer::words[54]={"0","int","bool","double","float","short","long","char","for","if","else","while","break","swtich","void"
		,"return","include","continue","do","get","put","id",".","|","(",")","[","]","=","==","<",":",";","*","/","%","{","}","<>"
		,"#","<=",">",">=","+",	"-","&","cons","\"","+=","-=","!=","_",",","\'"}; 
map<int,string> lexical_analyzer::wordtable;
