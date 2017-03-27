CFLAGS = -Wall -pedantic -ansi -g
LDFLAGS = -lMLV -lm 
CC = gcc

PVC : main.o affichage.o ville.o carte.o visite.o population.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o : main.c population.h
	$(CC) -c $(CFLAGS) $<

affichage.o : affichage.c affichage.h visite.h 
	$(CC) -c $(CFLAGS) $<

visite.o : visite.c visite.h carte.h
	$(CC) -c $(CFLAGS) $<

carte.o : carte.c carte.h ville.h
	$(CC) -c $(CFLAGS) $<

ville.o : ville.c ville.h include.h
	$(CC) -c $(CFLAGS) $<

population.o : population.c visite.h affichage.h
	$(CC) -c $(CFLAGS) $<

test_affichage : test_affichage.o affichage.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_affichage.o : test_affichage.c affichage.h include.h
	$(CC) -c $(CFLAGS) $<

test_visite : test_visite.o affichage.o carte.o visite.o ville.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_visite.o : test_visite.c affichage.h include.h carte.h visite.h ville.h
	$(CC) -c $(CFLAGS) $<

clean : 
	rm -f *.o

mrproper : clean
	rm -f PVC

install : PVC
	mkdir ../bin
	mv PVC ../bin/PVC
	make mrproper

uninstall : mrproper
	rm -f ../bin/PVC
	rm -rf e ../bin