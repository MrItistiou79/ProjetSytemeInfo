# ProjetSytemeInfo

##Fichiers 

###Fichiers C 
-_ecrivain.c_
-_philosophe.c_
-_producer.c_
Dans le dossier attente_active, la synchronisation a été implémentée en attente active, au lieu de la synchronisation POSIX. Il contient les fichiers suivants : 
-_ecrivain-tas.c_
-_philosophe-tas.c_
-_producer-tas.c_
-_semaphore.c_ : implémente les sémaphore avec les mutex attente active
-_mutex.c_: mutex implémentés en attente active
-_test-and-set.c_
-_test-and-test-and-set.c_

###Fichier Bash
_Projet1.bash_ <file.csv> <N> <prog> : Script permettant de mesurer les performances du programme qui lui est passé en argument. <file.csv> est le fichier csv dans lequel les mesures de performance sont stockées, <N> est le nombre de thread maximum pour lequel on veut réaliser le test de performance et <prog> le programme compilé pour lequel on veut mesurer les performances. 

###Fichiers python
-_plot.py_ : Script python permettant de plotter les performances mesurées à l'aide du script bash
-_compare.y_ : Script python permettant de comparer les performances de deux programmes en les plottant sur le même graphique.

##Commandes make
-_make all_ : compile tous les fichiers .c 
-_make mes-all_ : exécute les commandes suivantes : mes-philo mes-ecriv mes-prod mes-tas mes-tatas mes-philo-aa mes-ecriv-aa mes-prod-aa. Chacune de ces règles permet de lancer le script bash pour le programme C correspondant, _mes-all_ permet de le lancer pour tous les programmes. 
-_make plot-all_: exécute les commandes suivantes : plot-philo plot-prod plot-ecriv. Chacune de ces commandes permet de créer un graphe montrant les performances du programme C concerné.
-_make comp-all : exécute les commandes suivantes : comp-philo comp-prod comp-ecriv comp-tas. Chacune de ces commandes permet de lancer le script python, qui compare les performances pour un algorithme qui utilise la synchronisation POSIX et le même algorithme qui utilise la synchronisation attente active. 
-_make clean_ : permet de supprimer tous les fichiers générés par la compilation, ainsi que les fichiers csv.
