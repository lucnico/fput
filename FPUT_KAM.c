#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 32
#define dt 0.001
#define alfa 0.25
#define amp_ini 0.1
#define amp_fin 10.1
#define na 25 //número de amplitudes
#define damp (amp_fin - amp_ini)/na

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

double H(double *u, double *v, int deb) {
    double ener[N/2], ene_tot, pho[N/2], H_tot;
    int i;

    ene_tot = 0;
    for (i=0; i<(N/2); i++) {
        ener[i] = enerModoK(u,v,i);
        ene_tot += ener[i];
        pho[i] = 0;
    }

    H_tot = 0;
    for (i=1; i<(N/2); i++) {
        H_tot += (ener[i]/ene_tot)*log(ener[i]/ene_tot);
    }

    return H_tot*(-1);
}

int main(int argc, char *argv[]){
    int i, count_rec[na], tmed, tr, k;
    double u[N], v[N], t, ene, amp, ene0, erro;
    double Haux, Hzero, Hmax, Hinf, eta[na];

    FILE *f1 = fopen("fpu_kam.dat","w");

    Hmax = log(N/2);

    tr = (int) 2*0.38*pow(N,2.5)/(pow(amp_ini*alfa,0.5)); // tempo de recorrência
    tmed = 1000; //mede a cada tmed unidades de t

    for (k=0; k<na; k++) { //for que cobre todas as 'na' amplitudes
        amp = amp_ini+damp*k;

        for (i=0; i<N; i++){ // cond. iniciais
            u[i] = amp*sin(M_PI*(double)i/(N-1));
            v[i] = 0;
        }

        //teste de super recorrência
        ene0 = enerModoK(u,v,1);
        erro = ene0/100000;
        count_rec[k] = 0; //conta quantos "picos" tem a mesma energia que o estado inicial

        //teste de super recorrência 2
        Hzero = H(u,v,0);
        Hinf = Hzero;

		t = 0;
        for (i=0; i<(int)(18*tr/dt); i++){ //super recorrência está geralmente em ~(12*tr/dt)
            update(u, v);

            if (i%tmed==0){
                ene = enerModoK(u,v,1);
                if (pow(ene0-ene,2)<erro) count_rec[k]++;

                Haux = H(u,v,1);
                if (Haux>Hinf) Hinf = Haux;

                if (i%(100*tmed)==0)
                    fprintf(f1,"%f %f %f %f %f\n",amp,2*t*pow(pow(sin(M_PI/(2.0*(N+1)))/(2.0*M_PI),2),0.5), ene, enerModoK(u,v,2), enerModoK(u,v,3));
            }
			t = i*dt;
        }


        eta[k] = (Hmax-Hinf)/(Hmax-Hzero);
    }

	for(k=0; k<na; k++)
		fprintf(f1, "0 %f %i %f\n", amp_ini + k*damp, count_rec[k], eta[k]);

    fclose(f1);

    return 0;
}
