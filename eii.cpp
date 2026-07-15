#include<iostream>
using namespace std;
class vehicle{
    public:
    string brand="ford";
    int yrmfg;
   string color="red";
   void honk(){
    cout<<"toot";
   }
};

class car:public vehicle{
    public:
    string model="mustang";
};
int main(){
car gari;
gari.honk();
cout<<gari.model<<""<<gari.color;
 return 0;
}