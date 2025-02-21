set terminal svg size 1024,768 background "white"; \
	  set output "plot.cgamma.svg"; \
	  set key right; \
	  set view 60, 315; \
	  set palette rgbformulae 33,13,10; \
	  set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault; \
	  splot [][][0:6]\
	  	"3dData.txt" with pm3d \
	 
