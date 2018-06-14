#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//#define N 64
#define dt 0.001
#define alfa 0.25
#define amp_ini 1.0
#define trans pow(N/1.1,2.5)

double a(double *u, int i){
    return (u[i+1]+u[i-1]-2*u[i])+alfa*(pow(u[i+1]-u[i],2)-pow(u[i]-u[i-1],2));
}

double update(double *u, double *v){
    int i;
    double unov[N], vnov[N], aa;

    for (i=1; i<N-1; i++){ // calcula as forças e novas posições
        aa = a(u,i);
        u[i] = u[i]+v[i]*dt+a(u,i)*dt*dt/2.; // Velocity Verlet
        v[i] = v[i]+(aa+a(u,i))*dt/2.;
    }
}

double enerModoK(double *u, double *v, int modo){ //calcula a energia de um modo específico
    int i, k;
    double a, ap;

    a = 0;
    ap = 0;
    for (i=0; i<N; i++){
      a += u[i]*sin(M_PI*(double)modo*i/(N-1));
      ap += v[i]*sin(M_PI*(double)modo*i/(N-1));
    }

    return (0.5*ap*ap+2*pow(sin(M_PI*(double)modo/(N-1)/2),2)*a*a);
}


int main(int argc, char *argv[]){
    int i, count_rec, tmed, tr, k;
    double u[N], v[N], t, ene, amp=amp_ini, ene0, erro;

    char nome[1000];
    sprintf(nome,"periodo_N%d.dat",N);
    
    //FILE *f1 = fopen(nome,"w");

    tr = (int) 2*0.31*pow(N,2.5)/(pow(amp_ini*alfa,0.5)); // tempo de recorrência
    tmed = 1000; //mede a cada tmed unidades de t

    for (i=0; i<N; i++){ // cond. iniciais
      u[i] = amp*sin(M_PI*(double)i/(N-1));
      v[i] = 0;
    }

    //teste de super recorrência
    ene0 = enerModoK(u,v,1);
    erro = ene0/100000;
    count_rec = 0; //conta quantos "picos" tem a mesma energia que o estado inicial

    i=0;
    
    for (i=0; i<(int) trans/dt; i++) //descarta transiente
      update(u, v);

    
    for (;i<(int)(2*tr/dt); i++){ //super recorrência está geralmente em ~(12*tr/dt)
      update(u, v);
      t = i*dt;
      
      if (i%tmed==0){
	ene = enerModoK(u,v,1);
	if (fabs(ene0-ene)/ene0<0.1){
	  break;
	}
	
	//if (i%(10*tmed)==0)
	//fprintf(f1,"%f %f %f %f\n",t + dt, ene, enerModoK(u,v,2), enerModoK(u,v,3));
      }
    }

    printf("%d %e %e %e\n",N,t,ene,ene0);

    //fclose(f1);

    return 0;
}
