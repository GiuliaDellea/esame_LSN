/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
Random rnd;

int M=1e5;    //tot passi posiz
int N=100;     //blocchi
int L=(M/N);  //passi per blocco
double xn,xn1;
int beta=1, betamax=200,stepb=50,n=5,l=stepb/n;
double delta=1.4;
double r,c,A;
int tot=0, acc=0;
double* ave= new double[N]{0}; //valori H N blocchi
double* av2= new double[N]{0};
double sum_prog=0,su2_prog=0;
double* Hm= new double[n]{0}; //valori H b step a T fissa (come ave)
double* H2m= new double[n]{0};
double H_prog=0,H2_prog=0;

double H=0,H1;
double q,a;
double tot2=0,acc2=0;
double sum,sum2;
double mu,sigma;
double dmu,dsigma,deltamu=0.3,deltasigma=0.3;
double error(double,double,int );
double prob(double);
double ValH(double);
std::pair<double, double > HBlocchi(double);



/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
