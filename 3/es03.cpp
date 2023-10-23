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

double N(double x){
  return 0.5*(1.+erf(x/sqrt(2.)));
}
 
int main (int argc, char *argv[]){

 

   
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

   // ESERCIZIO 03.1
   // Punto 1: calcolo direttamente S(T)

   int M=10000; 
   int N=100;
   int L=(M/N);

   double S_0=100,T=1,K=100,r=0.1,vol=0.25,S_T;
   double W;
   double sumC,sumP,C,P;
   double* C_N= new double[N]{0};
   double* C_N2= new double[N]{0};
   double* P_N= new double[N]{0};
   double* P_N2= new double[N]{0};
   
   for(int i=0;i<N;i++){
     sumC=0;
     sumP=0;
     for(int j=0;j<L;j++){
       W=rnd.Gauss(0,1);                // gaussiana con mu=0, sigma=1
       S_T= S_0*exp((r-pow(vol,2)/2)*T+vol*W);   // mu=r
       // cout<<S_T<<endl;
       if(S_T-K>0){
	 C=exp(-r*T)*(S_T-K);
	 sumC+=C;
       }
       else{
	 P=-exp(-r*T)*(S_T-K);
	 sumP+=P;
       }
     }
     C_N[i]=sumC/L;
     C_N2[i]=pow(C_N[i],2);
     P_N[i]=sumP/L;
     P_N2[i]=pow(P_N[i],2);
   }

   double* sum_prog1= new double[N]{0};
   double* su2_prog1= new double[N]{0};
   double* sum_prog2= new double[N]{0};
   double* su2_prog2= new double[N]{0};

   ofstream output1;
   output1.open ("C_N_prog1.txt");
   ofstream output2;
   output2.open ("C_N_err_prog1.txt");
   ofstream output3;
   output3.open ("P_N_prog1.txt");
   ofstream output4;
   output4.open ("P_N_err_prog1.txt");

    for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	sum_prog1[i]+=C_N[j];
	su2_prog1[i]+=C_N2[j];
	sum_prog2[i]+=P_N[j];
	su2_prog2[i]+=P_N2[j];
      }
      sum_prog1[i]/=(i+1);
      output1<<sum_prog1[i]<<endl;
      su2_prog1[i]/=(i+1);
      output2<<error(sum_prog1,su2_prog1,i)<<endl;
      sum_prog2[i]/=(i+1);
      output3<<sum_prog2[i]<<endl;
      su2_prog2[i]/=(i+1);
      output4<<error(sum_prog2,su2_prog2,i)<<endl;
    }
    output1.close();
    output2.close();
    output3.close();
    output4.close();
    
   
		
   // Punto 2: calcolo discretizzato dividendo l'intervallo di tempo T
   // in 100 sottointervalli uguali	    

   
   double S2_T,Z_tot;
   double sumC2,sumP2,C2,P2;
   double* C2_N= new double[N]{0};
   double* C2_N2= new double[N]{0};
   double* P2_N= new double[N]{0};
   double* P2_N2= new double[N]{0};

   for(int i=0;i<N;i++){
     sumC2=0;
     sumP2=0;
    
     for(int j=0;j<L;j++){
       Z_tot=0;
       for(int k=0;k<100;k++)
	 Z_tot+=rnd.Gauss(0,1);                  // gaussiana con mu=0, sigma=1
       S2_T= S_0*exp((r-pow(vol,2)/2)*T+vol*Z_tot*pow(T/100,0.5));   // mu=r
       //cout<<S2_T<<endl;
       if(S2_T-K>0){
	 C2=exp(-r*T)*(S2_T-K);
	 sumC2+=C2;
       }
       else{
	 P2=-exp(-r*T)*(S2_T-K);
	 sumP2+=P2;
       }
     }
     C2_N[i]=sumC2/L;
     C2_N2[i]=pow(C2_N[i],2);
     P2_N[i]=sumP2/L;
     P2_N2[i]=pow(P2_N[i],2);
   }

   double* sum_prog12= new double[N]{0};
   double* su2_prog12= new double[N]{0};
   double* sum_prog22= new double[N]{0};
   double* su2_prog22= new double[N]{0};

   ofstream output5;
   output5.open ("C_N2_prog1.txt");
   ofstream output6;
   output6.open ("C_N2_err_prog1.txt");
   ofstream output7;
   output7.open ("P_N2_prog1.txt");
   ofstream output8;
   output8.open ("P_N2_err_prog1.txt");

    for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	sum_prog12[i]+=C2_N[j];
	su2_prog12[i]+=C2_N2[j];
	sum_prog22[i]+=P2_N[j];
	su2_prog22[i]+=P2_N2[j];
      }
      sum_prog12[i]/=(i+1);
      output5<<sum_prog12[i]<<endl;
      su2_prog12[i]/=(i+1);
      output6<<error(sum_prog12,su2_prog12,i)<<endl;
      sum_prog22[i]/=(i+1);
      output7<<sum_prog22[i]<<endl;
      su2_prog22[i]/=(i+1);
      output8<<error(sum_prog22,su2_prog22,i)<<endl;
    }
    output5.close();
    output6.close();
    output7.close();
    output8.close();
    

   return 0;
}
