set terminal svg background "white"; \
	  set output "plot.erf.svg"; \
	  set key left; \
	  plot [][-1.1 : 1.1] \
	  	"data.txt" index 0 with lines title "calculated erf(x)"\
	   ,"erf.data" with points pointtype 1 title "tabulated erf(x)" \

