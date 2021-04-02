//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"
#include "opencv4/opencv2/highgui.hpp"

#include <webots/TouchSensor.hpp>

using std::cout;
using std::cerr;
using std::endl;

using webots::TouchSensor;

using namespace cv;

#define SAMPLING_RATE 16

double compute_ball_err(const vector<Point>& contour, int cam_width_center) {
    vector<int> ball_centers = ImageProc::getContourCenter(contour);

    double err = (cam_width_center - ball_centers.at(0));

    return err;
}

int main() {
    Robot robot(
            SAMPLING_RATE,
            2,
            .031
    );

    namedWindow("output", WINDOW_NORMAL);

    int state = 0,
            cam_width_center = 1280 / 2;

    double s = -1,
            ball_err = 100,
            target_err = 100,
            v_ref = 9.0,
            kp = .005;

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

        if (state == 0 && abs(target_err) <= .0) {
            double angle = robot.getCameraPosition(false);

            robot.turnCamera(angle);

            s = .0;
            state = 1;

            kp = .01;
        } else if (state == 1 && abs(ball_err) <= .0) {
            state = 2;
        } else if (state == 2 && robot.getTouchSensorValue() == 1) {
            robot.passiveWait(1);
            state = 3;
        }

        if (!ball_contours.empty()){
            ball_err = compute_ball_err(ball_contours[0], cam_width_center);
        }

        if (state == 0) {
            if (!ball_contours.empty()) {
                s = ball_err * kp;

                if (!target_contours.empty()) {
                    vector<int> target_centers = ImageProc::getContourCenter(target_contours[0]);

                    target_err = (target_centers[0] - ImageProc::getContourCenter(ball_contours[0])[0]);
                    double y = target_err * .05;

                    robot.setVelocities({y, y});
                } else {
                    robot.setVelocities({v_ref, v_ref});
                }
            }

            robot.setCameraVelocity(s);
        } else if (state == 1) {
            if (!ball_contours.empty()) {
                s = ball_err * kp;

                robot.setVelocities({-s, s});
            } else {
                robot.setVelocities({v_ref, -v_ref});
            }
        } else if(state == 2) {
            if (!ball_contours.empty()) {
                s = ball_err * kp;

                robot.setVelocities({-s + v_ref, s + v_ref});
            } else {
                robot.setVelocities({v_ref, -v_ref});
            }
        } else {
            robot.setVelocities({.0, .0});
            robot.passiveWait(9999);
        }

        imshow("output", image);
        waitKey(SAMPLING_RATE);
    }

    return 0;
}

