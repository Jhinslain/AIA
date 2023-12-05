#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat preprocess(const cv::Mat& input, cv::Mat& mask, std::vector<cv::Point>& biggest_contour);

#endif // PREPROCESSING_HPP
