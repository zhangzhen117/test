#include "ZHEN.h"
class C1{
  int a;
public:
  C1(){cout<<"a new C1"<<endl;}
};
class C2:public C1{
  int b;
public:
  C2():C1(){cout<<"a new C2 based on C1"<<endl;}
};
int main(){
  C1 c1;
  C2 c2;
  return 0;
}
