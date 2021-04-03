//
// Created by miguel on 30/03/2021.
//

#include "../include/ImageProc.hpp"
#include <vector>

using std::vector;

#define center cv::Point2f((float) 1280 / 2, (float) 720 / 2)
#define maxRadius (double) 0.6 * min(center.y, center.x)

Mat ImageProc::threshold(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound) {
    GpuMat g_frame, hsv;
    Mat mask, mask_out;

    g_frame.upload(src);
    cv::cuda::cvtColor(g_frame, hsv, cv::COLOR_RGB2HSV);
    hsv.download(mask);

    inRange(mask, lower_bound, upper_bound, mask_out);

    mask.release();
    g_frame.release();
    hsv.release();

    return mask_out;
}

vector<vector<Point>> ImageProc::findContours(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound) {
    Mat mask = threshold(src, lower_bound, upper_bound);

    vector<vector<Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    mask.release();

    sort(contours.begin(), contours.end(), [](const vector<Point> &one, const vector<Point> &two) {
        return contourArea(one) > contourArea(two);
    });

    return contours;
}

vector<int> ImageProc::getContourCenter(const vector<Point> &contour) {
    if (contour.empty()) {
        return {0, 0};
    }

    cv::Moments m = moments(contour);

    int center_x = (int) (m.m10 / m.m00);
    int center_y = (int) (m.m01 / m.m00);

    return {center_x, center_y};
}

void ImageProc::draw_contour_rectangle(const Mat &src, const vector<Point> &contour, const Scalar &color) {
    cv::Rect rect = boundingRect(contour);

    cv::rectangle(src, rect, color, 1);
}

void ImageProc::draw_contour_cross(const Mat &src, const vector<int> &centers, const Scalar &color) {
    int center_x = centers[0];
    int center_y = centers[1];

    line(src, Point(center_x, center_y + 5), Point(center_x, center_y - 5), color, 1);
    line(src, Point(center_x + 5, center_y), Point(center_x - 5, center_y), color, 1);
}

void ImageProc::drawContours(const Mat &src, const vector<vector<Point>> &contours, bool rectangle, bool cross) {
    if (rectangle) {
        for (const vector<Point> &contour : contours) {
            draw_contour_rectangle(src, contour, Scalar(255, 0, 0));
        }
    } else {
        cv::drawContours(src, contours, -1, Scalar(0, 255, 255), 1);
    }

    if (cross) {
        for (const vector<Point> &contour : contours) {
            draw_contour_cross(src, getContourCenter(contour), Scalar(255, 255, 255));
        }
    }
}

Mat ImageProc::processCameraImage(unsigned int height, unsigned int width, const unsigned char *data, bool log_polar) {
    Mat out = Mat((int) height, (int) width, CV_8UC4, (unsigned *) data);
    if (log_polar) {
        return applyLogPolar(out);
    } else {
        return out;
    }
}

Mat ImageProc::applyLogPolar(const Mat &src, const int flags) {
    Mat log_image, recovered_image;

    warpPolar(src, log_image, cv::Size(), center, maxRadius, flags + cv::WARP_POLAR_LOG); // semilog Polar

    // inverse transform
    warpPolar(log_image, recovered_image, src.size(), center, maxRadius,
              flags + cv::WARP_POLAR_LOG + cv::WARP_INVERSE_MAP);

    return recovered_image;
}

double ImageProc::getDistanceByArea(const vector<Point> &contour, double (*function)(double)) {
    return function(cv::contourArea(contour));
}

