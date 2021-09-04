#ifndef FUNC_H_
#define FUNC_H_
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

class func{
public:
    string name;
    string type;
    int flag;//0:undefined 1:defined
    int pnum;
    vector<string> ptype;
    func(string n,string t,int f,int s,vector<string> o):name(n),type(t),flag(f),pnum(s),ptype(o){};
    func(){	};
}; 


#endif
