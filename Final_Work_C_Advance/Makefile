all: area_calc 

area_calc: area_calc.o 
	gcc -o area_calc area_calc.o 

area_calc.o: area_calc.c 
	gcc -c -o area_calc.o area_calc.c 

clean:
	del -rf *.o 
	del -rf area_calc.exe