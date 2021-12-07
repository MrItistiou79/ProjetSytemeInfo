CC=gcc
CFLAGS= -g -lpthread
NCPU=4
BASH=Projet1.bash
	
#Compilation 
	
all: philo prod ecriv test-and-set tts ecriv-aa philo-aa prod-aa ecriv-aa2 philo-aa2 prod-aa2

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

ecriv-aa2: attente_active/ecrivain-tatas.o attente_active/semaphore.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
philo-aa2: attente_active/philosophe-tatas.o attente_active/semaphore.o attente_active/mutex.o
	$(CC) -o $@ $^ $(CFLAGS)
	
prod-aa2:  attente_active/producer-tatas.o attente_active/semaphore.o attente_active/mutex.o
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
	-rm -f prod-aa
	-rm -f philo-aa
	-rm -f ecriv-aa2
	-rm -f prod-aa2
	-rm -f philo-aa2
	-rm -f *.csv
	
#Mesures

mes-all : mes-philo mes-ecriv mes-prod mes-tas mes-tatas mes-philo-aa mes-ecriv-aa mes-prod-aa mes-philo-aa2 mes-ecriv-aa2 mes-prod-aa2

mes-philo: philo
	./$(BASH) philosophe.csv $$((2 * $(NCPU))) $<
	 	
mes-ecriv: ecriv
	./$(BASH) ecrivain.csv $$((2 * $(NCPU))) $<  
	
mes-prod: prod
	./$(BASH) producer.csv $$((2 * $(NCPU))) $< 
	
mes-tas: test-and-set
	./$(BASH) tas.csv $$((2 * $(NCPU))) $<

mes-tatas: tts
	./$(BASH) tatas.csv $$((2 * $(NCPU))) $<
	
mes-philo-aa: philo-aa
	./$(BASH) philosophe-aa.csv $$((2 * $(NCPU))) $<
	
mes-ecriv-aa: ecriv-aa
	./$(BASH) ecrivain-aa.csv $$((2 * $(NCPU))) $<

mes-prod-aa: prod-aa
	./$(BASH) producer-aa.csv $$((2 * $(NCPU))) $<

mes-philo-aa2: philo-aa2
	./$(BASH) philosophe-aa2.csv $$((2 * $(NCPU))) $<
	
mes-ecriv-aa2: ecriv-aa2
	./$(BASH) ecrivain-aa2.csv $$((2 * $(NCPU))) $<

mes-prod-aa2: prod-aa2
	./$(BASH) producer-aa2.csv $$((2 * $(NCPU))) $<


#plots 

plot-all : plot-philo plot-prod plot-ecriv 

plot-philo: mes-philo
	python3 plot.py -f "philosophe.csv" -n "Temps philosophe"

plot-prod: mes-prod
	python3 plot.py -f "producer.csv" -n "Temps producteur"
	
plot-ecriv: mes-ecriv
	python3 plot.py -f "ecrivain.csv" -n "Temps ecrivain"


#comparaison

comp-all : comp-philo comp-prod comp-ecriv comp-tas

comp-philo:mes-philo mes-philo-aa mes-philo-aa2
	python3 compare.py -a 3 -f "philosophe.csv" -g "philosophe-aa.csv" -h "philosophe-aa2.csv" -n "Comparaison POSIX vs attente active philosophe"
	
comp-prod:mes-prod mes-prod-aa mes-prod-aa2
	python3 compare.py -a 3 -f "producer.csv" -g "producer-aa.csv" -h "producer-aa2.csv" -n "Comparaison POSIX vs attente active producer"
	
comp-ecriv:mes-ecriv  mes-ecriv-aa mes-ecriv-aa2
	python3 compare.py -a 3 -f "ecrivain.csv" -g "ecrivain-aa.csv" -h "ecrivain-aa2.csv" -n "Comparaison POSIX vs attente active ecrivain"
	
comp-tas:mes-tas mes-tatas
	python3 compare.py -a 2 -f "tas.csv" -g "tatas.csv" -n "Comparaison test-and-set vs test-and-test-and-set"
	



