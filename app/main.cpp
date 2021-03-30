//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"
#include "opencv4/opencv2/highgui.hpp"

using std::cout;
using std::endl;

using namespace cv;

int main() {
    Robot robot(
            16,
            2,
            .032
    );

    namedWindow("output");

    while (robot.run() != -1) {
        auto image = robot.getCameraImage();

        auto contours = ImageProc::findContours(image, Scalar(103, 26, 0), Scalar(156, 255, 255));

        ImageProc::drawContours(image, contours, true, true);

        imshow("output", image);
        waitKey(16);
    }

    return 0;
}