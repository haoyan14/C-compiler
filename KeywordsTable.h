#ifndef   KEYWORDSTABLE_H_   
#define   KEYWORDSTABLE_H_   
#include<iostream>
#include<string>
#include<map>
using namespace std;
class KeywordsTable{
	private:
		static string words[30];
		map<string,int> m;
	public:
		KeywordsTable(){
			init();
		} 
		void init();
		int get(string str);
		
};

#endif
