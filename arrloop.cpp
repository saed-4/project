#include <iostream>
#include <string> 
using namespace std;
int sum=0;
int avg=0;
int main(){
int num[]={20,30,40,50,60,70,80};
int arraylength= sizeof(num)/sizeof(num[0]);
    for(int i=0; i<7; i++){
        sum+=num[i];
    }
    avg=sum/arraylength;
    cout<<"Sum: "<<sum<<endl;
    cout<<"Average: "<<avg<<endl;
    return 0;
}