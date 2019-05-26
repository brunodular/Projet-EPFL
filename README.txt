1. Notre Accélérateur et Informations Générales

Le code de ce fichier Git simule un accélérateur de particules (de mani1ere simplifié) sous format texte mais également sous forme graphique 3D. 

Pour aboutir à la réalisation de notre simulation, nous avons implémenté tout ce qui a été demandé dans les séries liés au projet. Nous avons donc implémenté toutes les classes demandées, et noous avons ajouté une autre classe (la classe Cases) qui nous semblait nécessaire pour l'optimisation meilleur voisin.
Nous avons donc également implémenté une partie graphisme avec laquelle on peut visualisé en 3D la simulation du mouvement des particules dans l'accélérateur. La partie graphisme est effectuée au moyen de la bibliothèque Qt (la version qui se trouve sur les machines virtuelles). A cela, nous avons également ajouté l'affichage des eillipses qui réprésentent (comme indiqué dans le complément mathématiques) la répartition dans les faisceaux. 

Afin de ne pas avoir eu à écrire tous les makefiles, nous avons utilisé des fichiers .pro, dans lesquelles nous avons indiqué les dépendances entre les différents fichiers du projet. Ceux-ci vont ensuite permettre de générer les makefiles, comme expliqué ci-dessous.

Les fichiers sont répartis de la manière suivante:
  - les fichiers liés à l'affichage graphique sont dans le dossier Qt-GL
  - les fichiers qui font l'abstraction des objets simulés dans le dossier general
  - les fichiers tests (qui ne sont généralement plus compilable) se trouvent dans le dossier TESTS
  - le fichier réponse et le journal se trouvent dans le dossier INFO
  - le code lié à l'affichage format texte se trouve dans le dossier vue_texte
  - le code qui a permis à la création du graphique (cf. fichier conception) se trouve dans TESTS/exerciceP13
 

2. Comment démarrer

Pour faire fonctionner ce programme, il faut d'abord créer les "makefiles" qui vont permettre au code de compiler. Pour créer ces makefiles, il suffit d'aller sur le terminal, de se rendre dans le dossier "Projet-EPFL-master" provenant du Git, et d'écrire "qmake" puis appuyer sur la touche "enter".
Ensuite, il faut compiler avec le mot-clé "make". Et enfin, pour démarrer le programme, il suffit d'écrire "./Qt-GL/accelerator" et le programme (format graphique) sera lancé. Par la suite, il suffit de suivre les instructions qui apparaissent sur le terminal. Et si tout a été fait correctement, lorsque vous refuserez d'ajouter un autre faisceau dans l'accélérateur, une fenêtre s'affichera avec un accélérateur et des particules en mouvement, et n autres fenêtres affichant des ellipses (où n est le nombre de faisceaux ajoutés à l'accélérateur).

Pour s'amuser un peu avec le programme, il est conseillé de faire varier le nombre de côtes de l'accélérateur, et de faire varier les autres paramètres de distribution des faisceaux (pour voir leurs effets sur la forme des ellipses).
Dans la partie graphique il est également conseillé de faire bouger le point de vue (avec les touches "W", "A", "S", "D", "UP", "DOWN", "LEFT", "RIGHT", "SPACE"), et de faire varier la vitesse des particules (avec les touches "P" et "O").

Il est cependant conseillé de ne ni mettre trop de particules à la fois et ni trop bouger la "caméra" lorsqu'il y a trop de particules qui sont en mouvement. En effet, ceci ferait très probablement disparaître toutes les particules (cf. fichier conception pour plus d'informations).

3. Estimation travail

En moyenne, nous avons chacun probablement travaillé autour trois heures par semaine sur ce projet.
