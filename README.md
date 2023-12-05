# Analyse d'Image Avancée : Jeu de Bille en Réalité Augmentée

## Introduction
Ce projet vise à créer une expérience interactive en réalité augmentée où des objets 3D, tels que des billes, sont affichés sur une feuille de papier placée devant une caméra. L'objectif est de faire bouger ces objets en temps réel, synchronisés avec le mouvement de la feuille. Pour cela, le projet implique un scan minutieux des images capturées par la caméra et un suivi précis du flux vidéo.

### 1) Concept du Jeu
Le jeu se présente comme un labyrinthe en 3D dans lequel une bille apparaît et doit être dirigée jusqu'à un trou de sortie. Ce défi est rendu possible en bougeant physiquement le plateau (la feuille de papier) sous la caméra. Les éléments clés du jeu sont :

Plusieurs Niveaux : Différents niveaux de complexité et de design.
Murs Mobiles et Colorés : Murs qui changent de position et de couleur pour diversifier le gameplay.
Niveaux Modifiables : Possibilité d'ajouter ou de déplacer des trous et des murs pour renouveler l'expérience.
Difficulté Adaptative : Le jeu s'adapte au niveau du joueur.
Physique Réaliste : Gestion des hauteurs et des sauts de la balle en fonction du mouvement du plateau.
Interactivité Augmentée : Ajout de petits papiers sur l'écran qui modifient le jeu, apportant des bonus ou des malus.

### 2) Fonctionnement
Le jeu repose sur la détection et le suivi de points spécifiques :
- Cercle bleu : Point de départ
- Octogone rouge : Zone de mort
- Triangle vert : Point de sortie

![image](https://github.com/Jhinslain/AIA/assets/152390192/c3ef79ad-41c6-4045-bf67-1d831d69d1e4)

### 3) Points de Repère : Les points clés du jeu sont le coin supérieur droit, le coin inférieur gauche, le trou d'arrivée et le point d'apparition de la balle.
Tracking Avancé : Utilisation de l'homographie pour identifier les quatre sommets du plateau de jeu et suivi d'objets pré-définis.

![image](https://github.com/Jhinslain/AIA/assets/152390192/b0cfd9b8-9b34-4c76-b099-cca2740bd407)

## Méthodologie de Tracking

### 1) Prétraitement de l'Image :
Correction de l'éclairage, filtrage et préparation de l'image pour un traitement optimal.

### 2) Masque sur la Feuille :
Application d'un masque pour isoler la feuille de papier et ses caractéristiques.

### 3) Suivi du Rectangle de la Feuille : 
Maintien d'un suivi précis de la position et de l'orientation de la feuille.

### 4) Suivi des Éléments Importants : 
Détection des éléments du jeu, notamment à travers la détection des couleurs avec des seuils HSV spécifiques.
