CC=gcc
CFLAGS= -g -lpthread
NCPU=4
BASH=Projet1.bash
	
#Compilation 
	
all: philo prod ecriv test-and-set tts ecriv-aa philo-aa prod-aa

philo: philosophe.o
	$(CC) -o $@ $< $(CFLAGS) 
		
prod: producer.o
	$(CC) -o $@ $< $(CFLAGS) 

ecriv: ecrivain.o
	$(CC) -o $@ $< $(CFLAGS) 

ecriv-aa: attente_active/ecrivain-tas.o attente_active/semaphore.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
philo-aa: attente_active/philosophe-tas.o attente_active/semaphore.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
prod-aa:  attente_active/producer-tas.o attente_active/semaphore.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
test-and-set: attente_active/test-and-set.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
tts : attente_active/test-and-test-and-set.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	

clean :
	-rm -f *.png
	-rm -f *.o
	-rm -f ecriv
	-rm -f prod
	-rm -f philo
	-rm -f test-and-set
	-rm -f tts
	-rm -f */*.o


#Mesures

mes-philo: philo
	./$(BASH) output.csv $$((2 * $(NCPU))) $<
	 	
mes-ecriv: ecriv
	./$(BASH) output.csv $$((2 * $(NCPU))) $<  
	
mes-prod: prod
	./$(BASH) output.csv $$((2 * $(NCPU))) $< 
	
mes-tas: test-and-set
	./$(BASH) output.csv $$((2 * $(NCPU))) $<

mes-tatas: test-and-test-and-set
	./$(BASH) output.csv $$((2 * $(NCPU))) $<

#plots 

plot-philo: mes-philo
	python3 plot.py -f "output.csv" -n "Temps philosophe"

plot-prod: mes-prod
	python3 plot.py -f "output.csv" -n "Temps producteur"
	
plot-ecriv: mes-ecriv
	python3 plot.py -f "output.csv" -n "Temps ecrivain"

plot-tas: mes-tas
	python3 plot.py -f "output.csv" -n "Test and set"

plot-tatas: mes-tatas
	python3 plot.py -f "output.csv" -n "Test and test and set"



