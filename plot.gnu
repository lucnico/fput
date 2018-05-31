set terminal gif font 'verdana' enhanced animate optimize
set size square
set output 'acopladoforadefase.gif'
stats 'graph.dat' nooutput
set yrange[-1:1]
do for [i=1:int(STATS_blocks)] {
    plot 'graph.dat' index (i-1) w l lw 3 notitle
}
