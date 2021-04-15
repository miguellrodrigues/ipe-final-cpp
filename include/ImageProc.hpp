//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_IMAGEPROC_HPP
#define IPE_FINAL_IMAGEPROC_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include <vector>

using std::vector;

using cv::Mat;
using cv::Scalar;
using cv::Point;
using cv::min;

class ImageProc {
public:
    static Mat threshold(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound);

    static vector<vector<Point>> findContours(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound);

    static vector<int> getContourCenter(const vector<Point> &contour);

    static void draw_contour_rectangle(const Mat &src, const vector<Point> &contour, const Scalar &color);

    static void draw_contour_cross(const Mat &src, const vector<int> &centers, const Scalar &color);

    static void
    drawContours(const Mat &src, const vector<vector<Point>> &contours, bool rectangle = false, bool cross = false);

    static Mat processCameraImage(unsigned int height, unsigned int width, const unsigned char *data, bool log_polar);

    static Mat applyLogPolar(const Mat &src, const int flags = cv::INTER_LINEAR + cv::WARP_FILL_OUTLIERS);

    static double getDistanceByArea(const vector<Point> &contour, double (*function)(double));
};

#endif //IPE_FINAL_IMAGEPROC_HPP
