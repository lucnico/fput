#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 32   // 32 para enerModo
#define dt 0.01 // 0.001 para enerModo
#define alfa 0.25

void init(double *u, double *uant){
  int i;
  
  for(i=1; i<N-1; i++){ // cond. iniciais
    u[i]=sin(M_PI*(double)i/(N-1));
    uant[i]=sin(M_PI*(double)i/(N-1));
  }

  u[0]=0; u[N-1]=0; // massas fixas nas bordas
  uant[0]=0; uant[N-1]=0;
}



double update(double *u, double *uant, double *v){
  int i;
  double unov[N], a;
  
  for(i=1; i<N-1; i++){ // calcula acelerações
    a=(u[i+1]+u[i-1]-2*u[i])+alfa*(pow(u[i+1]-u[i],2)-pow(u[i]-u[i-1],2));
    unov[i]=2*u[i]-uant[i]+a*dt*dt; // Verlet
    v[i]=(unov[i]-uant[i])/(2*dt); // calcula a velocidade
  }
  
  for(i=1; i<N-1; i++){ // atualiza as posições
    uant[i]=u[i];
    u[i]=unov[i];
  }
}

void anima(double *u){
  int i;
  
  for(i=0; i<N; i++){
    printf("%lf %lf 5\n",(double)i/N, 0.2*u[i]+0.5);
  }
}

void enerModo(double t, double *u, double *v){
  int i,k;
  double a[6], da[6];
    
  for(k=1; k<6; k++){
    a[k]=0; da[k]=0;
    for(i=0; i<N; i++){
      a[k]+=u[i]*sin(M_PI*k*i/(N-1));
      da[k]+=v[i]*sin(M_PI*k*i/(N-1));
    }

    printf("%d %lf %lf\n", k, t, 0.5*da[k]*da[k]+2*pow(sin(M_PI*(double)k/(N-1)/2),2)*a[k]*a[k]);
  }
}

int main(int argc, char *argv[]){
  int i;
  double u[N],uant[N],v[N],t, E;
  
  init(u, uant);
  
  for(t=0; t<300000; t+=dt){  // 9000 para enerModo
    update(u, uant, v);
    
    if((int)(t/dt)%1000==0){
      enerModo(t, u, v);
      //anima(u);                // ./a.out | ./DynSim.sh -l 32 -m 3
    }
  }
  
  return 0;
}
