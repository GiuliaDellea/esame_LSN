#include <iostream>
#include <fstream>
#include <string>
#define col 34
#define rig col*col
#define dim2 2
#define pm 0.08
#define pc 0.6
#include "random.h"
#include "cities.h"
#include <cmath>
using namespace std;


void Swap(double &v, double &n) {
  double k;
  k=v;
  v=n;
  n=k;
}

void bubbleSort(double* v, int n) {
  int scambio;
  do {
    scambio = 0;
    for (int i=0; i<n-1; i++) {
      if (v[i]>v[i+1]) {
	Swap(v[i],v[i+1]);
	scambio = 1;
      }
    }
  }while(scambio==1);
}

void bubbleSort(double v[][col+1]) {
  int scambio;
  int N=col*col;
  //cout<<N<<endl;
  double a=0;
  do {
    scambio = 0;
    for(int k=0;k<N-1;k++){
      //cout<<k<<endl;      
      //cout<<v[k][col]<<endl;
      //cout<<v[k+1][col]<<endl;
      if(v[k][col]>v[k+1][col]){
	//cout<<"uuuuuu"<<endl;
	for (int i=0; i<col+1; i++){
	  //cout<<i<<endl;
	  a=v[k][i];
	  //cout<<a<<endl;
	  v[k][i]=v[k+1][i];
	  //cout<<v[k][i]<<endl;
	  v[k+1][i]=a;
	  //cout<<v[k+1][i]<<endl;
	}
	scambio = 1;
      }
    }
  }while(scambio==1);
}

void bubbleSort2(int v[][dim2], int righe) {
  int scambio;
  int N=righe;
  //cout<<N<<endl;
  int a=0;
  do {
    scambio = 0;
    for(int k=0;k<N-1;k++){
      //cout<<k<<endl;      
      //cout<<v[k][col]<<endl;
      //cout<<v[k+1][col]<<endl;
      if(v[k][dim2-1]>v[k+1][dim2-1]){
	//cout<<"uuuuuu"<<endl;
	for (int i=0; i<dim2; i++){
	  //cout<<i<<endl;
	  a=v[k][i];
	  //cout<<a<<endl;
	  v[k][i]=v[k+1][i];
	  //cout<<v[k][i]<<endl;
	  v[k+1][i]=a;
	  //cout<<v[k+1][i]<<endl;
	}
	scambio = 1;
      }
    }
  }while(scambio==1);
}

double check (double* v, int n){
  double* a= new double[n]{0};
  double diff=0;
  for (int i=0;i<n;i++){
    a[i]=v[i];
    //cout<<a[i]<<" ";
  }
  //cout<<endl;
  bubbleSort(a,n);
  for (int i=0;i<n-1;i++){
    diff=a[i+1]-a[i];
    //cout<<diff<<endl;
    if(diff==0)
      break;
  }
    
  return diff;
}

double dist(double* A, double* B){
  return sqrt(pow((B[0]-A[0]),2)+pow((B[1]-A[1]),2)+pow((B[2]-A[2]),2));
}

int Selection(double r, int N){ //r numero casuale unif in [0,1)
  double esp=2;
  return (int)(N*pow(r,esp));
}

void Permutation1(double* v, int l,double r1, double r2, double r) { //r1,r2 numeri casuali in [0,l), r in [0,1)
 
  double a,k;
  int i1,i2;
  i1=(int)r1;
  i2=(int)r2;
  a=r;
  //cout<<i1<<" "<<i2<<" "<<a<<endl;
  //cout<<v[i1]<<" "<<v[i2]<<endl;
  if(a<pm){
    k=v[i1];
    v[i1]=v[i2];
    v[i2]=k;
  }
}

void Shift(double* v,int l, int r1, int r2, int r3, double r) { //r1 int in [0,l-2], r2 ed r3 int in [1,l-2], r double in [0,1)
 
  double a;
  a=r;
  if(a<pm){
    double* app=new double[l-1]{0};
    int indice, m,n;
    indice=r1;
    m=r2;
    n=r3;
    double* prova = new double [m]{0};
    //cout<<"indice:"<<indice<<" m:"<<m<<" n:"<<n<<" a:"<<a<<endl;
    for(int i=0;i<l-1;i++){
      app[i]=v[i+1];
      //cout<<app[i]<<" ";
    }
    //cout<<endl;
    
    for(int k=indice;k<=(indice+m-1);k++){
      //cout<<"k: "<<k<<endl;
      prova[(k-indice)%(l-1)]=app[k%(l-1)];
      //cout<<prova[(k-indice)%(l-1)]<<endl;
    }
    int* posti= new int[n]{0};
    int pos;
    for(int t=indice; t<=(indice+n-1); t++){
      posti[(t-indice)%(l-1)]=t%(l-1);
      //cout<<posti[(t-indice)%(l-1)]<<" ";
    }
    //cout<<endl;
    for(int k=(indice+m);k<=(indice+m-1+n);k++){
      pos=posti[(k-indice-m)%(l-1)];
      //cout<<"sposto chi sta in: "<<k%(l-1)<<endl;
      //cout<<"lo sposto in: "<<pos<<endl;
      app[pos]=app[k%(l-1)];
      //cout<<app[pos]<<endl;
    }

    for(int i=(indice+n); i<=(indice+m-1+n);i++){
      //cout<<"chi sposto: "<<prova[(i-indice-n)%(l-1)]<<endl;
      //cout<<"dove lo sposto: "<<i%(l-1)<<endl;
      app[i%(l-1)]=prova[(i-indice-n)%(l-1)];
      //cout<<app[i%(l-1)]<<endl;
    }

    for(int i=0;i<l-1;i++)
      v[i+1]=app[i];
  }
}


void PermutationM(double* v,int l, int r1, int r2, int r3, double r) { //r1 int in [0,l-2], r2 idem ma non nel range i1/i1+m-1, r3 int in [1,(l-1)/2], r double in [0,1)
 
  double a,k;
  int i1,i2,m;
  a=r;
  
  if(a<pm){
     i1=r1;
     i2=r2;
     m=r3;
     //cout<<"i1:"<<i1<<" "<<"i2:"<<i2<<" "<<"m:"<<m<<" "<<"a:"<<a<<endl;
     double* app=new double[l-1]{0};
     for(int i=0;i<l-1;i++){
       app[i]=v[i+1];
       //cout<<app[i]<<" ";
     }
     //cout<<endl;
     //for(int i=i1;i<=i1+m-1;i++)
       //cout<<app[i%(l-1)]<<" ";
       //cout<<endl;
     //for(int i=i2;i<=i2+m-1;i++)
       //cout<<app[i%(l-1)]<<" ";
       //cout<<endl;
     int* indici= new int[m]{0};
     int indice;
     for(int t=i2; t<=(i2+m-1); t++){
       indici[(t-i2)%(l-1)]=t%(l-1);
       //cout<<indici[(t-i2)%(l-1)]<<" ";
     }
     //cout<<endl;
    
     for(int i=i1;i<=i1+m-1;i++){
       indice=indici[(i-i1)%(l-1)];
       //cout<<"indice:"<<indice<<endl;
       //cout<<"app["<<indice<<"]="<<app[indice]<<endl;
       k=app[i%(l-1)];
       //cout<<"k:"<<k<<endl;
       app[i%(l-1)]=app[indice];
       //cout<<"app["<<i%(l-1)<<"]="<<app[i%(l-1)]<<endl;
       app[indice]=k;
       //cout<<"app["<<indice<<"]="<<app[indice]<<endl;
     }
     for(int i=0;i<l-1;i++)
       v[i+1]=app[i];
  }
}

void Inversion(double* v,int l, int r1, int r2, double r) { //r1 int in [0,l-2], r2 int in [2,l-1], r double in [0,1)
 
  double a,k;
  int indice,m;
  a=r;
  if(a<pm){
    //cout<<"non inverto"<<endl;
    // else{
    indice=r1;
    m=r2;
    //cout<<"indice:"<<indice<<" "<<"m:"<<m<<" "<<"a:"<<a<<endl;
    double* app=new double[l-1]{0};
    for(int i=0;i<l-1;i++){
      app[i]=v[i+1];
      //cout<<app[i]<<" ";
    }
    //cout<<endl;
    if(m%2==0){
      for(int i=0;i<m/2;i++){
	//cout<<i<<endl;
	k=app[(indice+i)%(l-1)];
	//cout<<"k:"<<k<<endl;
	app[(indice+i)%(l-1)]=app[(indice+m-1-i)%(l-1)];
	//cout<<"app["<<(indice+i)%(l-1)<<"]="<<app[(indice+i)%(l-1)]<<endl;
	app[(indice+m-1-i)%(l-1)]=k;
	//cout<<"app["<<(indice+m-1-i)%(l-1)<<"]="<<app[(indice+m-1-i)%(l-1)]<<endl;
      }
    }else{
      for(int i=0;i<1+m/2;i++){
	k=app[(indice+i)%(l-1)];
	//cout<<k<<endl;
	app[(indice+i)%(l-1)]=app[(indice+m-1-i)%(l-1)];
	//cout<<app[(indice+i)%(l-1)]<<endl;
	app[(indice+m-1-i)%(l-1)]=k;
	//cout<<app[(indice+m-1-i)%(l-1)]<<endl;
      }
    }
     
    for(int i=0;i<l-1;i++)
      v[i+1]=app[i];
  }
}
     
void CalcolaPeso(double* v, int l, double cities[][3]){
   double* A = new double[3]{0};
   double* B = new double[3]{0};
   double D=0;
   int indice1, indice2;

   for(int i=0;i<l-1;i++){
       indice1=(int)(v[i]);
       indice2=(int)(v[i+1]);
       //cout<<indice1<<" "<<indice2<<endl;
       for(int d=0;d<3;d++){	 
	 A[d]=cities[indice2-1][d];
	 //cout<<"A["<<d<<"]"<<" "<<A[d]<<endl;
	 B[d]=cities[indice1-1][d];
	 //cout<<"B["<<d<<"]"<<" "<<B[d]<<endl;
       }
       //cout<<dist(A,B)<<endl;
       D+=dist(A,B);
       //cout<<D<<endl;
     }
     indice1=(int)(v[l-1]);
     indice2=(int)(v[0]);
     //cout<<indice1<<" "<<indice2<<endl;
     for(int d=0;d<3;d++){
       A[d]=cities[indice2-1][d];
       //cout<<"A["<<d<<"]"<<" "<<A[d]<<endl;
       B[d]=cities[indice1-1][d];
       //cout<<"B["<<d<<"]"<<" "<<B[d]<<endl;
       }
     //cout<<dist(A,B)<<endl;
     D+=dist(A,B);
     v[l]=D;
     //cout<<D<<endl;
     //cout<<popol[k][l]<<endl;
}


int Crossover(double* seq1, double* seq2, int l, int r1, double r){ //r1 int in[2,l-1), è l'indice della prima casella dopo il taglio; r double in [0,1)
  int cut;
  double a;
  a=r;
  if(a<pc){
    //cout<<"sì crossover:"<<" "<<"a="<<a<<endl;
    //cout<<"cut:"<<r1<<endl;
    cut=r1;
    double* app1=new double[l-1]{0};
    double* app2=new double[l-1]{0};
    int mat1[l-cut][dim2];
    int mat2[l-cut][dim2];

    for(int i=0;i<l-1;i++){
      app1[i]=seq1[i+1];
      app2[i]=seq2[i+1];
    }
    
    for(int i=cut;i<=l-1;i++){
      for(int j=0;j<l;j++){
	if(seq1[i]==app2[j]){
	  mat1[i-cut][0]=app2[j];
	  mat1[i-cut][1]=j;
	}
	if(seq2[i]==app1[j]){
	  mat2[i-cut][0]=app1[j];
	  mat2[i-cut][1]=j;
	}
      }
    }
    bubbleSort2(mat1,l-cut);
    bubbleSort2(mat2,l-cut);

    for(int i=cut;i<=l-1;i++){
      seq1[i]=mat1[i-cut][0];
      seq2[i]=mat2[i-cut][0];
    }
    return 1;
  }else{
    //cout<<"no crossover:"<<" "<<"a="<<a<<endl;
    return 0;
  }
}
  
    
    
      
  

  
