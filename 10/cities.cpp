/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <iostream>
#include "random.h"
#include "cities.h"

using namespace std;

City :: City(double a, double b){
  x=a;
  y=b;
  z=0;
}
// Constructor (quadrato lato 1)

City :: City(double a){
  x=cos(a);
  y=sin(a);
  z=0;  
}
// Constructor (cerchio raggio 1), a=rnd.Rannyu(0,2*pi)

City :: ~City(){}
// Default destructor, does not perform any action



/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
