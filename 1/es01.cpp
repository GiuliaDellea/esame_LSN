
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

   // ESERCIZIO 01.1
   // punti 1 & 2
   
   int M=100000;    // Numero lanci
   int N=100;       // Numero blocchi
   int L=(M/N);     // Numero lanci per blocco (M multiplo di N)

   double* ave1= new double[N]{0};
   double* av21= new double[N]{0};
   double* ave2= new double[N]{0}; 
   double* av22= new double[N]{0};
   double sum1,sum2;
   double r;

   for(int i=0;i<N;i++){
    sum1=0;
    sum2=0;
    for(int j=0;j<L;j++){
      r=rnd.Rannyu();
      sum1+=r;
      sum2+=pow((r-0.5),2);
      // rnd.SaveSeed(); 
    }
    ave1[i]=sum1/L;
    av21[i]=pow(ave1[i],2);
    ave2[i]=sum2/L;
    av22[i]=pow(ave2[i],2);
   }

   double* sum_prog1= new double[N]{0};
   double* su2_prog1= new double[N]{0};
   double* sum_prog2= new double[N]{0};
   double* su2_prog2= new double[N]{0};

   ofstream output1;
   output1.open ("sum_prog1.txt");
   ofstream output2;
   output2.open ("err_prog1.txt");
   ofstream output3;
   output3.open ("sum_prog2.txt");
   ofstream output4;
   output4.open ("err_prog2.txt");

    for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	sum_prog1[i]+=ave1[j];
	su2_prog1[i]+=av21[j];
	sum_prog2[i]+=ave2[j];
	su2_prog2[i]+=av22[j];
      }
      sum_prog1[i]/=(i+1);                         // Media cumulativa
      output1<<sum_prog1[i]<<endl;
      su2_prog1[i]/=(i+1);                         // Media cumulativa quadrati
      output2<<error(sum_prog1,su2_prog1,i)<<endl; // Incertezza statistica
      sum_prog2[i]/=(i+1);
      output3<<sum_prog2[i]<<endl;
      su2_prog2[i]/=(i+1);
      output4<<error(sum_prog2,su2_prog2,i)<<endl;
    }
    output1.close();
    output2.close();
    output3.close();
    output4.close();

    // punto 3 

    int m=100;                      // Sotto-intervalli
    double l=100;                   // Sotto-intervalli (per divisione)
    int n=10000;                    // Numeri casuali
    double* oss= new double[m]{0};
    double sum3;

    ofstream output5;
    output5.open ("chi2.txt");

    for(int k=0;k<100;k++){
    
      for (int i=0;i<n;i++){
	r=rnd.Rannyu();
	for(int j=0;j<m;j++){
	  if (r>=j/l && r<(j+1)/l)
	    oss[j]+=1;
	}
	//rnd.SaveSeed();
      }
      sum3=0;	

      for(int j=0;j<m;j++){
	sum3+=pow(oss[j]-n/m,2);
	oss[j]=0;
      }
  
      output5<<sum3/(n/m)<<endl;
    }
    output5.close();


   
    /*ofstream output6;
    ofstream output7;
    output6.open("xdata.txt");
    output7.open("ydata.txt");
    int a= 35;
    int b= 165;
    int nbins=50;
    double n_bins= 50;
    double var;
    int* ydata= new int[nbins]{0};
    
    ifstream input2;
    input2.open("chi2.txt");
    for(int i=0;i<m;i++){
      input2>>var;
      // cout<<var<<endl;
      for(int j=0;j<nbins;j++){
	if (var>=a+j*(b-a)/n_bins && var<a+(j+1)*(b-a)/n_bins)
	    ydata[j]+=1;
      }
    }
    
    input2.close();
    int tot1=0;
    for(int i=0;i<nbins;i++){
      output6<<((a+i*(b-a)/n_bins)+(a+(i+1)*(b-a)/n_bins))/2<<endl;
      output7<<ydata[i]<<endl;
      tot1+=ydata[i];
    }
    // cout<<tot<<endl;
    output6.close();
    output7.close();*/

    //ESERCIZIO 01.2

    //STANDARD DICE

    int num=1;
    double Snums=0, Snume=0, Snumcl=0;

    ofstream output10;
    output10.open ("N=1.txt");

    for(int k=0;k<10000;k++){
    
      for (int i=0;i<num;i++){
	Snums+=rnd.Rannyu();
	Snume+=rnd.Exponential(1.);
	Snumcl+=rnd.Cauchy_Lorentz(0.,1.);
      }
      output10<<(double)Snums/num<<" "<<(double)Snume/num<<" "<<(double)Snumcl/num<<endl;
      Snums=0;
      Snume=0;
      Snumcl=0;
    }
      
    output10.close();

    num=2;

    ofstream output11;
    output11.open ("N=2.txt");

    for(int k=0;k<10000;k++){
    
      for (int i=0;i<num;i++){
	Snums+=rnd.Rannyu();
	Snume+=rnd.Exponential(1.);
	Snumcl+=rnd.Cauchy_Lorentz(0.,1.);
      }
      output11<<(double)Snums/num<<" "<<(double)Snume/num<<" "<<(double)Snumcl/num<<endl;
      Snums=0;
      Snume=0;
      Snumcl=0;
    }
      
    output11.close();

    num=10;

    ofstream output12;
    output12.open ("N=10.txt");

    for(int k=0;k<10000;k++){
    
      for (int i=0;i<num;i++){
	Snums+=rnd.Rannyu();
	Snume+=rnd.Exponential(1.);
	Snumcl+=rnd.Cauchy_Lorentz(0.,1.);
      }
      output12<<(double)Snums/num<<" "<<(double)Snume/num<<" "<<(double)Snumcl/num<<endl;
      Snums=0;
      Snume=0;
      Snumcl=0;
    }
      
    output12.close();

    num=100;

    ofstream output13;
    output13.open ("N=100.txt");

    for(int k=0;k<10000;k++){
    
      for (int i=0;i<num;i++){
	Snums+=rnd.Rannyu();
	Snume+=rnd.Exponential(1.);
	Snumcl+=rnd.Cauchy_Lorentz(0.,1.);
      }
      output13<<(double)Snums/num<<" "<<(double)Snume/num<<" "<<(double)Snumcl/num<<endl;
      Snums=0;
      Snume=0;
      Snumcl=0;
    }
      
    output13.close();



    



    //ESERCIZIO 01.3 "Buffon's experiment"

    // Calcolo pigreco con metodo accept-reject

    double c,d,tot2=0,fav=0,pigreco;
    
    for(int i=0;i<10000000;i++){
      c=rnd.Rannyu();
      d=rnd.Rannyu();
      if((c*c+d*d)<1)
	fav+=1;
      tot2+=1;
    }
    pigreco=4*fav/tot2;
    cout<<pigreco<<endl;

    double s=2;           // Lunghezza sbarra
    double D=2.2;         // Distanza linee
    double X;             // Distanza centro barra dalla linea più vicina
    double THETA;         // Angolo inclinazione barra rispetto all'orizzontale

    double* ave3= new double[N]{0}; 
    double* av23= new double[N]{0};
    double intersez;

    for(int i=0;i<N;i++){
      intersez=0;
      for(int j=0;j<L;j++){
	X=rnd.Rannyu(0.,D/2);
	THETA=rnd.Rannyu(0.,pigreco/2);
	if(X<=cos(THETA)*s/2)
	  intersez+=1;
      }
      //cout<<intersez<<endl;
      //cout<<(2*s*L/(D*intersez))<<endl;
      ave3[i]=2*s*L/(D*intersez);
      av23[i]=pow(ave3[i],2);
    }


   double* sum_prog3= new double[N]{0};
   double* su2_prog3= new double[N]{0};

   ofstream output8;
   output8.open ("sum_prog3.txt");
   ofstream output9;
   output9.open ("err_prog3.txt");

    for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	sum_prog3[i]+=ave3[j];
	su2_prog3[i]+=av23[j];
      }
      sum_prog3[i]/=(i+1);                         // Media cumulativa
      output8<<sum_prog3[i]<<endl;
      su2_prog3[i]/=(i+1);                         // Media cumulativa quadrati
      output9<<error(sum_prog3,su2_prog3,i)<<endl; // Incertezza statistica
    }
    output8.close();
    output9.close();
     
    
    

       
    

   return 0;
}
