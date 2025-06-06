# Kallune

> (Ça veut dire blaireau en suédois)

Projet de jeu vidéo réalisé dans le cadre des cours de programmation et de sythèse d'image du semestre 2 de l'IMAC.

## Compilation et exécution du projet
Ce projet utilise CMake pour gérer ses dépendances. Pour installer CMake, vous pouvez suivre [ce tutoriel](https://cmake.org/getting-started/).
Pour compiler le projet, il faut lancer cette commande :
```bash
cd build
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

## Challenges techniques
> La liste des soucis qu'on a vaincu!
- Animation de l'arrière-plan du menu (taille maximale des sprites atteinte)
- Séparation logique/graphique (difficulté à gérer les interactions entre les objets)
- Bizarreries d'openGL sur Mac (problèmes de compatibilité)
- Mystérieuse fuite de mémoire sur les sprites animés
- Gestion des positions isométriques

## Pistes d'amélioration
> La liste des choses qu'on aurait aimé faire!
- Ajouter des paramètres de génération de la carte dans le menu settings
- Améliorer l'ordre d'affichage des éléments
- Améliorer les visuels