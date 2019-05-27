1. Notre Accélérateur et Informations Générales

Le code de ce fichier Git simule un accélérateur de particules (de manière simplifiée) sous format texte mais également sous forme graphique 3D.

Pour aboutir à la réalisation de notre simulation, nous avons implémenté tout ce qui a été demandé dans les séries liés au projet. Nous avons donc implémenté toutes les classes demandées, et nous avons ajouté une autre classe (la classe Cases) qui nous semblait nécessaire pour l'optimisation meilleur voisin.
Nous avons donc également implémenté une partie graphisme avec laquelle on peut visualiser en 3D la simulation du mouvement des particules dans l'accélérateur. La partie graphisme est effectuée au moyen de la bibliothèque Qt (la version qui se trouve sur les machines virtuelles). A cela, nous avons également ajouté l'affichage des ellipses qui réprésentent (comme indiqué dans le complément mathématique) la répartition des particules dans les faisceaux.
La partie d'affichage textuel étant, selon nous, moins esthétique et intéressante à programmer, nous n'avons pas mis en place toute une interface pour cette partie.

Afin de ne pas avoir eu à écrire tous les makefiles, nous avons utilisé des fichiers .pro, dans lesquelles nous avons indiqué les dépendances entre les différents fichiers du projet. Ceux-ci vont ensuite permettre de générer les makefiles, comme expliqué ci-dessous.

Les fichiers sont répartis de la manière suivante:
  - les fichiers liés à l'affichage graphique sont dans le dossier Qt_GL
  - les fichiers qui font l'abstraction des objets simulés sont dans le dossier general
  - les fichiers tests (qui ne sont généralement plus compilable) se trouvent dans le dossier TESTS
  - le fichier réponse et le journal se trouvent dans le dossier INFOS
  - le code lié à l'affichage format texte se trouve dans le dossier vue_texte
  - le code qui a permis à la création du graphique donnant concernant l'influence de la forme de l'accélérateur sur la stabilité des particules (cf. fichier conception) se trouve dans TESTS/testPolygone

Enfin, étant donné que les tests ont été crées à un moment donné dans notre projet, la plupart ne compilent pas.

2. Comment démarrer

Pour faire fonctionner ce programme, il faut d'abord créer les "makefiles" qui vont permettre au code de compiler. Pour créer ces makefiles, il suffit d'aller sur le terminal, de se rendre dans le dossier "Projet-EPFL-master" provenant du Git, et d'écrire "qmake" puis appuyer sur la touche "enter".
Il suffit ensuite de compiler avec le mot-clé "make". Et enfin, pour démarrer le programme, il suffit d'écrire "./Qt-GL/accelerator" et le programme (sous format graphique) sera lancé. Par la suite, il suffit de suivre les instructions qui apparaissent sur le terminal. Et si tout a été fait correctement, lorsque vous refuserez d'ajouter un autre faisceau dans l'accélérateur, une fenêtre s'affichera avec un accélérateur et des particules en mouvement, et n autres fenêtres affichant des ellipses (où n est le nombre de faisceaux ajoutés à l'accélérateur) apparaîtront également.

Afin de ne pas ralentir la compilation du programme principal, les programmes "tests" ne sont pas compilés par défaut. Pour les compiler, il faut se rendre dans "TESTS/TESTS.pro" et enlever le "#" qui précède le test souhaité ("#" signifie que la ligne est en commentaire).

Si vous désirez afficher la simulation sous format texte, il faudra suivre les deux premières étapes indiquées ci-dessus, pour ensuite écrire "./TESTS/exerciceP10/exerciceP10". Ceci lancera la simulation texte. Cependant, pour modifier les caractéristiques du faisceau et de l'accélérateur, il faudra les modifier directement sur le code source (cf. fichier conception pour avoir plus d'informations sur les méthodes à utiliser et les constructeurs à appeller).

3. Remarques concernant l'utilisation du programme

Pour s'amuser un peu avec le programme, il est conseillé de faire varier le nombre de côtés de l'accélérateur, et de faire varier les autres paramètres de distribution des faisceaux (pour voir leurs effets sur la forme des ellipses par exemple).

Dans la partie graphique, il est également conseillé de faire bouger le point de vue (avec les touches "W", "A", "S", "D", "UP", "DOWN", "LEFT", "RIGHT", "SPACE", ou encore avec la souris), et de faire varier la vitesse des particules (avec les touches "P" et "O"). Il est cependant conseillé de mettre PAUSE (touche "SPACE") lorque vous voulez redimensionner ou déplacer la fenêtre, ou vous déplacer avec la souris. Sinon, pour une raison encore inconnue, les particules ont tendance à parfois disparaître. Cela est peut-être dû à des questions de mémoire.

Le nombre maximum de particules simulables en même temps dépend des capacités de l'ordinateur. Sur les ordinateurs du CO, c'est fluide pour 100-200 particules, et au dessus cela commence à ralentir.

4. Estimation du travail investi

En moyenne, nous avons chacun probablement travaillé autour de 5 heures par semaine sur ce projet.
