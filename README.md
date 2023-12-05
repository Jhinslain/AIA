# Projet Analyse d'Image Avancée

## I. Analyse du Sujet
### 1. Introduction
Ce projet vise à afficher des informations et objets 3D sur une feuille placée devant la caméra. L'objectif est de faire bouger ces objets en temps réel en fonction du mouvement de la feuille. Cela nécessite le scan des images capturées par la caméra pour identifier des points spécifiques et le suivi (tracking) du flux vidéo.

### 2. Idées
Le concept principal est de développer un jeu de bille 3D dans un labyrinthe. Le jeu implique :

Apparition d'une bille et création d'un labyrinthe.
Objectif de bouger le plateau pour diriger la bille vers la sortie en utilisant une physique réaliste.
Rendu 3D en temps réel sur la vidéo.
Idées Supplémentaires
Plusieurs niveaux de jeu.
Murs mobiles de différentes couleurs.
Niveaux modifiables avec apparition/disparition de trous et murs.
Difficulté adaptative.
Gestion des hauteurs et sauts de la balle.
Intégration d'éléments interactifs comme des bonus/malus.
### 3. Fonctionnement
Le jeu fonctionnera avec des points de repère spécifiques tels que :

Point supérieur droit et inférieur gauche du jeu.
Point d'arrivée (trou de sortie).
Point d'apparition de la balle.
![image](https://github.com/Jhinslain/AIA/assets/152390192/5380d7ba-ab68-4af2-9673-f371b33d03dd)

### 4. Idée de Tracking
Utilisation de techniques telles que :

Homographie : Identification des 4 sommets du labyrinthe.
Reconnaissance d'objets connus sur le plan avec des dimensions préétablies.
### 5. Repère
Le système se basera principalement sur les données capturées par la caméra pour le suivi des objets.

### 6. Suivi Robuste des Points d'Intérêt
Le suivi impliquera :

Prétraitement de l'image (ajustements de l'éclairage, filtrage).
Détection des points d'intérêt.
Suivi des points à travers les différentes frames.
Validation et correction en temps réel.
Possibilité de calibration et réinitialisation par l'utilisateur.
## II. Implémentation
Le projet est développé en C++ en utilisant OpenCV, GLFW et GLEW. Les étapes clés de l'implémentation incluent :

Initialisation et vérification de la caméra.
Capture et prétraitement des frames.
Application de masques pour isoler les éléments d'intérêt.
Utilisation de techniques de tracking avancées.
Dessin et affichage des éléments interactifs en temps réel.
