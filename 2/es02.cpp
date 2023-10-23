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

double dist(double A1[],double A2[],int n){
  if (n==0)
    return 0;
  else{
    double sum=0;
     for(int i=0;i<n;i++)
       sum+=pow(A1[i]-A2[i],2);
 return sqrt(sum);
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


   // ESERCIZIO 02.1
   // punto 1 (distribuzione uniforme) & 2 (importance sampling)

   int M=10000; 
   int N=100;
   int L=(M/N);
  
   
   double r;
   double sum1;
   double* I_N1= new double[N]{0};
   double* I_N21= new double[N]{0};

   for(int i=0;i<N;i++){
     sum1=0;
     for(int j=0;j<L;j++){
       r=rnd.Rannyu();
       sum1+=M_PI/2*cos(M_PI*r/2);
       //rnd.SaveSeed();
     }
     I_N1[i]=sum1/L;
     I_N21[i]=pow(I_N1[i],2);
     }

   
   double x;
   double sum2;
   double* I_N2= new double[N]{0};
   double* I_N22= new double[N]{0};
  
   for(int i=0;i<N;i++){
     sum2=0;
     for(int j=0;j<L;j++){
       r=rnd.Rannyu();
       x=1-sqrt(1-r);
       sum2+=M_PI/2*cos(M_PI*x/2)/(2*(1-x));
       //rnd.SaveSeed();
     }
     I_N2[i]=sum2/L;
     I_N22[i]=pow(I_N2[i],2);
    }


   double* I_N1_prog= new double[N]{0};
   double* I_N21_prog= new double[N]{0};
   double* I_N2_prog= new double[N]{0};
   double* I_N22_prog= new double[N]{0};
  

   ofstream output1;
   output1.open ("I_N_prog1.txt");
   ofstream output2;
   output2.open ("I_N_err_prog1.txt");
   ofstream output3;
   output3.open ("I_N_prog2.txt");
   ofstream output4;
   output4.open ("I_N_err_prog2.txt");
  

   for(int i=0;i<N;i++){
      for(int j=0;j<i+1;j++){
	I_N1_prog[i]+=I_N1[j];
	I_N21_prog[i]+=I_N21[j];
	I_N2_prog[i]+=I_N2[j];
	I_N22_prog[i]+=I_N22[j];
      }
      I_N1_prog[i]/=(i+1);
      output1<<I_N1_prog[i]<<endl;
      I_N21_prog[i]/=(i+1);
      output2<<error(I_N1_prog,I_N21_prog,i)<<endl;
      I_N2_prog[i]/=(i+1);
      output3<<I_N2_prog[i]<<endl;
      I_N22_prog[i]/=(i+1);
      output4<<error(I_N2_prog,I_N22_prog,i)<<endl;
    }
    output1.close();
    output2.close();
    output3.close();
    output4.close();
  
    // ESERCIZIO 02.2
    // Punto 1: 3D RW su reticolo cubico (a=1), ogni step è un passo
    // in una delle 3 direzioni principali x,y,z di lunghezza a.

    int nrw=10000;              // Numero RW generati
    int passi=100;              // Numero passi di ogni RW
    int blocchi=100;            // Numero blocchi in cui si dividono gli nrw RWs
    int h=nrw/blocchi;          // Numero RWs per blocco
    double a=1;                 // Passo reticolare

    double* sum_i = new double[passi]{0}; // Ogni componente è la somma delle distanze dall'O degli h RWs di un singolo blocco
    
    double* sum_blocchi_i = new double[passi]{0}; // Ogni componente è la somma dei valori medi delle distanze dall'O dei vari blocchi per ciascuno step i
    
     double* sum2_blocchi_i = new double[passi]{0}; // Valori medi quadrati delle distanze dall'O dei vari blocchi ad ogni step i 
     
    int dim=3;                                 // Dimensione
    double* O = new double[dim]{0};            // Origine
    double* posiz = new double[dim]{0};        // Posizione generica

    // ofstream output5;
    // output5.open ("sum_blocchi.txt");

    for(int i=0;i<blocchi;i++){
      for(int j=0;j<h;j++){
	for(int l=0;l<passi;l++){
	  r = rnd.Rannyu();
	  if(r<=1./6)
	    posiz[0]+=a;
	  if(1./6<r && r<=2./6)
	    posiz[0]-=a;
	  if(2./6<r && r<=3./6)
	    posiz[1]+=a;
	  if(3./6<r && r<=4./6)
	    posiz[1]-=a;
	  if(4./6<r && r<=5./6)
	    posiz[2]+=a;
	  if(5./6<r && r<=6./6)
	    posiz[2]-=a;
	  sum_i[l]+=dist(O,posiz,dim);
	}
	for(int k=0;k<dim;k++)
	  posiz[k]=0;
      }
	 
      //output5<<"Blocco "<<i+1<<endl;
      for(int p=0;p<h;p++){
	sum_blocchi_i[p]+=sum_i[p]/h;
	sum2_blocchi_i[p]+=pow(sum_i[p]/h,2);
        //output5<<sum_i[p]/h<<endl;
	sum_i[p]=0;
      }
    }

    /*output5.close();

    double var;
    ifstream input1;*/
    ofstream output6;
    output6.open ("media_blocchi1.txt");
    ofstream output8;
    output8.open ("errore_blocchi1.txt");
    /* input1.open("sum_blocchi.txt");
    for(int j=0;j<nrw;j++){
      input1>>var;
      sum_prog_i[j%100]+=var;
      }*/
    
    

    for(int p=0;p<h;p++){
      sum_blocchi_i[p]/=blocchi;
      sum2_blocchi_i[p]/=blocchi;
      output6<<sum_blocchi_i[p]<<endl;
      output8<<error(sum_blocchi_i,sum2_blocchi_i,p)<<endl;
    }
      

      
    
    //input1.close();
    output6.close();
    output8.close();


    // Punto 2: 3D RW, ogni step è un passo di lunghezza a=1
    // in direzione generica con theta in 0-pigreco e phi in 0-2*pigreco

    double theta, phi;

     double* sum_i2 = new double[passi]{0}; // Ogni componente è la somma delle distanze dall'O degli h RWs di un singolo blocco
    
    double* sum_blocchi_i2 = new double[passi]{0}; // Ogni componente è la somma dei valori medi delle distanze dall'O dei vari blocchi per ciascuno step i
    
     double* sum2_blocchi_i2 = new double[passi]{0}; // Valori medi quadrati delle distanze dall'O dei vari blocchi ad ogni step i 

    for(int k=0;k<dim;k++)
      posiz[k]=0;
    
    
    for(int i=0;i<blocchi;i++){
      for(int j=0;j<h;j++){
	for(int l=0;l<passi;l++){
	  theta = rnd.Rannyu(0.,M_PI);
	  phi = rnd.Rannyu(0.,2*M_PI);
	  posiz[0]+=a*sin(theta)*cos(phi);
	  posiz[1]+=a*sin(theta)*sin(phi);
	  posiz[2]+=a*cos(theta);
	  sum_i2[l]+=dist(O,posiz,dim);
	}
       	for(int k=0;k<dim;k++)
	  posiz[k]=0;
      }
      
    
	 
      //output5<<"Blocco "<<i+1<<endl;
      for(int p=0;p<h;p++){
	sum_blocchi_i2[p]+=sum_i2[p]/h;
	sum2_blocchi_i2[p]+=pow(sum_i2[p]/h,2);
        //output5<<sum_i[p]/h<<endl;
	sum_i2[p]=0;
      }
    }

    // output5.close();
    

    /*double var;
    ifstream input1;*/
    ofstream output7;
    output7.open ("media_blocchi2.txt");
    ofstream output9;
    output9.open ("errore_blocchi2.txt");
    /* input1.open("sum_blocchi.txt");
    for(int j=0;j<nrw;j++){
      input1>>var;
      sum_prog_i[j%100]+=var;
      }*/
    
    

    for(int p=0;p<h;p++){
      sum_blocchi_i2[p]/=blocchi;
      sum2_blocchi_i2[p]/=blocchi;
      output7<<sum_blocchi_i2[p]<<endl;
      output9<<error(sum_blocchi_i2,sum2_blocchi_i2,p)<<endl;
      //output7<<sum_i[p]<<endl;
    }
      
    
    //input1.close();
    output7.close();
    output9.close();
       
    
          

   return 0;
}
