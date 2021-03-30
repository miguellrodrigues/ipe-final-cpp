//
// Created by miguel on 30/03/2021.
//

#include "../include/ImageProc.hpp"
#include <vector>

using std::vector;

vector<vector<Point>> ImageProc::findContours(const Mat& src, const Scalar& lower_bound, const Scalar& upper_bound) {
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

vector<int> ImageProc::getContourCenter(const vector<Point> &contour) {
    Moments m = moments(contour);

    int center_x = (int) (m.m10 / m.m00);
    int center_y = (int) (m.m01 / m.m00);

    return {center_x, center_y};
}

void ImageProc::draw_contour_rectangle(const Mat& src, const vector<Point>& contour, const Scalar& color) {
    Rect rect = boundingRect(contour);

    cv::rectangle(src, rect, color, 1);
}

void ImageProc::draw_contour_cross(const Mat &src, const vector<int> &centers, const Scalar &color) {
    int center_x = centers.at(0);
    int center_y = centers.at(1);

    line(src, Point(center_x, center_y + 5), Point(center_x, center_y - 5), color, 1);
    line(src, Point(center_x + 5, center_y), Point(center_x - 5, center_y), color, 1);
}

void ImageProc::drawContours(const Mat &src, const vector<vector<Point>> &contours, bool rectangle, bool cross) {
    if (rectangle) {
        for (const vector<Point> & contour : contours) {
            draw_contour_rectangle(src, contour, Scalar(50, 150, 0));
        }
    } else {
        cv::drawContours(src, contours, -1, Scalar(0, 255, 255), 1);
    }

    if (cross) {
        for (const vector<Point> & contour : contours) {
            draw_contour_cross(src, getContourCenter(contour), Scalar(255, 255, 255));
        }
    }
}

Mat ImageProc::processWebotsCameraImage(unsigned int width, unsigned int height, const unsigned char *data) {
    Mat out = Mat(width, height, CV_8UC4, (unsigned *)data);
    return out;
}

