#include "preprocessing.hpp"

cv::Mat preprocess(const cv::Mat& input, cv::Mat& mask, std::vector<cv::Point>& biggest_contour) {
    cv::Mat gray, norm, blurred, binary;

    //--- 1. Pr�paration et pr�traitement de l'image ---//
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY); // Convertir en niveaux de gris
    cv::equalizeHist(gray, norm); // �galiser l'histogramme
    cv::GaussianBlur(norm, blurred, cv::Size(5, 5), 1.5, 1.5); // Flou gaussien
    cv::adaptiveThreshold(blurred, binary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 11, 2); // Seuillage

    //--- 2. Morphologie pour r�duire le bruit ---//
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, binary, cv::MORPH_OPEN, element); // Op�ration d'ouverture

    //--- 3. Correction gamma de l'image ---//
    cv::Mat gammaCorrected;
    norm.convertTo(norm, CV_32F, 1.0 / 255.0);
    cv::pow(norm, 0.5, gammaCorrected);
    gammaCorrected.convertTo(gammaCorrected, CV_8U, 255.0);

    //--- 4. D�tection des contours ---//
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    double max_area = 0;
    std::vector<cv::Point> current_biggest_contour;
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area > max_area) {
            max_area = area;
            current_biggest_contour = contour;
        }
    }

    //--- 5. V�rification de la forme du contour ---//
    std::vector<cv::Point> approx;
    //modification du seuillage possible
    cv::approxPolyDP(current_biggest_contour, approx, 0.02 * cv::arcLength(current_biggest_contour, true), true);

    // V�rifier s'il y a 4 coins
    if (approx.size() != 4) {
        // Si le contour n'a pas 4 coins, vous pouvez le rejeter ou prendre d'autres mesures
        return blurred; // Par exemple, retourner une image vide ou prendre une autre action
    }

    // Apr�s avoir trouv� le plus grand contour et l'avoir approxim�
    std::vector<cv::Point> sortedCorners(4);
    if (approx.size() == 4) {
        // Trier les coins
        sort(approx.begin(), approx.end(), [](const cv::Point& a, const cv::Point& b) {
            return a.y < b.y;
            });

        if (approx[0].x < approx[1].x) {
            sortedCorners[0] = approx[0]; // Coin sup�rieur gauche
            sortedCorners[1] = approx[1]; // Coin sup�rieur droit
        }
        else {
            sortedCorners[0] = approx[1]; // Coin sup�rieur gauche
            sortedCorners[1] = approx[0]; // Coin sup�rieur droit
        }

        if (approx[2].x < approx[3].x) {
            sortedCorners[2] = approx[2]; // Coin inf�rieur gauche
            sortedCorners[3] = approx[3]; // Coin inf�rieur droit
        }
        else {
            sortedCorners[2] = approx[3]; // Coin inf�rieur gauche
            sortedCorners[3] = approx[2]; // Coin inf�rieur droit
        }

        // Afficher les coins sur l'image et imprimer les coordonn�es
        for (int i = 0; i < 4; i++) {
            cv::circle(input, sortedCorners[i], 5, cv::Scalar(0, 0, 255), -1);
            std::cout << "Coin " << i << ": (" << sortedCorners[i].x << ", " << sortedCorners[i].y << ")" << std::endl;
        }
    }

    //--- 6. Comparaisons et mises � jour du contour ---//
    const double MIN_AREA = 1000.0;
    double maxMove = 30.0;
    double maxAreaDifference = 500.0;
    double maxShapeDifference = 0.3;

    bool isCloseEnough = true;
    bool isSimilarArea = true;
    bool isSimilarShape = true;

    if (!biggest_contour.empty() && !current_biggest_contour.empty()) {
        // V�rification de la proximit�
        cv::Moments m1 = cv::moments(biggest_contour, false);
        cv::Point center1(m1.m10 / m1.m00, m1.m01 / m1.m00);

        cv::Moments m2 = cv::moments(current_biggest_contour, false);
        cv::Point center2(m2.m10 / m2.m00, m2.m01 / m2.m00);

        double dist = cv::norm(center1 - center2);
        isCloseEnough = dist <= maxMove;


        // Comparaison de Forme
        double similarity = cv::matchShapes(biggest_contour, current_biggest_contour, cv::CONTOURS_MATCH_I1, 0);
        isSimilarShape = similarity < maxShapeDifference;

    }

    if (max_area > MIN_AREA && isCloseEnough && isSimilarArea && isSimilarShape) {
        biggest_contour = current_biggest_contour;
    }

    //--- 7. Cr�ation du masque bas� sur le contour ---//
    mask = cv::Mat::zeros(input.size(), CV_8UC1);
    if (!biggest_contour.empty()) {
        cv::drawContours(mask, std::vector<std::vector<cv::Point>>(1, biggest_contour), -1, cv::Scalar(255), cv::FILLED);
        cv::Scalar color = cv::Scalar(0, 255, 0); // Couleur verte pour la visualisation
        cv::drawContours(input, std::vector<std::vector<cv::Point>>(1, biggest_contour), -1, color, 2); // Dessiner le contour
    }

    return blurred;
}
