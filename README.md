# Recherche du plus grand rectangle dans un dallage.
## Génération de l'éxécutable

Compiler en utilisant le fichier **./make.sh**.
Le binaire est **bin**.

## Utilisation du binaire
Le binaire s'utilise de la façon suivante :
  * **./bin -h**
    * Permet d'avoir l'aide.
  * **./bin -f nomDeFichier [numeroDeSolution] [boolAfficherGrille]**
    * Permet de traiter le dallage de **nomDeFichier** avec la solution **numeroDeSolution**. Par défaut : Solution 1. **numeroDeSolution** va de 1 à 4.
	  * **boolAfficherGrille** permet d'afficher ou non le dallage.
  * **./bin -s borneInf borneSup [nomDeFichier]**
	  * Permet de générer un fichier csv contenant un test de performance des solution sur un dallage de N*N avec N allant de borneInf à borneSup.
		* **nomDeFichier** est le nom de fichier de sortie. Par défaut : "stats.csv"
	* **./bin -t typeTest**. Permet d'éxéctuer le script de test d'erreurs de fichier et le script de test de dallages.
	  * Si **typeTest** = 1 alors les tests d'erreurs seront faits.
		* Si **typeTest** = 2 alors les tets de dallages seront faits.
## Documentation
Le détail du fonctionnement des fonctions se trouvent dans les fichiers **.\*.h**.
Aussi, une documentation Doxygen a été générée pour avoir une meilleure vision des fonctions et des structures utilisées.

## Remarques
Dans nos dallage et implémentation des solutions :
* '1' équivaut à une case non-accessible
* '0' équivaut à une case accessible.





GERTNER Pierre
DUVET Youri
