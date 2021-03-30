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
    static vector<vector <cv::Point>> findContours(const Mat& src, const Scalar& lower_bound, const Scalar& upper_bound);

    static void drawContours(const Mat& src, const Mat &contours, bool rectangle=false, bool cross=false)
};

#endif //IPE_FINAL_IMAGEPROC_HPP
