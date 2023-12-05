#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <opencv2/opencv.hpp>

// Fonction pour dessiner une balle
cv::Mat drawBall(cv::Point center, int radius);

// Fonction pour dessiner un mur
cv::Mat drawWall(cv::Point start, cv::Point end);

// Fonction pour dessiner une spike
cv::Mat drawSpike(cv::Point center, int radius);

// Fonction pour dessiner l'arrivée
cv::Mat drawArrival(cv::Point center, int radius);




// Fonctions similaires pour 'spike' et 'arrival'

#endif // AFFICHAGE_HPP
