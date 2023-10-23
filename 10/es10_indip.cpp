#include "mpi.h"
#include <iostream>
#include <fstream>
#include <string>
#define col 50
#define rig col*col
#define dim1 2
#include "es10.h"
#include "random.h"
#include <cmath>
using namespace std;


  
int main (int argc, char *argv[]){

  int size, rank;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Request req;

  if(size%2!=0){
    cout<<"Il numero di nodi deve essere pari"<<endl;
    return -1;
  }
  
  double tstart = MPI_Wtime();
  
  //cout<<"Nodo "<<rank<<" dei "<<size<<" generati"<<endl;

  int l=50; //numero città
  int N=l*l; //numero individui popolazione

    
  Random rnd;
  int seed[4];
  int p1, p2;
  ifstream Primes("Primes");
  if (Primes.is_open()){
    for(int i=0;i<=rank;i++)
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

   

  //GENERAZIONE POPOLAZIONE INIZIALE

  double* num = new double[l-1]{0};
  int cont=0, posto;
  double popol[rig][col+1]; //una colonna in più dove metto i pesi, col=l, rig=N

  for(int i=2;i<l+1;i++)
    num[i-2]=i;  

  for(int k=0;k<N;k++){
    popol[k][0]=1;
     
    for(int i=1;i<l;i++){
      posto=(int)rnd.Rannyu(0,l-i);
      popol[k][i]=num[posto];
      Swap(num[posto],num[l-i-1]);
    }
    cont+=1;
  }
  //cout<<cont<<endl;

  
  //GENERAZIONE CITTA'

  ifstream input1;
  input1.open("American_capitals.dat");
  int nc=0;
  double cities[col][dim1]; //2D
  double var1, var2;

  for(int k=0;k<l;k++){
    input1>>var1>>var2;
    cities[k][0]=var1;
    cities[k][1]=var2;
    nc+=1;
  }

  //cout<<"nc"<<" "<<nc<<endl;

  input1.close();
	 
  //CALCOLO PESI

  double* A = new double[2]{0};
  double* B = new double[2]{0};
  double D=0;
  int indice1, indice2;

  for(int k=0;k<N;k++){
    D=0;
    for(int i=0;i<l-1;i++){
      indice1=(int)(popol[k][i]);
      indice2=(int)(popol[k][i+1]);
      for(int d=0;d<2;d++){	 
	A[d]=cities[indice2-1][d];
	B[d]=cities[indice1-1][d];
      }
      D+=dist(A,B);
    }
    indice1=(int)(popol[k][l-1]);
    indice2=(int)(popol[k][0]);
    for(int d=0;d<2;d++){
      A[d]=cities[indice2-1][d];
      B[d]=cities[indice1-1][d];
    }
    D+=dist(A,B);
    popol[k][l]=D;
  }
      
  bubbleSort(popol);
  
  /*cout<<"Best path della popolazione iniziale:"<<endl;
  for(int i=0;i<l+1;i++)
    cout<<popol[0][i]<<" ";
    cout<<endl;*/
   
  //SIMULAZIONE

  ofstream output1;
  output1.open("p1" + to_string(rank) + ".txt", ios::app);
  ofstream output2;
  output2.open("p2" + to_string(rank) + ".txt", ios::app);
  ofstream output3;
  output3.open("p3" + to_string(rank) + ".txt", ios::app);

  double Newpopol[rig][col+1];
  double sum=0;
  int seq1,seq2,sbagliati=0,generati=0,run=200,totsi=0,totno=0,var,cit;
  double* app1=new double[l+1]{};
  double* app2=new double[l+1]{};

  //produzione numeri casuali per PermutationM
  int i1,i2,m,tot=0,scambi=0;

  for(int h=0;h<run;h++){
    tot+=1;
    generati=0;
    sbagliati=0;
    totsi=0;
    totno=0;
    sum=0;
    for(int i=0;i<N;i+=2){
      seq1=Selection(rnd.Rannyu(),N);
      for(int j=0;j<l+1;j++){
	app1[j]=popol[seq1][j];
      }
      seq2=Selection(rnd.Rannyu(),N);
      for(int j=0;j<l+1;j++){
	app2[j]=popol[seq2][j];
      }

      //Crossover

      var=Crossover(app1,app2,l,rnd.Rannyu(2,l-1),rnd.Rannyu());
      if(check(app1,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app1[j]=popol[seq1][j];
      }
      if(check(app2,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app2[j]=popol[seq2][j];
      }
      if(var==1)
	totsi+=1;
      else
	totno+=1;

      //Permutation1
     
      Permutation1(app1,l,rnd.Rannyu(1,l),rnd.Rannyu(1,l),rnd.Rannyu());
      if(check(app1,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app1[j]=popol[seq1][j];
      }       
      Permutation1(app2,l,rnd.Rannyu(1,l),rnd.Rannyu(1,l),rnd.Rannyu());
      if(check(app2,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app2[j]=popol[seq2][j];
      }

      //Shift

      Shift(app1,l,rnd.Rannyu(0,l-1),rnd.Rannyu(1,l-1),rnd.Rannyu(1,l-1),rnd.Rannyu());
      if(check(app1,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app1[j]=popol[seq1][j];
      }
      Shift(app2,l,rnd.Rannyu(0,l-1),rnd.Rannyu(1,l-1),rnd.Rannyu(1,l-1),rnd.Rannyu());
      if(check(app2,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app2[j]=popol[seq2][j];
      } 
     
      //PermutationM
     
      i1=rnd.Rannyu(0,l-1);
      m=rnd.Rannyu(1,(l-1)/2.);
      do{
	i2=rnd.Rannyu(0,l-1);
      }while(((i2+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) || ((i2+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1) && (i2+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) || (((i2+m-1+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1))));
      PermutationM(app1,l,i1,i2,m,rnd.Rannyu());
      if(check(app1,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app1[j]=popol[seq1][j];
      }
      i1=rnd.Rannyu(0,l-1);
      m=rnd.Rannyu(1,(l-1)/2.);
      do{
	i2=rnd.Rannyu(0,l-1);
      }while(((i2+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) || ((i2+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1) && (i2+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1)) || (((i2+m-1+l-1-i1)%(l-1)>=(i1+l-1-i1)%(l-1)) && ((i2+m-1+l-1-i1)%(l-1)<=(i1+m-1+l-1-i1)%(l-1))));
      PermutationM(app2,l,i1,i2,m,rnd.Rannyu());
      if(check(app2,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app2[j]=popol[seq2][j];
      }

      //Inversion

      Inversion(app1,l,rnd.Rannyu(0,l-1),rnd.Rannyu(2,l),rnd.Rannyu());
      if(check(app1,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app1[j]=popol[seq1][j];
      }
      Inversion(app2,l,rnd.Rannyu(0,l-1),rnd.Rannyu(2,l),rnd.Rannyu());
      if(check(app2,l)!=1){
	sbagliati+=1;
	for(int j=0;j<l+1;j++)
	  app2[j]=popol[seq2][j];
      }

      CalcolaPeso(app1,l,cities);
      CalcolaPeso(app2,l,cities);

      for(int j=0;j<l+1;j++){
	Newpopol[i][j]=app1[j];
	Newpopol[i+1][j]=app2[j];
      }
      generati+=2;
    }
    if(N%2!=0){
      for(int j=0;j<l+1;j++)
	Newpopol[N-1][j]=popol[0][j]; //essendo N dispari, metto come sequenza spaiata la migliore della popolazione precedente
      generati+=1;
    }     

    bubbleSort(Newpopol);
     
    output1<<Newpopol[0][l]<<endl;

    for(int k=0;k<N/2;k++)
      sum+=Newpopol[k][l];
    output2<<sum/(N/2)<<endl;

    /*cout<<"Generati:"<<generati<<endl;
      cout<<"Sbagliati:"<<sbagliati<<endl;
      cout<<"Sì crossover:"<<totsi<<endl;
      cout<<"No crossover:"<<totno<<endl;
      cout<<endl;*/

    for(int k=0;k<N;k++){
      for(int i=0;i<l+1;i++)
	popol[k][i]=Newpopol[k][i];
    }
  } 

  cout<<"Run eseguite:"<<tot<<endl;
  cout<<"Scambi: "<<scambi<<endl;
  cout<<"Best path della popolazione finale:"<<endl;
  for(int i=0;i<l+1;i++)
    cout<<Newpopol[0][i]<<" ";
  cout<<endl;

  for(int i=0;i<l;i++){
    cit=(int)(Newpopol[0][i]);
    for(int d=0;d<2;d++)	
      output3<<cities[cit-1][d]<<" ";
    output3<<endl;
  }
  for(int d=0;d<2;d++)	
    output3<<cities[0][d]<<" ";
  output3<<endl;
     
   
  output1.close();
  output2.close();
  output3.close();  
     
  //La soluzione è la sequenza alla prima riga (dopo aver riordinato) della nuova popolazione (o dell'ultima nuova popolazione se ho fatto più run)
  //Se cambio l, devo cambiare anche le costanti che ho definito (col,...)
     
   
  double tend = MPI_Wtime();
  double dt = tend - tstart;

  cout<<"rank:"<<rank<<", tempo ="<<dt<<endl;

   

  MPI_Finalize();
       

    return 0;
}
