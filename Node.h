#ifndef NODE_H_
#define NODE_H_
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
class Node{
public:
	string type; 
	int width;
    string val;
    vector<Node*> sons;
    Node *father;
    string name;
    int ivalue;
    int id;
    int line;
    static int cur_id;
    int trueno,falseno,next;
    Node(string s,int no){
        ivalue=0;
        val = s;
        line = no;
        if(s=="$");
        else id = ++cur_id;
    }
    Node(string s,string name,int no){
        ivalue=0;
        val = s;
        this->name=name;
        line = no;
        if(s=="$");
        else id = ++cur_id;
    }
    void add_son(Node* son){
        son->father=this;
        sons.push_back(son);
    }
    
};

#endif
