//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_IMAGEPROC_HPP
#define IPE_FINAL_IMAGEPROC_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/cudaimgproc.hpp"

#include <vector>

using std::vector;

using namespace cv;
using namespace cv::cuda;

class ImageProc {
public:
    static Mat threshold(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound);

    static vector<vector<Point>> findContours(const Mat &src, const Scalar &lower_bound, const Scalar &upper_bound);

    static vector<int> getContourCenter(const vector<Point> &contour);

    static void
    drawContours(const Mat &src, const vector<vector<Point>> &contours, bool rectangle = false, bool cross = false);

    static void draw_contour_rectangle(const Mat &src, const vector<Point> &contour, const Scalar &color);

    static void draw_contour_cross(const Mat &src, const vector<int> &centers, const Scalar &color);

    static Mat processCameraImage(unsigned int height, unsigned int width, const unsigned char *data);
};

#endif //IPE_FINAL_IMAGEPROC_HPP
