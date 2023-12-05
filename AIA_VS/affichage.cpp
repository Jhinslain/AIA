#include "affichage.hpp"

// Fonction pour dessiner une balle
cv::Mat drawBall(cv::Point center, int radius) {
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::circle(image, center, radius, cv::Scalar(255, 0, 0), -1);
    return image;
}

// Fonction pour dessiner un mur
cv::Mat drawWall(cv::Point start, cv::Point end) {
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::rectangle(image, start, end, cv::Scalar(5,5,5), -1);
    return image;
}


// Fonction pour dessiner un spike
cv::Mat drawSpike(cv::Point center, int radius) {
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::circle(image, center, radius, cv::Scalar(0, 0, 255), -1);
    return image;
}

// Fonction pour dessiner l'arrivée
cv::Mat drawArrival(cv::Point center, int radius) {
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::circle(image, center, radius, cv::Scalar(21, 123, 16), -1);
    return image;
}