#include<iostream>
#include<string>
using namespace std;
class a{
public:
    a(istream& is=cin){cin>>word;}
    //a(string s="hello"):word(s){}
    string word;
};


int main(){
    a a1;
    cout<<a1.word;
    return 0;
}
