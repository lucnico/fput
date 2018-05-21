#include <math.h>
#include <stdio.h>

#define dt 0.01
#define w2 1.0

double fi(double x){
  return -w2*x;
}

main(){

  double  x=1.18,vhnew,vh,xnew,E,E0;
  double  v=0;
  int i;

  E0 = v*v/w2 + x*x;

  vh = v + fi(x)*dt/2.0; 
  
  for(i=0;i<10000;i++){
    vhnew = vh + fi(x)*dt;
    xnew = x + vhnew*dt;

    v=(vhnew+vh)/2;
    x=xnew;    vh = vhnew;
    E = v*v/w2 + x*x;
    
    printf("%f %f %f %f\n",i*dt,x,v,E/E0 - 1.0);
  }


}
