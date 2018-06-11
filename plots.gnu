#plotar uma amplitude específica do arquivo
amp = 1.0
n_modos = 3
plot for[i=3:(n_modos+2)] '.../fpu_kam.dat' using 2:($1==amp ? column(i):1/0) w l title 'Modo '.(i-2)

#plotar no mesmo gráfico todas as amplitudes
set xlabel '{/Symbol w}_1t/2{/Symbol p}'
set ylabel 'Energia'
n_modos = 3
amp_ini = 0.1
amp_fin = 10.1
na = 25
damp = (amp_fin-amp_ini)/na
list = ""; a=amp_ini-damp; while (a<amp_fin) {list=list.sprintf(" %.3f",a=a+damp)}
do for [amp in list] {
plot for[i=3:(n_modos+2)] '.../fpu_kam.dat' using 2:($1==amp ? column(i):1/0) w l title 'Modo '.(i-2)
pause 0.2
}

#plotar o gráfico com o contador
set xlabel 'Amplitude'
set ylabel 'número de recorrências'
plot '.../fpu_kam.dat' using 2:($1==0 ? $3:1/0) w lp title ''

#plotar o gráfico dos etas
set xrange [0:10]
set xlabel 'Amplitude'
set ylabel '{/Symbol h}'
plot '.../fpu_kam.dat' using 2:($1==0 ? $4:1/0) w lp title ''