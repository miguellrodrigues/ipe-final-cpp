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
        Mat image = robot.getCameraImage();

        vector<vector<Point>> ball_contours = ImageProc::findContours(
                image,
                Scalar(103, 26, 0),
                Scalar(156, 255, 255)
        );

        ImageProc::drawContours(image, ball_contours, false, true);

        vector<vector<Point>> target_contours = ImageProc::findContours(
                image,
                Scalar(65, 0, 0),
                Scalar(98, 223, 255)
        );

        ImageProc::drawContours(image, target_contours, true, true);

        imshow("output", image);
        waitKey(16);

        try {
            vector<int> ball_centers = ImageProc::getContourCenter(ball_contours.at(0));
            vector<int> target_centers = ImageProc::getContourCenter(ball_contours.at(0));

            int x = 640 / 2;

            double err = 0.1 * (x - target_centers.at(0));

            robot.setVelocities({-err, err});
        } catch (Exception &ex) {

        }
    }

    return 0;
}