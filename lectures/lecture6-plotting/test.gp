set terminal svg background "white";

#The disadvantage of making a seperate file, have to hardcode the output file
set output "plot.test.svg";

set xlabel "x";
set ylabel "y";

#Legend
set key out;

#Plot these two functions from x = 0 to x = 2 pi and set the yscale to -2 to 2
plot [0:2*pi][-2:2]\
    sin(x) with lines title "sin(x) label" \
   ,cos(x) with lines title "cos(x) label"