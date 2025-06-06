# Kallune

> (Ça veut dire blaireau en suédois)

![Title Screen](./doc/screenshots.gif?raw=true) 

Projet de jeu vidéo réalisé dans le cadre des cours de programmation et de sythèse d'image du semestre 2 de l'IMAC.

## Compilation et exécution du projet
Ce projet utilise CMake pour gérer ses dépendances. Pour installer CMake, vous pouvez suivre [ce tutoriel](https://cmake.org/getting-started/).
Pour compiler le projet, il faut lancer cette commande :
```bash
cd build
cmake ..
cmake --build .
cd ..
```
Puis pour démarrer le projet :
```bash
cd bin
./Kallune // macOS & Linux
Kallune.exe // Windows
```

## Organisation du code
Le code est organisé en "modules", chacun ayant une responsabilité spécifique. Voici un aperçu des principaux modules :
- `main` : Point d'entrée du jeu, gère la boucle principale et l'initialisation.
- `input` : Gère les entrées utilisateur (clavier, souris).
- `game.py` : Gère la logique du jeu, les interactions entre les objets et l'état du jeu.
- `graphics` : Gère l'affichage des éléments graphiques, y compris les sprites et les animations.
- `utils`: Utilitaires communs aux différents modules, comme les états les fonctions de gestion des collisions.

## Améliorations réalisées
> La liste des améliorations apportées par rapport à la version initiale!
- Vue isométrique
- Animations des sprites
- Système d'ennemis différents
- Bloc plein double (type de terrain additionnel)
- [tracké, mais pas affiché] Système de score

## Challenges techniques
> La liste des soucis qu'on a rencontré
- **Animation de l'arrière-plan du menu (taille maximale des sprites atteinte)**  
    L'arrière-plan animé du menu est en réalité un sprite animé. Nous avons fait ce choix pour gagner du temps de développement et éviter d'avoir à coder des déplacements, mais nous avons rencontré d'autres soucis : au départ, l'animation ne chargeait pas et affichait juste un carré noir. Nos recherches sur internet ont indiqué que c'était certainement dû au fait que notre spritesheet dépassait la taille de texture maximale permise par défaut par OpenGL. Nous avons donc adapté la spritesheet en la passant sur plusieurs lignes (une spritesheet carrée plutôt qu'une longue bande) et en divisant la résolution afin que chaque frame soit pixel perfect (à l'origine la résolution était trois fois plus haute que nécessaire). La spritesheet finale fait 2775x1888 pixels, ce qui est beaucoup plus raisonnable qu'à l'origine.

- **Séparation logique/graphique (difficulté à gérer les interactions entre les objets)**  
    Nous avons souhaité séparer la logique et l'affichage afin de séparer les responsabilités. L'avantage principal de cette pratique est qu'il est beaucoup plus facile de faire un affichage différent sans avoir à modifier la logique à nouveau. En revanche, cela nous a posé plusieurs difficultés :  
        - Séparer la logique et l'affichage rajoute un risque de "désynchronisation" entre les deux : quand un ennemi ne s'affiche pas, par exemple, il faut vérifier si le souci ne vient pas du passage d'état entre les deux.  
        - Pour certaines fonctionnalités un peu poussées (par exemple, rajouter des cases décoratives aléatoires sur la carte qui ne sont pas prévues par la logique), la séparation des responsabilités rajoute du travail et de la complexité. Il faut instancier des objets dans l'affichage afin d'avoir un random "persistant" et qui ne se recalcule pas à chaque frame. Ce n'est pas nécessairement mauvais mais ça peut prendre du temps. Nous avons pensé plus tard à d'autres techniques pour éviter ce souci (bruit de Perlin déterministe par exemple).  
        - La librairie que nous utilisons pour la gestion des fenêtres (GLFW) ne se prête pas vraiment à séparer l'affichage de la gestion des interactions. Elle utilise un objet Window qui réunit ces deux aspects. Les callbacks qu'on peut lui passer pour récupérer les interactions utilisateur doivent être des fonctions statiques, ce qui force à utiliser des variables globales, ce que nous voulions éviter. Nous avons réussi à contourner ce problème mais ça a un peu mis le bazar dans l'organisation bien séparée que nous avions imaginée.

- **Bizarreries d'OpenGL sur macOS (problèmes de compatibilité)**  
    Faire fonctionner OpenGL sur macOS nous a posé plusieurs soucis qui sont visiblement spécifiques à cette plateforme. Certains d'entre eux sont très peu documentés, ce qui a rendu très difficile la résolution des problèmes. Tous ces soucis sont réglés et le jeu fonctionne très bien sur Mac désormais.

- **Mystérieuse fuite de mémoire sur les sprites animés**  
    Nous avons rencontré un souci de fuite de mémoire en chargeant les sprites animés. Au bout d'un certain temps, le programme était tué par une erreur SIGKILL car il utilisait visiblement trop de mémoire. Cela venait des sprites animés : à chaque changement de frame, nous créions un nouveau tableau d'UV et rappelions la fonction `createVAO` fournie par glbasimac. Cela entraînait une fuite de mémoire et n'était pas du tout optimal (voir le screenshot ci-dessous).  
    ![Crash](./doc/crash.png?raw=true)  
    Nous avons ajouté une fonction à glbasimac qui met à jour uniquement le buffer d'UVs, ce qui a résolu le souci.

- **Gestion des positions isométriques**  
    Nous avons décidé de calculer la logique du jeu sur une grille classique, et de convertir les positions "2D" en isométrique seulement au moment de l'affichage. Nous avons un peu tâtonné pour faire fonctionner les positions isométriques.

## Pistes d'amélioration
> La liste des choses qu'on aurait aimé faire!
- Affichage du score
- Ajouter des paramètres de génération de la carte dans le menu settings
- Améliorer l'ordre d'affichage des éléments
- Améliorer les visuels (gestions des cases voisines)
