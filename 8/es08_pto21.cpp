#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "es08.h"
#include <cmath>
using namespace std;

double error(double AV,double AV2,int n){
  if (n==0)
    return 0;
  else{
    return sqrt((AV2 - AV*AV)/n);
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

std::pair<double , double > HBlocchi(double xn){
  for(int i=0;i<N;i++){
	   sum=0;
	   ave[i]=0;
	   av2[i]=0;
	   acc=0;
	   tot=0;
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
	       sum+=ValH(xn);
	     }
	     else
	       sum+=ValH(xn);
	   }
	   ave[i]=sum/L;
	   av2[i]=pow(ave[i],2);
	 }
	 for(int i=0;i<N;i++){
	   sum_prog=0;
	   su2_prog=0;
	   for(int j=0;j<i+1;j++){
	     sum_prog+=ave[j];
	     su2_prog+=av2[j];
	   }
	 }
	   sum_prog/=N;
	   su2_prog/=N;
	   //cout<<(double)acc/tot<<endl;
	 return std::make_pair(sum_prog, su2_prog);
}
  
 
int main (int argc, char *argv[]){

 
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

   
   
   

   ofstream output;
   output.open ("Ris.txt");
   //output<<"b"<<" "<<"H"<<" "<<"e"<<" "<<"m"<<" "<<"s"<<endl;

   xn=1;
   mu=1;
   sigma=0.5;
   std::pair<double ,double > v = HBlocchi(xn);
   H=v.first;
  
   for(int k=0;k<betamax;k++){
     beta=k+1;
     for(int i=0;i<n;i++){
       sum2=0;
       Hm[i]=0;
       H2m[i]=0;
       for(int j=0;j<l;j++){
	 dmu=rnd.Rannyu(-deltamu,deltamu);
	 dsigma=rnd.Rannyu(-deltasigma,deltasigma);
	 mu+=dmu;
	 sigma+=dsigma;
	 std::pair<double ,double > p = HBlocchi(xn); 
	 H1=p.first;
	 tot2+=1;
	 q=exp(-beta*(H1-H));
	 if(q<=1)
	   a=q;
	 else
	   a=1;
	 r=rnd.Rannyu();
	 if(r<=a){
	   H=H1;
	   acc2+=1;
	   sum2+=H;
	 }
	 else{
	   mu-=dmu;
	   sigma-=dsigma;
	   sum2+=H;
	 }
       }
       Hm[i]=sum2/l;
       H2m[i]=pow(Hm[i],2);
     }
     for(int i=0;i<n;i++){
       H_prog=0;
       H2_prog=0;
       for(int j=0;j<i+1;j++){
	 H_prog+=Hm[j];
	 H2_prog+=H2m[j];
       }
     }

     H_prog/=n;
     H2_prog/=n;
     output<<beta<<" "<<H_prog<<" "<<error(H_prog,H2_prog,n)<<" "<<mu<<" "<<sigma<<endl;
   
   }
   
     cout<<acc2/tot2<<endl;
     cout<<acc2<<endl;
     cout<<tot2<<endl;
    
       
       
      

   output.close();

   
     
   
    

   return 0;
}
