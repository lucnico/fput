#plotar uma amplitude específica do arquivo
amp = 1.0
plot '.../fpu.dat' using 2:($1==amp?$3:1/0)

#plotar no mesmo gráfico todas as amplitudes
amp_ini = 1.0
amp_fin = 10.0
na = 5
damp = (amp_fin-amp_ini)/na
plot for [i=0:(na-1)] 'e:/FPU/fpu.dat' u 2:($1==(i*damp + amp_ini)?$3:1/0) w l title 'Amplitude '.i