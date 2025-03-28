set terminal pngcairo enhanced font "Arial,12" size 1280,720
set output 'sorting_plot.png'

set title "Зависимость времени сортировки от размера массива"
set xlabel "Размер массива"
set ylabel "Время (секунды)"
set format x "%.0f"
set format y "%.6f"
set xrange [100:350000]
set yrange [0:1500]
set logscale xy
set grid
set datafile separator ","
plot "sorting_data.csv" using 1:2 with linespoints title "Shaker Sort", \
     "sorting_data.csv" using 1:3 with linespoints title "Merge Sort", \
     "sorting_data.csv" using 1:4 with linespoints title "Quick Sort"
