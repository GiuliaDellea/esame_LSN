#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "es08_nonSA.h"
#include <cmath>
using namespace std;

double error(double AV[],double AV2[],int n){
  if (n==0)
    return 0;
  else{
    return sqrt((AV2[n] - AV[n]*AV[n])/n);
  }
}

double prob(double x){
  return pow(exp(-pow(x-mu,2)/(2*pow(sigma,2)))+exp(-pow(x+mu,2)/(2*pow(sigma,2))),2);
}

double ValH(double x){
  double V=pow(x,4)-(5./2.)*pow(x,2);
  double e1=exp(-pow(x-mu,2)/(2*pow(sigma,2)));
  double e2=exp(-pow(x+mu,2)/(2*pow(sigma,2)));
  double psi=e1+e2;
  double d2_psi=e1*(pow(-(x-mu)/pow(sigma,2),2)-pow(sigma,-2))+e2*(pow(-(x+mu)/pow(sigma,2),2)-pow(sigma,-2));
  return -0.5*d2_psi/psi+V;
}
 
int main (int argc, char *argv[]){

 

  int M=1e6;    //tot passi
  int N=100;    //blocchi
  int L=(M/N);  //passi per blocco
  
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

   double xn,xn1;
   double delta=2.4;
   double r,c,A;
   int tot=0, acc=0;
   double* ave= new double[N]{0}; 
   double* av2= new double[N]{0};
   double* sum_prog= new double[N]{0};
   double* su2_prog= new double[N]{0};

   ofstream output1;
   output1.open ("H_ott.txt");
   ofstream output2;
   output2.open ("err_H_ott.txt");
   ofstream outputx;
   outputx.open ("x_ott.txt");

   xn=1;
   mu=0.771312;
   sigma=0.620721;
   outputx<<xn<<endl;
   
   double sum;
   for(int i=0;i<N;i++){
     sum=0;
     for(int j=0;j<L;j++){
       xn1=rnd.Rannyu(xn-delta,xn+delta);
       tot+=1;
       c=prob(xn1)/prob(xn);
       if(c<=1)
	 A=c;
       else
	 A=1;
       r=rnd.Rannyu();
       if(r<=A){
	 xn=xn1;
	 acc+=1;
	 //if(acc%100 == 0)
	 outputx<<xn<<endl;
	 sum+=ValH(xn);
       }
       else
	 sum+=ValH(xn);
     }
     ave[i]=sum/L;
     av2[i]=pow(ave[i],2);
   }
   for(int i=0;i<N;i++){
     for(int j=0;j<i+1;j++){
	sum_prog[i]+=ave[j];
	su2_prog[i]+=av2[j];
      }
      sum_prog[i]/=(i+1);
      output1<<sum_prog[i]<<endl;
      su2_prog[i]/=(i+1);
      output2<<error(sum_prog,su2_prog,i)<<endl;
    }

    cout<<(double)acc/tot<<endl;
     
   
     

   output1.close();
   output2.close();
   outputx.close();

   
     
   
    

   return 0;
}
