#include <math.h>
#include <stdio.h>

#define dt 0.01
#define w2 1.0

double fi(double x){
  return -w2*x;
}

main(){

  double  x=1.18,vnew,xnew,E,E0;
  double  v=0;
  int i;

  E0 = v*v/w2 + x*x;

  
  
  for(i=0;i<10000;i++){
    xnew = x + v*dt + fi(x) * dt*dt/2 ;
    vnew = v + (fi(x)+fi(xnew))*dt/2 ;


    x = xnew;
    v = vnew;
    E = v*v/w2 + x*x;
    
    printf("%f %f %f %.15e\n",i*dt,x,v,E/E0 - 1.0);
  }


}
