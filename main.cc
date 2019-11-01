#include <iostream>
#include"functions.h"
#include<time.h> 


#include<limits.h> // for int,char macros 
#include<float.h> // for float,double macros 


using namespace std;

int main(){

  int pr=800;
  vector<unsigned long int> digit;
  digit.push_back(16);

  unsigned long int base =10000000;

  number n1 = ArcTan(5,base, pr);
  number n2 = ArcTan(239,base, pr);
  number n3( 0, digit, base , 0 );
  
//  cout<<"#######################################"<<endl;

  number n4 = Multiply( n1,n3 );

//  n1.Roundoff(pr);
//  n4.Roundoff(pr);
  
//  n1.Print();
//  Divide(n4,16,pr).Print();




  n3.sign =1;
  n3.digit[0] = 4;
  
  n3 = Multiply(n2, n3);
//  n3.Roundoff(pr);  
  
 // n2.Roundoff(pr);
//cout<<"##########################################"<<endl;
//  n2.Print();

//  Divide(n3, 4, pr).Print();
  
  n4 = Combine(n4,n3);
  n4.Roundoff(pr);      
  n4.Print();


 return 0;
}
