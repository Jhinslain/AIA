# AIA
Projet Analyse d'Image Avancée

I.	Analyse du sujet

1)	Introduction
Afficher des informations, objets 3D sur une feuille placé devant la cam. Si la feuille bouge, les objets doivent bouger en temps réels. 
Il faut donc scanner les images à la caméra pour trouver des points spécifiques. Il faut aussi analyser le flux vidéo pour le tracking.

2)	Idées
Afficher un jeu de bille 3D dans un labyrinthe. Une bille apparait, un labyrinthe est créé, le but bouger le plateau pour faire bouger la bille avec une physique jusqu’au trou de sortie.
La 3D doit être reproduit en temps réel sur la vidéo.
Idées supplémentaires :
-	Plusieurs niveaux
-	Murs qui bougent avec différentes couleurs
-	Niveaux amovibles (trou/ mur apparaissent / bougent)
-	Difficulté adaptative
-	Hauteurs / saut de la balle avec mouvement du plateau
-	Ajout de petit papier par-dessus l’écran qui modifie le jeu. Comme des petit bonus/malus. 

3)	Fonctionnement

 Point supérieur droite du jeu
 Point inférieur gauche du jeu
  Trou d’arrivé
 	 Point d’apparition de la balle



4)	Idée de tracking :
-	Homographie : prendre les 4 sommets et savoir lesquels sont

-	Prendre des objets sur le plan qu’on connait à l’avance et qu’on connait les mesures

5)	Repére
	Caméra 
6)	Suivis robuste de points d’intérêts 

1. Prétraitement de l'Image
•	Correction d’éclairage : Ajuster les niveaux de luminosité et de contraste pour gérer les variations d'éclairage.
•	Filtrage : Utiliser des filtres (par exemple, un filtre Gaussien) pour réduire le bruit dans l'image.
2. Détection des Points d'Intérêt
•	Utiliser une méthode robuste pour détecter vos points d'intérêt (par exemple, les croix dans les coins de votre feuille). Vous pouvez utiliser des méthodes de détection de contours (comme expliqué dans les réponses précédentes) ou d'autres techniques de détection de caractéristiques.
•	Validation : Assurer une vérification de la cohérence des points trouvés (par exemple, s'assurer qu'ils forment un quadrilatère d'une certaine forme ou taille).
3. Suivi des Points
•	Association : Vous devez garder une trace de quel point correspond à quelle caractéristique d'un frame à l'autre.
•	Prédiction : Vous pouvez utiliser des méthodes de prédiction (comme le filtre de Kalman) pour estimer où vos points d'intérêt seront dans la frame suivante, ce qui peut aider à maintenir un suivi robuste même si la détection des points d'intérêt échoue temporairement.
•	Correction : Si vos points bougent d'une manière inattendue, vous devrez peut-être corriger les estimations de leurs positions.
•	Vérification : Vous devez également vérifier constamment la validité des points suivis pour assurer qu'ils correspondent toujours aux caractéristiques que vous essayez de suivre.
4. Validation par l'Utilisateur
•	Calibration : Permettre à l'utilisateur de valider ou de corriger les points suivis peut améliorer la robustesse du suivi en évitant les erreurs de suivi cumulatives.
•	Réinitialisation : Offrir un mécanisme permettant de réinitialiser le suivi si jamais il devient incorrect ou si les points perdent leur suivi.
