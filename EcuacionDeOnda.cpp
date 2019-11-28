#include <iostream>
#include <fstream>
#include <cmath>
#include "stdio.h"

void init(double *psi, int n_x);
void print(double *psi, int n_x);
void copy(double *recibe, double *entrega, int n_x);
void evolve(double *psi_new, double *psi_old, double *psi_old2, double delta_t, double delta_x, int n_x);

int main(int argc, char **argv){
    
  double *psi = NULL;
  double *psi_past = NULL;
  double *psi_old2 = NULL;
  int n_x;
  int n_t;
  int n;
  int j;
  double t_max=1.0;
  double delta_t= 0.1/n_t;
  double delta_x = 1.0/100.0;
  double cc2 = (delta_x*delta_x)/(delta_t*delta_t);
  double tension = 40.0;
  double densidad = 1.0;
  double c2 = tension/densidad;

  n_x=atoi(argv[1]);
  n_t=atoi(argv[2]);
  
  psi  = new double [n_x];
  psi_past  = new double [n_x];
  psi_old2 = new double [n_x];

  init(psi_old2, n_x);
  init(psi, n_x);
    
  for(j=0;j<n_x;j++){
      
    psi_old2[j]= 10E-4 * sin(2*M_PI*j*delta_x);
  }

  for(j=1; j<n_x-1;j++){
	 
	psi[j] = psi_old2[j] + (c2/(2*cc2))*(psi_old2[j+1]+psi_old2[j-1] - 2*psi_old2[j]);
  }	
    
  print(psi_old2, n_x);
  print(psi,n_x);	
	
  
  for(n=1;n<n_t+1;n++){
      
    copy(psi_past, psi, n_x);
    evolve(psi, psi_past, psi_old2, cc2,c2,n_x);
    print(psi, n_x);
    copy(psi_old2,psi_past,n_x);
  }

  return 0;
}

void evolve(double *psi_new, double *psi_old, double *psi_old2, double cc2, double c2, int n_x){
  int i;
  double s=1.0;
  for(i=1;i<n_x-1;i++){
    psi_new[i] = psi_old[i];
    psi_new[i] += 2* psi_old[i] - psi_old2[i] + (c2/cc2)*(psi_old[i+1]+psi_old[i-1]-2*psi_old[i]);
  }
  
}

void copy(double *recibe, double *entrega, int n_x){
  int i;
  for (i=0;i<n_x;i++){
    recibe[i] = entrega[i];
  }
}

void init(double *psi, int n_x){
  int i;
  for(i=0;i<n_x;i++){
    psi[i] = 0.0;
    psi[i+1] = 0.0;
  }
}


void print(double *psi, int n_x){
  int i;
  for(i=0;i<n_x;i++){
    std::cout << psi[i] << " ";
  }
  std::cout << "\n";
}

