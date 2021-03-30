//
// Created by miguel on 30/03/2021.
//

#include "../include/ImageProc.hpp"
#include <vector>

using std::vector;

vector<vector<cv::Point>> ImageProc::findContours(const Mat& src, const Scalar& lower_bound, const Scalar& upper_bound) {
    GpuMat g_frame, hsv;
    Mat mask, mask_out;

    g_frame.upload(src);
    cuda::cvtColor(g_frame, hsv, COLOR_RGB2HSV);
    hsv.download(mask);

    inRange(mask, lower_bound, upper_bound, mask_out);

    vector<vector<Point>> contours;

    cv::findContours(mask_out, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    return contours;
}

void ImageProc::drawContours(const Mat &src, const Mat &contours, bool rectangle, bool cross) {
    if (rectangle) {

    } else {
        cv::drawContours(src, contours, -1, Scalar(0, 255, 255), 1);
    }

    if (cross) {

    }
}

