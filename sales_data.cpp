#include <iostream>
#include "Sales_data.h"
using namespace std;
int main(){
    Quote q1("book1",12.5);
    Bulk_quote q2("book2",12.5,5,0.5);
    Quote * p1=&q2;
    p1->debug();
}
