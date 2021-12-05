CC=gcc
CFLAGS= -g -lpthread
NCPU=2
BASH=Projet1.bash
HEADERS=-I	
#Compilation 
	
all: philo prod ecriv test-and-set

philo: philosophe.o
	$(CC) -o $@ $< $(CFLAGS) 
		
prod: producer.o
	$(CC) -o $@ $< $(CFLAGS) 

ecriv: ecrivain.o
	$(CC) -o $@ $< $(CFLAGS) 
	
	
test-and-set: mutex.o test-and-set.o
	$(CC) -o $@ $< $(CFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	

clean : 
	-rm -f *.o
	-rm -f ecriv
	-rm -f prod
	-rm -f philo
	-rm -f test-and-set


#Mesures

mes-philo: philo
	./$(BASH) output.csv $$((2 * $(NCPU))) $<
	 	
mes-ecriv: ecriv
	./$(BASH) output.csv $$((2 * $(NCPU))) $<  
	
mes-prod: prod
	./$(BASH) output.csv $$((2 * $(NCPU))) $< 
	

#plots 

plot-philo: mes-philo
	python3 plot.py -f "output.csv" -n "Temps philosophe"

	
plot-prod: mes-prod
	python3 plot.py -f "output.csv" -n "Temps ecrivain"
	
	
plot-ecriv: mes-ecriv
	python3 plot.py -f "output.csv" -n "Temps producteur"







