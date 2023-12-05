#include "element_detection.hpp"

// Fonction pour obtenir le centre de masse d'un contour
cv::Point2f getContourCenter(const std::vector<cv::Point>& contour) {
    cv::Moments m = cv::moments(contour);
    return cv::Point2f(static_cast<float>(m.m10 / m.m00), static_cast<float>(m.m01 / m.m00));
}

cv::Mat cleanMask(const cv::Mat& mask) {
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::Mat clean;
    cv::morphologyEx(mask, clean, cv::MORPH_OPEN, kernel);
    return clean;
}


// Fonction pour d�tecter les �l�ments de couleur
std::vector<cv::Point2f> detectColorElements(const cv::Mat& mask) {
    float minArea = 100.0f;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat cleanedMask = cleanMask(mask);

    cv::findContours(cleanedMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<cv::Point2f> elements;

    for (const auto& contour : contours) {
        // Assurez-vous que le contour est suffisamment grand pour �tre consid�r� comme un �l�ment
        if (cv::contourArea(contour) > 100) {
            elements.push_back(getContourCenter(contour));
        }
    }
    return elements;
}


// D�tection d'une forme circulaire (la balle)
cv::Point2f detectCircle(const cv::Mat& mask) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contour, center, radius);

        // Filtrer les petits contours et s'assurer que la forme est suffisamment circulaire
        if (radius > 10 && contour.size() > 5) {
            return center; // Retourner le premier cercle d�tect�
        }
    }

    return cv::Point2f(-1.0f, -1.0f); // Retourner un point invalide si aucun cercle n'est d�tect�
}

// D�tection d'un triangle (le trou de fin)
cv::Point2f detectTriangle(const cv::Mat& mask) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);

        if (approx.size() == 3) {
            cv::Point2f center = (approx[0] + approx[1] + approx[2]) / 3.0f;
            return center; // Retourner le centre du triangle
        }
    }

    return cv::Point2f(-1.0f, -1.0f); // Retourner un point invalide si aucun triangle n'est d�tect�
}

 


// Utilisez des seuils HSV pour les couleurs de vos formes
const cv::Scalar RED_LOW_1(0, 50, 50);
const cv::Scalar RED_HIGH_1(10, 255, 255);
const cv::Scalar RED_LOW_2(170, 50, 50);
const cv::Scalar RED_HIGH_2(179, 255, 255);

const cv::Scalar BLUE_LOW(106 - 10, 150, 150);
const cv::Scalar BLUE_HIGH(106 + 10, 255, 255);

const cv::Scalar GREEN_LOW(80 - 10, 50, 50);
const cv::Scalar GREEN_HIGH(80 + 10, 255, 255);


//M�lange de detection

GameElements detectGameElements(const cv::Mat& input) {
    GameElements elements;

    cv::Mat hsv, redMask, redMask1, redMask2, greenMask;
    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);

    // Cr�er un masque pour le rouge
    cv::inRange(hsv, RED_LOW_1, RED_HIGH_1, redMask1);
    cv::inRange(hsv, RED_LOW_2, RED_HIGH_2, redMask2);
    cv::inRange(hsv, GREEN_LOW, GREEN_HIGH, greenMask);

    redMask = redMask1 | redMask2;

    // D�tecter les trous de mort (rouge)
    elements.deathHolesPositions = detectColorElements(redMask);

    // D�tecter la balle (forme circulaire)
    elements.ballPosition = detectCircle(input); // ou un autre masque si n�cessaire

    // D�tecter l'arriv�e (triangle vert))
    elements.endHolePosition = detectTriangle(input);

    return elements;
}


////Detecte les Elements par la couleurs 
//GameElements detectGameElements(const cv::Mat& input) {
//    GameElements elements;
//
//    cv::Mat hsv, blueMask, redMask, greenMask, redMask1, redMask2;
//    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);
//
//    // Cr�er des masques pour diff�rentes couleurs
//    cv::inRange(hsv, BLUE_LOW, BLUE_HIGH, blueMask);
//    cv::inRange(hsv, RED_LOW_1, RED_HIGH_1, redMask1);
//    cv::inRange(hsv, RED_LOW_2, RED_HIGH_2, redMask2);
//    cv::inRange(hsv, GREEN_LOW, GREEN_HIGH, greenMask);
//
//    redMask = redMask1 | redMask2;
//
//    // D�tecter les �l�ments pour chaque couleur
//    elements.blueElements = detectColorElements(blueMask);
//    elements.redElements = detectColorElements(redMask);
//    elements.greenElements = detectColorElements(greenMask);
//
//    return elements;
//}

////Detecte les Elements par les formes 
//GameElements detectGameElements(const cv::Mat& input) {
//    GameElements elements;
//
//    cv::Mat hsv, mask;
//    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);
//
//    // Masque pour d�tecter les formes
//    // � ajuster selon la couleur de vos formes sp�cifiques
//    cv::inRange(hsv, BLUE_LOW, BLUE_HIGH, mask);
//
//    // D�tecter la balle (forme circulaire)
//    elements.ballPosition = detectCircle(mask);
//
//    // D�tecter le trou de fin (forme triangulaire)
//    elements.endHolePosition = detectTriangle(mask);
//
//    // D�tecter les trous de mort (formes octogonales)
//    elements.deathHolesPositions = detectOctagons(mask);
//
//    // D�tecter d'autres �l�ments sp�cifiques si n�cessaire
//    // ...
//
//    return elements;
//}