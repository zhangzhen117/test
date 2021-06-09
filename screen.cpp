#include"Screen.h"

int main(){
    Screen myScreen(5,5,'x');
    myScreen.display(cout);
    cout<<endl;
    Screen s1=myScreen.move(4,0);
    myScreen.set('a').display(cout);
    cout<<endl;
    s1.set('a').display(cout);
    cout<<endl;

    return 0;
}
