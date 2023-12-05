#ifndef ELEMENT_DETECTION_HPP
#define ELEMENT_DETECTION_HPP

#include <opencv2/opencv.hpp>

cv::Point2f getContourCenter(const std::vector<cv::Point>& contour);

cv::Point2f detectCircle(const cv::Mat& mask);
cv::Point2f detectTriangle(const cv::Mat& mask);
std::vector<cv::Point2f> detectOctagons(const cv::Mat& mask);

cv::Mat cleanMask(const cv::Mat& mask);
std::vector<cv::Point2f> detectColorElements(const cv::Mat& mask);


struct GameElements {
    cv::Point2f ballPosition;
    cv::Point2f endHolePosition;
    std::vector<cv::Point2f> deathHolesPositions;

    std::vector<cv::Point2f> redElements;    // Points pour les éléments rouges
    std::vector<cv::Point2f> blueElements;   // Points pour les éléments bleus
    std::vector<cv::Point2f> greenElements;  // Points pour les éléments verts
};

// Fonction pour détecter les éléments de jeu
GameElements detectGameElements(const cv::Mat& input);


#endif // ELEMENT_DETECTION_HPP
