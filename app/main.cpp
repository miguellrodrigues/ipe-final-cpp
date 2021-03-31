//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"
#include "opencv4/opencv2/highgui.hpp"

using std::cout;
using std::cerr;

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
                Scalar(105, 37, 0),
                Scalar(138, 238, 255)
        );

        ImageProc::drawContours(image, ball_contours, false, true);

        vector<vector<Point>> target_contours = ImageProc::findContours(
                image,
                Scalar(84, 0, 0),
                Scalar(100, 255, 152)
        );

        ImageProc::drawContours(image, target_contours, true, true);

        imshow("output", image);
        waitKey(16);

        try {
            vector<int> ball_centers = ImageProc::getContourCenter(ball_contours.at(0));
            vector<int> target_centers = ImageProc::getContourCenter(ball_contours.at(0));

            int x = 640 / 2;

            double err = 0.005 * (x - target_centers.at(0));

            robot.setCameraVelocity(err);
        } catch (Exception &ex) {
            cerr << ex.what();
        }
    }

    return 0;
}

