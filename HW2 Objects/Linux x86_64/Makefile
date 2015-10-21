analyze.exe: analyze.o weatherio.o util.o
	gcc -o analyze.exe analyze.o weatherio.o util.o

analyze.o: analyze.c weatherio.h
	gcc -c -o analyze.o analyze.c

clean: 
	rm analyze.exe weatherio.o analyze.o