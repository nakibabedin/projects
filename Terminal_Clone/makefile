compile: cd.o execute.o helpers.o main.o 
	gcc -o shell.out cd.o execute.o helpers.o main.o 

cd.o: cd.c 
	gcc -c cd.c

execute.o: execute.c helpers.h cd.h 
	gcc -c execute.c

helpers.o: helpers.c 
	gcc -c helpers.c

main.o: main.c execute.h helpers.h 
	gcc -c main.c

run: compile
	./shell.out

clean:
	rm -rf *.o compile *.out
