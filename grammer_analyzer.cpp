#include "grammer_analyzer.h"
//文法产生式解析 

grammer_analyzer::grammer_analyzer(string path2){
	FILE *instream = fopen(path2.c_str(), "r");
	if(!instream){
		cout<<"Failed to open the file"<<endl;
		exit(1);
	}
	char ch;
	ch=fgetc(instream);
	vector<string> temp;
	string nowstr;
	string left;
	while(ch!=EOF){
		nowstr="";
		while(ch==' '||ch=='\t'){
			ch=fgetc(instream);
		}
		while(ch!=' '&&ch!='\t'&&ch!='\n'){
			//cout<<nowstr<<endl;
			nowstr+=ch;
			ch=fgetc(instream);
		}
		while(ch==' '||ch=='\t'){
			ch=fgetc(instream);
		}
		if(ch=='\n'){
			temp.push_back(nowstr);
			ch=fgetc(instream);
			pro[left].push_back(temp);
			temp.clear();
			nowstr="";
			left="";
			continue;
		}
		if(nowstr=="->"){
			left=temp.back();
			temp.clear();
			continue;
		}
		if(nowstr=="|"&&temp.size()==0){
			
		}
		else if(nowstr=="|"){
			pro[left].push_back(temp);
			temp.clear();
			continue;
		}
		temp.push_back(nowstr);
	}
	follow["program"].insert("$");
}
//打印产生式 
void grammer_analyzer::printpro(){
	cout<<"产生式集合:"<<endl;
	for(auto &aa : pro){
		cout<<aa.first<<" :";
		for(auto &b:aa.second){
			for(auto &i:b){
				cout<<i<<" ";
			}
			if(b!=aa.second.back())cout<<"|"<<" ";
		}
		cout<<endl; 
	}
	return;
}
//递归求非终结符集合 
set<string> grammer_analyzer::nterfirst(string left){
	if(pro.count(left)>0){
        vector<vector<string> > temp=pro[left];
        for(auto &a:temp){//   E T'  |  id F | e
            if(a.size()==1&&a[0]=="e")fir[left].insert("e");
            else{
                int flagall=0;
                for(vector<string>::iterator i = a.begin(); i !=  a.end(); i++){// E  T' 
					// if(left=="program")cout<<*i<<endl;
                    int flag=0;
                    if(isnter(*i)){
                        set<string> s1=nterfirst(*i);
                        for (set<string>::iterator ii = s1.begin(); ii !=  s1.end(); ii++) {
							if (*ii == "e") {//此时空串不可插入
								flag = 1;
							}
							else {
								fir[left].insert(*ii);
							}
                        }
                    }
                    else if(ister(*i)){
                        fir[left].insert(*i);
                    }
                    if(i==a.end()-1&&flag==1){
                        flagall=1;
                    }
                    if(flag==0)break;
           		}
                if (flagall == 1) {
                    fir[left].insert("e");
                }
        }
    }
	}
    return fir[left];
}
//求first集合 
void grammer_analyzer::getfirst(){
	for(auto &a:ter){
		fir[a].insert(a);
	}
	for(auto &a:nter){
		nterfirst(a);
	}
	// cout << "First集" << endl;
	// for (map<string, set<string>>::iterator it = fir.begin(); it != fir.end(); it++) {
	// 	cout << it->first << " : "  ;
	// 	for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
	// 	{
	// 		cout << *ii << " ";
	// 	}
	// 	cout << endl;
	// }
}

//求follow集合
void grammer_analyzer::getfollow(){
	//map<string,vector<vector<string> > > pro;
	for(auto &prolist:pro){
		string left=prolist.first;
		for(auto &rightlist:prolist.second){
			for(vector<string>::iterator i=rightlist.begin();i!=rightlist.end();i++){
				if(ister(*i)){
					continue;
				}
				else if((i+1)!=rightlist.end()&&isnter(*(i+1))){
					set<string> temp=fir[*(i+1)];
					for(auto &ii:temp){
						if(ii!="e")follow[*i].insert(ii);
					}
				}
				else if((i+1)!=rightlist.end()&&ister(*(i+1))){
					follow[*i].insert(*(i+1));
				}
			}
			for(vector<string>::iterator i=rightlist.end()-1;i!=rightlist.begin()-1;i--){
				if(ister(*i))break;
				else {
					set<string>aa = follow[left];
					for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[*i].insert(*pp);
					}
				}
				if(fir[*i].find("e")==fir[*i].end())break;
			}
		}
	}
	for(auto &prolist:pro){
		string left=prolist.first;
		for(auto &rightlist:prolist.second){
			for(vector<string>::iterator i=rightlist.begin();i!=rightlist.end();i++){
				if(ister(*i)){
					continue;
				}
				else if((i+1)!=rightlist.end()&&isnter(*(i+1))){
					set<string> temp=fir[*(i+1)];
					for(auto &ii:temp){
						if(ii!="e")follow[*i].insert(ii);
					}
				}
				else if((i+1)!=rightlist.end()&&ister(*(i+1))){
					follow[*i].insert(*(i+1));
				}
			}
			for(vector<string>::iterator i=rightlist.end()-1;i!=rightlist.begin()-1;i--){
				if(ister(*i))break;
				else {
					set<string>aa = follow[left];
					for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[*i].insert(*pp);
					}
				}
				if(fir[*i].find("e")==fir[*i].end())break;
			}
		}
	}
	for(auto &prolist:pro){
		string left=prolist.first;
		for(auto &rightlist:prolist.second){
			for(vector<string>::iterator i=rightlist.begin();i!=rightlist.end();i++){
				if(ister(*i)){
					continue;
				}
				else if((i+1)!=rightlist.end()&&isnter(*(i+1))){
					set<string> temp=fir[*(i+1)];
					for(auto &ii:temp){
						if(ii!="e")follow[*i].insert(ii);
					}
				}
				else if((i+1)!=rightlist.end()&&ister(*(i+1))){
					follow[*i].insert(*(i+1));
				}
			}
			for(vector<string>::iterator i=rightlist.end()-1;i!=rightlist.begin()-1;i--){
				if(ister(*i))break;
				else {
					set<string>aa = follow[left];
					for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[*i].insert(*pp);
					}
				}
				if(fir[*i].find("e")==fir[*i].end())break;
			}
		}
	}
	for(auto &prolist:pro){
		string left=prolist.first;
		for(auto &rightlist:prolist.second){
			for(vector<string>::iterator i=rightlist.begin();i!=rightlist.end();i++){
				if(ister(*i)){
					continue;
				}
				else if((i+1)!=rightlist.end()&&isnter(*(i+1))){
					set<string> temp=fir[*(i+1)];
					for(auto &ii:temp){
						if(ii!="e")follow[*i].insert(ii);
					}
				}
				else if((i+1)!=rightlist.end()&&ister(*(i+1))){
					follow[*i].insert(*(i+1));
				}
			}
			for(vector<string>::iterator i=rightlist.end()-1;i!=rightlist.begin()-1;i--){
				if(ister(*i))break;
				else {
					set<string>aa = follow[left];
					for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[*i].insert(*pp);
					}
				}
				if(fir[*i].find("e")==fir[*i].end())break;
			}
		}
	}
	// cout << "Follow集" << endl;
	// for (map<string, set<string>>::iterator it = follow.begin(); it != follow.end(); it++) {
	// 	cout << it->first << " : "  ;
	// 	for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
	// 	{
	// 		cout << *ii << " ";
	// 	}
	// 	cout << endl;
	// }
}
//获取预测分析表索引位置,flag=0表示获取非终结符位置，flag=1表示获取终结符位置
int grammer_analyzer::getindex(string s,int flag)
{
	int n=nter.size();
	int m=ter.size();
	if(flag==0){
		for(int i=1;i<=n;i++){
			if(table[i][0]==s)return i;
		}	
	}
	else {
		for(int i=1;i<=m;i++){
			if(table[0][i]==s)return i;
		}	
	}
	return -1;
}
//将vector字符串转换为一个字符串，以空格分隔
string grammer_analyzer::tostring(vector<string> s){
	string ans="";
	for(auto &a:s){
		ans+=a+" ";
	}
	return ans;
}
//将set字符串转换为一个字符串，以空格分隔
string grammer_analyzer::tostring(set<string> s){
	string ans="\'";
	for(auto &a:s){
		ans+=a+"\' or \'";
	}
	return ans;
}
//将vector字符串指定段转换为一个字符串，以空格分隔
string grammer_analyzer::tostring(vector<pair<string,int>> s,int i){
	string ans="";
	int n=s.size();
	for(int j=i;j<n;j++){
		ans+=s[j].first+" ";
	}
	return ans;
}
//将栈转换为一个字符串，以空格分隔
string grammer_analyzer::tostring(stack<Node*> s){
	vector<string> ans;
	while(!s.empty()){
		ans.push_back(s.top()->val);
		s.pop();
	}
	string res="";
	for(int i=ans.size()-1;i>=0;i--){
		//cout<<ans[i]<<endl;
		res+=ans[i];
	}
	return res;
}
vector<string> grammer_analyzer::tovector(string s){
    vector<string> ans;
	istringstream is(s);
    string str;
    while(is>>str)  
    {  
        ans.push_back(str); 
    }  
    return ans;
}
//求预测分析表 
void grammer_analyzer::gettable(){
	int n=nter.size();
	int m=ter.size();
	table.resize(n+2,vector<string>(m+2,"err"));
	for(int i=1;i<=m;i++){
		if(ter[i-1]=="e"){
			table[0][i]="$";
			continue;
		}
		table[0][i]=ter[i-1];
	}
	for(int i=1;i<=n;i++)table[i][0]=nter[i-1];
	table[0][0]=" ";
	for(auto &prolist:pro){
		string left=prolist.first;
		for(auto &rightlist:prolist.second){//prolist.secon: E' T | T F | id  对每一个产生式
			int cnt=0;
			int flag=0;
			while(1){
				if(cnt>=rightlist.size())break;
				set<string> temp=fir[rightlist[cnt]];
				for(auto &terminal:temp){
					if(terminal=="e"){
						flag=1;
						continue;
					}
					int x=getindex(left,0);
					int y=getindex(terminal,1);
					table[x][y]=tostring(rightlist);//把A->α放入表项M[A,α]中
				}
				if(flag==1){
					cnt++;
					continue;
				}
				else break;
			}
			if(flag){//α的first集合中有空
				set<string> tempfol=follow[left];
				for(auto &terminal:tempfol){
					int x=getindex(left,0);
					int y=getindex(terminal,1);
					table[x][y]=tostring(rightlist);//把A->α放入表项M[A,b]中
				}
			}
		}
	}
	for(auto &nt:nter){
		for(auto &t:follow[nt]){
			int x=getindex(nt,0);
			int y=getindex(t,1);
			if(table[x][y]=="err"){
				table[x][y]="synch";
			}
		}
	}
	// printf ( "%-100s\n" , "预测分析表" );
	// for(int i=0;i<=n;i++){
	// 	for(int j=0;j<=m/2;j++){
	// 		printf ( "%6s|" , table[i][j].c_str());
	// 	}
	// 	cout<<endl;
	// 	cout<<"-------------------------------------------------------------------------------------------";
	// 	cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
	// }
	// printf ( "%-100s\n" , "预测分析表" );
	// for(int i=0;i<=n;i++){
	// 	for(int j=m/2;j<=m;j++){
	// 		printf ( "%6s|" , table[i][j].c_str());
	// 	}
	// 	cout<<endl;
	// 	cout<<"-------------------------------------------------------------------------------------------";
	// 	cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
	// }
}
//判断是否是非终结符 
bool grammer_analyzer::isnter(string s){
	for(auto &a:nter){
		if(a==s)return true;
	}	
	return false;
}
//判断是否是终结符 
bool grammer_analyzer::ister(string s){
	for(auto &a:ter){
		if(a==s)return true;
	}	
	return false;
}
//语法分析预测分析程序
void grammer_analyzer::analyse(string path,lexical_analyzer &la){
	map<int,string> temp=la.wordtable;
	FILE *instream = fopen(path.c_str(), "r");
	if(!instream){
		cout<<"Failed to open the file"<<endl;
		exit(1);
	}
	char ch;
	ch=fgetc(instream);
	vector<pair<string,int>> inputbuffer;
	queue<string> idq;
	queue<string> consq;
	int no,attr;
	string nowstr;
	//处理词法输出，保存到inputbuffer中
	while(ch!=EOF){
		nowstr="";
		if(ch=='('){
			while(ch!=','){
				ch=fgetc(instream);
				nowstr+=ch;
			}
			no=atoi(nowstr.c_str());
			nowstr="";
			ch=fgetc(instream);
			//if(no!=21&&no!=46){
			while(ch!=','){
				nowstr+=ch;
				ch=fgetc(instream);
			}
			if(no==21){
				int tt=atoi(nowstr.c_str());
				idq.push(la.i.get(tt));
			}
			else if(no==46){
				int tt=atoi(nowstr.c_str());
				consq.push(la.ct.get(tt));
			}
			nowstr="";
			while(ch!=')'){
				ch=fgetc(instream);
				nowstr+=ch;
			}
			int lineno=atoi(nowstr.c_str());
			string ii=temp[no];
			inputbuffer.push_back(make_pair(ii.c_str(),lineno+1));
			ch=fgetc(instream);
		}	
	}
	inputbuffer.push_back(make_pair("$",0));
	stack<Node*> s;
	s.push(new Node("$",0));
	string x,a;
	int i=0;
	int cnt=1;
	string proused="";
	root=new Node("program",0);
	s.push(root);
	int errorflag=0;
	do{
		string temp1=tostring(s);
		string temp2=tostring(inputbuffer,i);
		// printf ( "%-s","步骤:");
		// printf("%-d\n",cnt);
		// printf("%-s","符号栈:") ;
		// printf("%-s\n",temp1.c_str());
		// printf("%-s","输入串:" );
		// printf("%-s\n",temp2.c_str());
		// printf("%-s","所用产生式:") ;
		// printf("%-s\n",proused.c_str());
		x=s.top()->val;
		a=inputbuffer[i].first;
		int lineno=inputbuffer[i].second;
		if(ister(x)||x=="$"){
			proused="";
			if(x==a){
				s.pop();
				i++;
			}
			else {
				cout<<"Grammer analysis error:";
				cout<<"expected \'"<<x<<"\' before \'"<<a<<"\' at rows "<<lineno<<endl;
				errorflag=1;
				s.pop();
			}
		}
		else{
			if(table[getindex(x,0)][getindex(a,1)]!="err"){
				if(table[getindex(x,0)][getindex(a,1)]=="synch"){
					cout<<"Grammer analysis error:";
					cout<<"expected "<<tostring(fir[x])<<" before \'"<<idq.front()<<"\' at rows "<<lineno<<endl;
					errorflag=1;
					s.pop();
				}
				else{
					Node * nroot=s.top();
					s.pop();
					vector<string> temp=tovector(table[getindex(x,0)][getindex(a,1)]);
					int n=temp.size();
					vector<Node*> temp2;
					for(int i=0;i<n;i++){
						if(temp[i]=="e")continue;
						if(temp[i]=="id"){
							Node * tnode=new Node(temp[i],idq.front(),lineno);
							idq.pop();
							nroot->add_son(tnode);
							temp2.push_back(tnode);
						}
						else if(temp[i]=="cons"){
							Node * tnode=new Node(temp[i],consq.front(),lineno);
							consq.pop();
							nroot->add_son(tnode);
							temp2.push_back(tnode);
						}
						else {
							Node * tnode=new Node(temp[i],lineno);
							nroot->add_son(tnode);
							temp2.push_back(tnode);
						}
						
					}
					int m=temp2.size();
					for(int i=m-1;i>=0;i--){
						s.push(temp2[i]);
					}
					proused=x+"->"+table[getindex(x,0)][getindex(a,1)];
				}
			}
			else{
				cout<<"Grammer analysis error:";
				cout<<"expected "<<tostring(fir[x])<<" before \'"<<idq.front()<<"\' at rows "<<lineno<<endl;
				errorflag=1;
				i++;
			}
		}
		cnt++;
	}while(x!="$");
	if(errorflag)exit(0);
	cout<<"Grammer analysis accepted!"<<endl;
}
bool cmp(Node* a,Node* b){
	return a->id<b->id;
}
//打印语法树
void grammer_analyzer::printtree(){
	vector<Node*> ans;
	dfs(root,ans);
	cout<<"语法树"<<endl;
	sort(ans.begin(),ans.end(),cmp);
	for(auto &a:ans){
		if(a->father==NULL)cout<<0<<" ";
		else cout<<a->father->id<<" ";
	}
	for(auto &a:ans){
		cout<<"string(\'"<<a->val<<"\')"<<",";
	}
	cout<<endl;
}
//搜索语法树
void grammer_analyzer::dfs(Node* r,vector<Node*> &ans){
	if(r!=NULL){
		 ans.push_back(r);
	}
	else return;
	int n=r->sons.size();
	for(int i=n-1;i>=0;i--){
		dfs(r->sons[i],ans);
	}
	return ;
}
map<string,vector<vector<string> > > grammer_analyzer::pro;
map<string,set<string> > grammer_analyzer::fir;
map<string,set<string> > grammer_analyzer::follow;
vector<string> grammer_analyzer::nter={"program","header","headers","programs","program1","fundefine","para0","para1","type","paralist","para","sentences","sentences1","sentence","statement","idlist",
	"idassignlist2","idlist3","para2","assignment","assignment1","arrayassign","arrayassign2","expression","expression1","fun","opexpression","opnum","opexpression1","branch","branch1"
	,"branch2","cmpexpression","cmpope","loop","forloop","whileloop","jump"};
vector<string> grammer_analyzer::ter={"int","bool","double","float","short","long","char","for","if","else","while","break","swtich","void"
		,"return","include","continue","do","get","put","id",".","|","(",")","[","]","=","==","<",":",";","*","/","%","{","}","<>"
		,"#","<=",">",">=","+",	"-","&","cons","\"","+=","-=","!=","_",",","\'","e"};
vector<vector<string> > grammer_analyzer::table;
Node* grammer_analyzer::root;
//
// expression -> opexpression | fun | id opexpression1
// fun -> id ( paralist )
//program1 -> header program2
