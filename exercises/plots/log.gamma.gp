set terminal svg background "white"; \
	  set output "plot.gamma.svg"; \
	  set key right; \
	  plot [][-50 : 50] \
	  	"data.txt" index 1 with lines title "calculated gamma(x)", \
		"gamma.data" with points pointtype 1 title "tabulated gamma(x) \
	 
