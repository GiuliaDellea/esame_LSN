#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include <cmath>
using namespace std;

double error(double AV[],double AV2[],int n){
  if (n==0)
    return 0;
  else{
    return sqrt((AV2[n] - AV[n]*AV[n])/n);
  }
}

double prob1(double a,double b,double c){
  double v=exp(-2*sqrt(a*a+b*b+c*c))/M_PI;
  return v;
}

double prob2(double a,double b,double c){
  double v=(a*a+b*b+c*c)*exp(-sqrt(a*a+b*b+c*c))*(c*c/(a*a+b*b+c*c))/32*M_PI;
  return v;
}
 
int main (int argc, char *argv[]){

 

  int M=1e6; 
  int N=100;
  int L=(M/N);
  
  Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
	    // cout<<seed[0] << seed[1] << seed[2] << seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   double xn,yn,zn,xn1,yn1,zn1;
   double delta=1.4;
   double r,c,A, tot=0, acc=0;
   double* ave1= new double[N]{0}; 
   double* av21= new double[N]{0};
   double* sum_prog1= new double[N]{0};
   double* su2_prog1= new double[N]{0};

   /*ofstream output1;
   output1.open ("R2_prog.txt");
   ofstream output2;
   output2.open ("err_R2_prog.txt");*/
   ofstream outputx;
   outputx.open ("xfond.txt");
   ofstream outputy;
   outputy.open ("yfond.txt");
   ofstream outputz;
   outputz.open ("zfond.txt");

   xn=100;
   yn=100;
   zn=100;
   outputx<<xn<<endl;
   outputy<<yn<<endl;
   outputz<<zn<<endl;
   double sum1;
   for(int i=0;i<N;i++){
     sum1=0;
     for(int j=0;j<L;j++){
       xn1=rnd.Rannyu(xn-delta,xn+delta);
       yn1=rnd.Rannyu(yn-delta,yn+delta);
       zn1=rnd.Rannyu(zn-delta,zn+delta);
       /*xn1=rnd.Gauss(xn,delta);
       yn1=rnd.Gauss(yn,delta);
       zn1=rnd.Gauss(zn,delta);*/
       tot+=1;
       c=prob2(xn1,yn1,zn1)/prob2(xn,yn,zn);
       if(c<=1)
	 A=c;
       else
	 A=1;
       r=rnd.Rannyu();
       if(r<=A){
	 xn=xn1;
	 yn=yn1;
	 zn=zn1;
	 acc+=1;
	 outputx<<xn<<endl;
	 outputy<<yn<<endl;
	 outputz<<zn<<endl;
	 sum1+=sqrt(xn*xn+yn*yn+zn*zn);
       }else{
	 sum1+=sqrt(xn*xn+yn*yn+zn*zn);
       }
    ave1[i]=sum1/L;
    av21[i]=pow(ave1[i],2);
     }
   }

   /*for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	sum_prog1[i]+=ave1[j];
	su2_prog1[i]+=av21[j];
      }
      sum_prog1[i]/=(i+1);
      output1<<sum_prog1[i]<<endl;
      su2_prog1[i]/=(i+1);
      output2<<error(sum_prog1,su2_prog1,i)<<endl;
      }*/

    cout<<acc/tot<<endl;
     
   
     

   /*output1.close();
   output2.close();*/
   outputx.close();
   outputy.close();
   outputz.close();

   
     
   
    

   return 0;
}
