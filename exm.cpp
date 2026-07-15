#include <iostream>
using namespace std;
int main(){
double temp[]={37.5,32.6,30,26,25,31,34};
double minTemp = temp[0];
double maxTemp = temp[0];
double avg=0.0;
double sum=0.0;
  int arraylength=sizeof(temp)/sizeof(temp[0]);
  for(int i =0; i<arraylength; i++){
    if(temp[i] < minTemp){ minTemp=temp[i]; }
    if(temp[i] > maxTemp){ maxTemp=temp[i];}
    sum+=temp[i];
  }
  avg=sum/arraylength;
  cout << "Minimum Temperature: " << minTemp << endl;
    cout << "Maximum Temperature: " << maxTemp << endl;
    cout<<"sum "<<sum<<endl ;
    cout << "Average Temperature: " << avg << endl;
    
  return 0;
}