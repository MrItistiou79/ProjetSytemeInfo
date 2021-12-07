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
	-rm -f ecriv-aa
	-rm -f *.csv
	-rm -f philo-aa

#Mesures

mes-philo: philo
	./$(BASH) philosophe.csv $$((2 * $(NCPU))) $<
	 	
mes-ecriv: ecriv
	./$(BASH) ecrivain.csv $$((2 * $(NCPU))) $<  
	
mes-prod: prod
	./$(BASH) producer.csv $$((2 * $(NCPU))) $< 
	
mes-tas: test-and-set
	./$(BASH) tas.csv $$((2 * $(NCPU))) $<

mes-tatas: test-and-test-and-set
	./$(BASH) tatas.csv $$((2 * $(NCPU))) $<
	
mes-philo-aa: philo-aa
	./$(BASH) philosophe-aa.csv $$((2 * $(NCPU))) $<
	
mes-ecriv-aa: ecriv-aa
	./$(BASH) ecrivain-aa.csv $$((2 * $(NCPU))) $<
	
mes-prod-aa: prod-aa
	./$(BASH) producer-aa.csv $$((2 * $(NCPU))) $<


#plots 
plot-all : plot-philo plot-prod plot-ecriv plot-tas plot-tatas plot-philo-aa plot-prod-aa plot-ecriv-aa

plot-philo: mes-philo
	python3 plot.py -f "philosophe.csv" -n "Temps philosophe"

plot-prod: mes-prod
	python3 plot.py -f "producer.csv" -n "Temps producteur"
	
plot-ecriv: mes-ecriv
	python3 plot.py -f "ecrivain.csv" -n "Temps ecrivain"

plot-tas: mes-tas
	python3 plot.py -f "tas.csv" -n "Test and set"

plot-tatas: mes-tatas
	python3 plot.py -f "tatas.csv" -n "Test and test and set"

plot-philo-aa: mes-philo-aa
	python3 plot.py -f "philosophe-aa.csv" -n "Temps philosophe attente active"

plot-prod-aa: mes-prod-aa
	python3 plot.py -f "producer-aa.csv" -n "Temps producteur attente active"
	
plot-ecriv-aa: mes-ecriv-aa
	python3 plot.py -f "ecrivain-aa.csv" -n "Temps ecrivain attente active"


#comparaison

comp-all : comp-philo comp-prod comp-ecriv comp-tas

comp-philo:mes-philo mes-philo-aa
	python3 compare.py -f "philosophe.csv" -g "philosophe-aa.csv" -n "Comparaison POSIX vs attente active philosophe"
	
comp-prod:mes-prod mes-prod-aa
	python3 compare.py -f "producer.csv" -g "producer-aa.csv" -n "Comparaison POSIX vs attente active producer"
	
comp-ecriv:mes-ecriv mes-ecriv-aa
	python3 compare.py -f "ecrivain.csv" -g "ecrivain-aa.csv" -n "Comparaison POSIX vs attente active ecrivain"
	
comp-tas:mes-tas mes-tatas
	python3 compare.py -f "tas.csv" -g "tatas.csv" -n "Comparaison test-and-set vs test-and-test-and-set"
	



