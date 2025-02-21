CXXFLAGS += -std=c++23 -Wall -Wextra -O2
LDLIBS += -lstdc++ -lm

# #Make the plot directly in the Makefile
# plot.erf.svg : data.txt erf.data Makefile
# 	echo 'set terminal svg background "white"; \
# 		  set output "$@"; \
# 		  set key left; \  #legend
# 		  plot [][-1.1 : 1.1]\ #plot with automatic x-limits and y between -1.1 and 1.1
# 		  	"$<" index 0 with points title "erf(x)"\
# 		   ,"erf.data" with points pointtype 4 title "tabulated erf(x)" \
# 	' | tee log.erf.gp | gnuplot
# #tee means that it recieves from the standard input and sends the same to a standrad output -> into a file and also to gnuplot (intermediate step)

plot.erf.svg : data.txt erf.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  plot [][-1.1 : 1.1] \
		  	"$<" index 0 with lines title "calculated erf(x)"\
		   ,"erf.data" with points pointtype 1 title "tabulated erf(x)" \
	' | tee log.erf.gp | gnuplot

plot.gamma.svg : data.txt gamma.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  plot [][-50 : 50] \
		  	"$<" index 1 with lines title "calculated gamma(x)", \
			"gamma.data" with points pointtype 1 title "tabulated gamma(x) \
		 ' | tee log.gamma.gp | gnuplot

plot.lngamma.svg : data.txt lngamma.data Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  plot \
		  	"$<" index 2 with lines title "calculated lngamma(x)", \
			"lngamma.data" with points pointtype 1 title "tabulated lngamma(x) \
		 ' | tee log.lngamma.gp | gnuplot

#For small step sizes, the svg file becomes comically large
plot.cgamma.png : 3dData.txt Makefile
	echo 'set terminal png size 1920,1080 background "white"; \
		  set output "$@"; \
		  set key right; \
		  set view 60, 315; \
		  set palette rgbformulae 33,13,10; \
		  splot [][][0:6] \
		  	"$<" with pm3d \
		 ' | tee log.cgamma.gp | gnuplot
		
plot.cgamma.svg : 3dData.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  set view 60, 315; \
		  set palette rgbformulae 33,13,10; \
		  set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault; \
		  splot [][][0:6]\
		  	"$<" with pm3d \
		 ' | tee log.cgamma.gp | gnuplot

3dData.txt : main
	./main
#not a great way to do it, but i dont know how to switch the destination for the standard output :(

data.txt : main
	./main > $@

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc


clean:	
	$(RM) [Oo]ut* [Ll]og* *.o main data.txt *.svg