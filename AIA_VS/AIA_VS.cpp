#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core.hpp"
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "preprocessing.hpp"
#include "element_detection.hpp"
#include "affichage.hpp"



//---------------------//
//------MAIN-----------//
//---------------------//
int main() {

    // 1. INITIALISATION ET VERIFICATION DE LA CAMERA
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la caméra." << std::endl;
        return -1;
    }

    cv::namedWindow("Preprocessed", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Mask Applied", cv::WINDOW_AUTOSIZE);

    cv::Mat prev_frame;
    std::vector<cv::Point2f> corner_points; // Stocker les points d'angle pour le suivi

    cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
    bool isTrackerInitialized = false;

    std::vector<cv::Point2f> prev_points;
    bool isPrevPointsInitialized = false;


    // 2. BOUCLE PRINCIPALE
    while (true) {
        // A. CAPTURE DE FRAME
        cv::Mat frame, preprocessed_frame, image_with_mask;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Frame vide capturé. Fin du programme." << std::endl;
            break;
        }

        // Inverser l'image
        cv::flip(frame, frame, 1); // horizontal flip

        // B. PRETRAITEMENT DE L’IMAGE
        cv::Mat mask;
        std::vector<cv::Point> biggest_contour;
        preprocessed_frame = preprocess(frame, mask, biggest_contour);

        // Appliquez le masque sur l'image prétraitée pour obtenir l'image de la feuille
        cv::bitwise_and(frame, frame, image_with_mask, mask);


        if (!biggest_contour.empty()) {
            if (!isTrackerInitialized) {
                // Initialiser le tracker
                cv::Rect2d bbox = cv::boundingRect(biggest_contour);
                tracker = cv::TrackerKCF::create();
                tracker->init(frame, bbox);
                isTrackerInitialized = true;
            }
            else {
                // Mise à jour du tracker
                cv::Rect2d bbox;
                cv::Rect bbox_int(bbox.x, bbox.y, bbox.width, bbox.height);
                if (tracker->update(frame, bbox_int)) {
                    cv::rectangle(frame, bbox, cv::Scalar(255, 0, 0), 2, 1);
                }
                else {
                    std::cerr << "Suivi échoué. Réinitialisation du tracker." << std::endl;
                    isTrackerInitialized = false;
                }
            }
        }
        else {
            isTrackerInitialized = false;
        }

        //// Suivi optique
        //if (isPrevPointsInitialized) {
        //    std::vector<uchar> status;
        //    std::vector<float> err;
        //    std::vector<cv::Point2f> current_points;
        //    cv::calcOpticalFlowPyrLK(prev_frame, image_with_mask, prev_points, current_points, status, err);

        //    // Dessiner les points suivis
        //    for (size_t i = 0; i < current_points.size(); i++) {
        //        if (status[i]) {
        //            cv::line(frame, prev_points[i], current_points[i], cv::Scalar(0, 255, 0), 2);
        //            cv::circle(frame, current_points[i], 5, cv::Scalar(0, 255, 0), -1);
        //        }
        //    }

        //    prev_points = current_points;
        //}

        if (!biggest_contour.empty() && !isPrevPointsInitialized) {
            // Initialiser les points pour le suivi optique
            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::goodFeaturesToTrack(gray, prev_points, 100, 0.01, 10);
            isPrevPointsInitialized = true;
        }


        
        //Détecte les éléments de la feuille (Ball / Arrival / DeathHoles)
        //Meilleur détection -> ball par forme / DeathHoles par  couleur / Arrival par les 2
        GameElements elements = detectGameElements(image_with_mask);

        // Dessiner la balle
        if (elements.ballPosition != cv::Point2f(-1.0f, -1.0f)) {
            cv::Mat ballImage = drawBall(elements.ballPosition, 5);
            cv::addWeighted(frame, 1.0, ballImage, 1.0, 0, frame);
        }

        // Dessiner les trous de mort (rouges)
        for (const auto& deathHole : elements.deathHolesPositions) {
            cv::Mat deathHoleImage = drawSpike(deathHole, 5);
            cv::addWeighted(frame, 1.0, deathHoleImage, 1.0, 0, frame);
        }

        // Dessiner l'arrivée (triangle vert)
        if (elements.endHolePosition != cv::Point2f(-1.0f, -1.0f)) {
            cv::Mat arrivalImage = drawArrival(elements.endHolePosition, 5);
            cv::addWeighted(frame, 1.0, arrivalImage, 1.0, 0, frame);
        }


        // E. AFFICHAGE DE L’IMAGE
        cv::imshow("Original with tracking", frame);
        cv::imshow("Preprocessed", preprocessed_frame);
        cv::imshow("Mask Applied", image_with_mask);

        char c = (char)cv::waitKey(25);
        if (c == 27) break;

        prev_frame = frame.clone();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

