set terminal pngcairo enhanced font "Arial,12" size 800,600
set output 'histogram.png'

set title "Гистограмма данных"
set xlabel "Значение"
set ylabel "Частота"
set style fill solid 0.5
bin_width = 1
#bin(x) = bin_width * floor(x / bin_width)
bin(x) = x
set xrange [-0.3:1.5]
plot "data.csv" using (bin($1)):($2) smooth freq with boxes title "Гистограмма"
