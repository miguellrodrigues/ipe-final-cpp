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
            .031
    );

    namedWindow("output");

    int state = 0;
    double s = -1, ball_err = 100, target_err = 100;

    robot.turn(-90);

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
                Scalar(89, 50, 0),
                Scalar(102, 221, 197)
        );

        ImageProc::drawContours(image, target_contours, true, true);

        imshow("output", image);
        waitKey(16);

        if (state == 0 && abs(target_err) <= .01) {
            s = .0;
            state = 1;
        }

        if (state == 0) {
            if (!ball_contours.empty()) {
                vector<int> ball_centers = ImageProc::getContourCenter(ball_contours[0]);

                ball_err = (320 - ball_centers.at(0));

                s = ball_err * 0.005;

                if (!target_contours.empty()) {
                    vector<int> target_centers = ImageProc::getContourCenter(target_contours[0]);

                    target_err = (target_centers[0] - ball_centers[0]);
                    double y = target_err * .05;

                    robot.setVelocities({y, y});
                }
            }
        } else if (state == 1) {
            // turn robot to align with the ball

            double angle = robot.getCameraPosition(false);

            robot.turn(-angle);

            cout << angle << endl;

            state = 2;
        } else {
            robot.setVelocities({0, 0});
            // kick the ball
        }

        robot.setCameraVelocity(s);
    }

    return 0;
}

