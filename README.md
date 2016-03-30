# cbastien

Projet de compilation, réalisé dans le cadre du M1 ALMA

Instructions supportées
==============

Ce compilateur peut compiler des programmes contenant les instructions suivantes :
* Déclaration de variables et de constantes de type **entier** ou **booléen**
* Assignation de valeurs aux variables
* Opérateurs mathématiques : +, -, * et /
* Opérateurs relationnels : ==, !=, <, <=, > et >=
* Opérateurs booléens : ou, non, et
* Instruction de contrôle **If/then/else**
* Boucle **While**

Installation
==============

Les programmes suivants sont requis pour l'installation de ce compilateur :
* **g++** version 4.8.4 ou supérieure
* **make** version 3.81 ou supérieure

Vous pouvez télécharger le code source à l'adresse [suivante](https://github.com/Callidon/cbastien) ou en utilisant **git** avec la commande suivante :
```bash
git clone https://github.com/Callidon/cbastien.git
```

Pour compiler le projet, naviguez dans le dossier du projet et compilez le à l'aide de **make**
```bash
cd cbastien/
make
```

Utilisation
==============

Pour compiler un programme, vous avez besoin d'une grammaire, qui décrit le langage du programme, et le programme lui même.
Utilisez la commande ```./cbastien -c <path-to-grammar> <path-to-programm>``` pour compiler un programme à l'aide d'une grammaire. Par exemple, pour compiler l'un des programmes fournis avec le projet :
```bash
./cbastien -c examples/grammar.txt examples/somme.txt
```

Cette commande produit du pcode stocké dans un fichier *pcode.txt* dans le répertoire *examples/*. Pour exécuter du pcode contenu dans un fichier, utilisez la commande suivante :
```bash
./cbastien -x examples/pcode.txt
```

Programmes d'exemples
==============

Les programmes suivants sont fournis avec le projet, stockés dans le dossier *examples/* :
* **somme.txt** qui effectue puis affiche la somme de deux entiers demandés en input
* **successif.txt** qui calcule puis affiche la somme des entiers consécutifs de 0 jusqu'à *N*, ce dernier étant demandé en input
* **fibonacci.txt** qui calcule puis affiche la suite de fibonnaci de *N*, ce dernier étant demandé en input

*Copyright 2016 Pierre Gaultier & Thomas Minier*
