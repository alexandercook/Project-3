
all: main_mm main_malloc packet

mm.o:	mm.c
	gcc -c mm.c
	
main_mm:	main_mm.c mm.o
	gcc -o main_mm main_mm.c mm.o
	
main_malloc:	main_malloc.c mm.o
	gcc -o main_malloc main_malloc.c mm.o
	
main:	main_mm main_malloc
	./main_mm
	./main_malloc

packet:	packet.c mm.o
	gcc -o packet packet.c mm.o
	
clean:
	rm -Rf *.o \
		main_mm main_malloc main packet


