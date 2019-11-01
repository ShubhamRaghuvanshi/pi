#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class number{



  public:

        unsigned long int base;
        long int precision;
        int radix;
        vector<unsigned long int> digit; 
        bool sign;


        number();  

        number( bool sign, vector<unsigned long int> d,unsigned long int b, int r );

        void Initialize(bool sign, vector<unsigned long int> d, unsigned long int b, int r);
        friend number Combine(number n1, number n2);
        friend number Add(number n1, number n2);
        friend number Complement(number n);
        friend number Subtract(number n1, number n2);
        friend number Multiply(number n1, number n2);
        friend number Divide(number n, unsigned long int d, int p);
        void Roundoff(int Nroundoff);
        void Equals(number n);
        void Print();
        void Format();
        ~number();
        
};

long int concat(long int a, long int b) ;
number ArcTan(int x, long int Base, int Np); 


  
#endif
