Out.txt : main.exe		# Out.txt depends on main.exe, Target Out.txt depends on the prerequisite main.exe, tabular indicates starting the recipe
	mono main.exe > Out.txt 

main.exe : main.cs hello.dll 		#We have to translate our program from the high level to bytecode. ALTERNITAVELY, "mcs main.cs", should do the same? 
	mcs -target:exe -reference:hello.dll -out:main.exe main.cs 

hello.dll : hello.cs
	mcs -target:library -out:hello.dll hello.cs

#Make only builds the first target it meets, so if you want to build another target you have to specify