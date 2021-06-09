#ifndef PERSON
#define PERSON
#include<iostream>
#include<string>
using namespace std;


class Person{
friend istream& read(istream& ,Person& );
friend ostream& print(ostream& ,const Person & );
public:
    person()=default;
    person(const string& s1, const string& s2):
            name(s1),addredd(s2) {}
    Person& get_name()const {return name;}
    Person& get_address()const {return address;}
private:
    string name;
    string address;
};


istream& read(istream& is,Person& p){
    cout<<"Please input name and address of a persen:"<<endl;
    is>>p.name>>p.address;
    return is;
}


ostream& print(ostream& os,const Person & p){
    os<<p.get_name()<<" "<<p.get_address();
    return os;
}


#endif
