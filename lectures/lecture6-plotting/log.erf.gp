set terminal svg background "white"; \
	  set output "plot.gamma.svg"; \
	  set key bottom; \
	  plot \
	  	"data.txt" index 1 with lines title "gamma(x)"\

