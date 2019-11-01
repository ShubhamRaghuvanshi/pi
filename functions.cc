
#include <iostream>
#include <iomanip> 
#include <math.h>
#include <vector>
#include <string>

#include "functions.h"

using namespace std;


number::number(){
}

number::~number(){}

number::number(bool s, vector<unsigned long int> d, unsigned long int b, int r ){

  digit = d;
  base = b;
  radix = r;
  precision = digit.size() - radix;
  sign =s;
}


void number::Initialize(bool s, vector<unsigned long int> d, unsigned long int b, int r){

  digit = d;
  base = b;
  radix = r;
  precision = digit.size() - radix;
  sign =s;
}


void  number::Roundoff(int Nroundoff){

  int Nlast = radix - Nroundoff;
  
  if(Nlast > 0){
    int temp = digit[Nlast-1];
    digit.erase( digit.begin(), digit.begin() + Nlast); 
    radix = radix - Nlast;
  }
}

number Complement(number n){

  number nc=n;
  nc.digit[0] = n.base - n.digit[0];
  for(int i=1; i<n.digit.size(); i++){
    nc.digit[i] = n.base -1 - n.digit[i];
  }
  return nc;

}

void number::Print(){

  if(sign == 1) cout<<"-";   
  int BaseDigits =  floor ( log10(base)) +1;

   for(int i=digit.size() -1 ; i>=2; i--){

   if(digit[i]>0) {
    int k= floor( log10(digit[i]) )+1;
    for(int i= k; i< BaseDigits-1 ; i++ )
      cout<<"0";
    }
    else  {
      for(int i=1; i<BaseDigits-1; i++ ) 
        cout<<"0";
  }
      
    cout<<digit[i];
    if(i == radix && radix >0 ) cout<<". ";     
    if(i%20 == 0 ) cout<<endl;
  }
  cout<<endl;
}


number Combine(number n1, number n2){

  if(n1.base != n2.base ){
    cout<<"Numbers are in different basis "<<endl;  
    return n1;
  }  

//cout<<"combining"<<endl;
//cout<<n1.radix<<" "<<n2.radix<<endl;
//cout<<n1.precision<<" "<<n2.precision<<endl;

  int dr=0;
  if(n1.radix > n2.radix){
    for(int i=0; i< n1.radix-n2.radix; i++){
      n2.digit.insert(n2.digit.begin(),0);
      dr++;
    } 
    n2.radix = n2.radix +dr;
  } 

  if(n2.radix > n1.radix){
    for(int i=0; i< n2.radix-n1.radix; i++){
      n1.digit.insert(n1.digit.begin(),0);      
      dr++;
    }
    n1.radix = n1.radix +dr;
  } 

  if( n1.precision > n2.precision){
    for(int i=0; i < n1.precision - n2.precision; i++ ){
      n2.digit.push_back(0);           
    }
  }

  if( n2.precision > n1.precision){
    for(int i=0; i < n2.precision - n1.precision; i++ ){
      n1.digit.push_back(0);
    }
  }


    if( n1.sign == 0 && n2.sign == 1) 
      return Subtract(n1,n2);
    else if (n1.sign == 1 && n2.sign == 0)    
      return Subtract(n2,n1);    
    else 
      return Add(n1, n2);  

}


number Add(number n1, number n2){
  
  number n3=n1;
  int carry =0;
  
  for(int i= 0 ; i< n1.digit.size(); i++){
    n3.digit[i] = n1.digit[i] + n2.digit[i] + carry;
      
    if(n3.digit[i] >= n1.base){
      n3.digit[i] = n3.digit[i]%n1.base;
      carry = 1;
    }
    else carry =0;
  }

  if(carry ==1){
    n3.digit.push_back(carry);
  } 

  int j=0; 
  while (n3.radix > n3.digit.size()-1  )
  {  n3.digit.push_back(0);
    j++;
    if(j>100) break;
  }

  n3.precision = n3.digit.size() - n3.radix;
  return n3;
}

number Subtract(number n1, number n2){

  number n3=n1;

  int carry =0;

  n2 = Complement(n2);

  for(int i= 0 ; i<n1.digit.size(); i++){
  
    n3.digit[i] = n1.digit[i] + n2.digit[i] + carry;

    if(n3.digit[i] >= n1.base){
      n3.digit[i] = n3.digit[i]%n1.base;
      carry = 1;
    }
    else carry =0;
  }

  int j=0; 
  while (n3.radix > n3.digit.size()-1  )
  {  n3.digit.push_back(0);
    j++;
    if(j>100) break;
  }

  n3.precision = n3.digit.size() - n3.radix;
  if(carry == 1) {
    n3.sign =0;
    return n3;
  }

  else{ 
    n3.sign =1;
    return Complement(n3);
  }
}

number Multiply(number n1, number n2){
  
  if(n1.base != n2.base ){
    cout<<"Numbers are in different basis "<<endl;  
    return n1;
  }  

  number n3;
  n3.base = n1.base;
  n3.radix = n1.radix + n2.radix;
  
  if(n1.sign == n2.sign )  n3.sign =0;
  else n3.sign =1;
    
  long int temp;
  int carry=0;
  
  int Nterms = n1.digit.size() + n2.digit.size() -1;

  for(int k=0; k<Nterms; k++ ){
    temp=0; 
    for(int i=0;  i<n1.digit.size() ;  i++ ){
      if( k-i < n2.digit.size()  )
        temp = temp + n1.digit[i]*n2.digit[k-i] ;
    }  // k'th term
    temp = temp + carry;
    if(temp >= n3.base) {      
      carry = temp/n3.base;      
      temp = temp%n3.base;     
    }
    else carry =0;
    n3.digit.push_back(temp);
  } // k loop 
    
  if(carry != 0) n3.digit.push_back(carry);
  
  n3.Format();
  return n3;
}

void number::Format(){

  int pr=0;  
  for(int i=0; i< radix; i++){
    if(digit[i] ==0){
      pr++;
    }
    else break;
  }
  digit.erase(digit.begin(), digit.begin() + pr );
  radix = radix - pr;
  if(radix < 0) 
    radix =0;
    
  for(int i = digit.size() -1  ; i>= radix; i--){
    if( digit[i] == 0  )
      digit.erase(digit.begin()+i);
    else 
      break;
  }
  
  int j=0; 
  while (radix > digit.size()-1  )
  {  
    digit.push_back(0);
    j++;
    if(j>100) break;
  }

   precision = digit.size() - radix; 
}



long int concat(long int a, long int b) 
{ 
  
    // Convert both the integers to string 
    string s1 = to_string(a); 
    string s2 = to_string(b); 
  
    // Concatenate both strings 
    string s = s1 + s2; 
  
    // Convert the concatenated string 
    // to integer 
    long int c = stoi(s); 
  
    // return the formed integer 
    return c; 
 
}


number Divide(number n, unsigned long int d, int p){

  if(d >= n.base){
    cout<<"Dividor is out of base"<<endl;
    return n;
  }

  if(d ==0 ){
    cout<<"inf"<<endl;
    return n;
  }

  bool dsign;
  if(d>=0 ) dsign =0;
  else      dsign =1;

  number q;
  q.base = n.base;  
  if(dsign == n.sign )  q.sign =0;
  else                  q.sign =1;

//  for(int i=0; i<p; i++)
//    n.digit.insert(n.digit.begin(),0);

  int itr = n.digit.size()-1;
  unsigned long int divident=0, remainder=0, quotient; 
  int BaseDigits = floor (log10 (n.base)); 
 
//  n.Print();
//  cout<<setw(15)<<"itr"<<setw(15)<<"divident"<<setw(15)<<"d"<<setw(15)<<"quotient"<<setw(15)<<"remainder"<<setw(15)<<itr<<setw(15)<<p<<endl;


  
    int temp=0; 
    int Base = pow(10, floor( log10(n.base -1 )  ) + 1 );

  while(itr > -p){
   
    if(itr >= 0){
      divident = remainder*Base + n.digit[itr];
      if(divident >= d){
  
      }

      else{
        if(itr>0){
          divident = n.digit[itr]*Base + n.digit[itr-1];
          q.digit.insert(q.digit.begin(), 0); 
        } 
        itr--;
      }
    }
    else{ 
      divident = remainder*Base;
      temp++;  
    }

      quotient = divident/d;
      remainder = divident - quotient*d;
      q.digit.insert(q.digit.begin(), quotient);
      itr--;
//cout<<itr<<endl;
// q.Print(); 
 //  cout<<setw(15)<<itr<<setw(15)<<divident<<setw(15)<<d<<setw(15)<<quotient<<setw(15)<<remainder<<endl;
 
}  

  q.radix = temp  + n.radix  ;
 
//cout<<q.digit.size()<<" "<<q.radix<<" "<<itr<<" "<<n.radix<<endl;
//  q.Print(); 
  q.Format();
 
  return q;

}



number ArcTan(int  x ,long int Base, int Np){ 
 
  number one,sum, term;

  one.base = Base;  
  one.digit.push_back(1);  
  one.sign =0;
  one.radix=0;
  one.precision =0;


  sum.base = Base;
  sum.digit.push_back(0);  
  sum.sign =0;
  sum.radix=0;
  sum.precision =0;

  term.base = Base;
  term.digit.push_back(1);  
  term.sign =0;
  term.radix=0;
  term.precision =0;


  long int coeff = 1 ;

  one =  Divide(one, x, Np);
  sum = one;
  one = Multiply(one,one);

  for(int i=1; i<=8000; i++){

    term.sign = !term.sign;
    term  = Multiply(term,one);

    term.Roundoff(Np);
    term.Format();
       
    sum = Combine( sum, Divide(term, (2*i+1)*x, Np ) ); 

   
    sum.Roundoff(Np);
    sum.Format();

 //cout<<i<<setw(20)<<(2*i+1)*x<<endl;   
  // sum.Print();
    
   

  }

  return sum;

}







void number::Equals(number n){
  base = n.base;
  radix = n.radix;
  digit = n.digit;
  precision = n.precision;
  sign = n.sign;
}





























