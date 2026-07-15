#include <iostream>
using namespace std;
/*class Employee{
    private:
    int salary;
public:
Employee(int s){
   salary = s;
}
friend void displaySalary(Employee emp);
};
  void displaySalary(Employee emp){
    cout<<"salary:"<<emp.salary;
};

int main(){
    Employee mysal(20000);
    displaySalary(mysal);
    return 0;
}*/
/*
class myclass{
    public:
    void myfunction(){
        cout<<"content of base class";

    }
};
class myotherclass{
    public:
    void anyotherfunction(){
        cout<<"any other function";

    }
};
//derived class
class mychildclass:public myclass,public myotherclass{

};
int main(){
    mychildclass myobj;
    myobj.myfunction();
     myobj.anyotherfunction();
     return 0;
}
*/
// multiple inheritance
class employee{
    protected:
    int salary;
};
class programmer:public employee{
    public:
    int bonus;
    int setsalary(int x){
      salary =x;
    }
  int getsalary(){
        return salary;
    }
};
int main(){
    programmer mysal;
    mysal.setsalary(80000);
      mysal.bonus=15000;
      cout<<"salary"<<mysal.getsalary();
      cout<<"\n bonus"<<mysal.bonus;
      return 0 ;
}
