#ifndef   SYMBOL_H_   
#define   SYMBOL_H_   
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
class symbol{
public:
    string name;
    string type;
    int scope;
    int offset;
    static int off;
    int regnum;
    symbol(string n,string t,int s,int o):name(n),type(t),scope(s),offset(off),regnum(-1){off+=4;};
}; 

#endif
