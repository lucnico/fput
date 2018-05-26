#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 32 // 11 vai, 12 da problema
#define dt 0.001
#define alfa 0.25

double a(double *u, int i){
  return (u[i+1]+u[i-1]-2*u[i])+alfa*(pow(u[i+1]-u[i],2)-pow(u[i]-u[i-1],2));
}

void init(double *u, double *v){
  int i;
  
  for(i=0; i<N; i++){ // cond. iniciais
    u[i]=0.5*sin(M_PI*(double)i/(N-1));
    v[i]=0;
  }

  u[0]=0; u[N-1]=0; // massas fixas nas bordas

  return;
}

void update(double *u, double *v){
  int i;
  double unov[N], vnov[N];
  
  for(i=1; i<N-1; i++){ // calcula as forças e novas posições
    unov[i]=u[i]+v[i]*dt+a(u,i)*dt*dt/2.; // Velocity Verlet
  }
  for(i=1; i<N-1; i++){
    vnov[i]=v[i]+(a(u,i)+a(unov,i))*dt/2.;
  }
  
  for(i=1; i<N-1; i++){ // atualiza as posições
    u[i]=unov[i];
    v[i]=vnov[i];
  }

  return;
}

void anima(double *u){
  int i;
  
  for(i=0; i<N; i++){
    printf("%lf %lf 5\n",(double)i/N, 0.5*u[i]+0.5);
  }

  return;
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
  double u[N],v[N],t, E;
  
  init(u, v);
  
  for(t=0; t<9000; t+=dt){
    update(u, v);

    if((int)(t/dt)%1000==0){
      enerModo(t, u, v);
      anima(u);
    }
  }
  
  return 0;
}
