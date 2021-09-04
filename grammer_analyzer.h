#ifndef GRAMMER_ANALYZER_H_
#define GRAMMER_ANALYZER_H_
#include<iostream>
#include<string>
#include<map>
#include <iomanip>
#include<vector>
#include <fstream> 
#include<cstdio>
#include<fstream>
#include <utility> 
#include<sstream>
#include<stack>
#include<queue>
#include<algorithm>
#include "lexical_analyzer.h"
#include"Node.h"
#include<set>
using namespace std;
class grammer_analyzer{
	private:
		static map<string,vector<vector<string> > > pro;
		static map<string,set<string> > fir;
		static map<string,set<string> > follow;
		static vector<string> nter;
		static vector<string> ter;
		static vector<vector<string> > table;
		static Node * root;
	public:
		grammer_analyzer(string path2);
		void printpro();
		set<string> nterfirst(string left);
		void getfirst();
		void getfollow();
		bool isnter(string s);
		bool ister(string s);
		void gettable();
		int getindex(string s,int flag);
		string tostring(vector<string> s);
		string tostring(set<string> s);
		string tostring(vector<pair<string,int> > s,int i);
		string tostring(stack<Node*> s);
		vector<string> tovector(string s);
		void analyse(string path,lexical_analyzer &la);
		void printtree();
		void dfs(Node* r,vector<Node*>& ans);
		Node* getroot(){return root;};
};


#endif
