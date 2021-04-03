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

double compute_ball_err_s(const vector<Point>& contour, int cam_width_center, double kp) {
    vector<int> ball_centers = ImageProc::getContourCenter(contour);

    double err = (cam_width_center - ball_centers[0]);

    ball_centers.clear();

    return err * kp;
}

int main() {
    Robot robot(
            SAMPLING_RATE,
            2,
            .031
    );

    //namedWindow("output", WINDOW_NORMAL);

    int state = 0,
            cam_width_center = 1280 / 2;

    double s = -1,
            ball_err,
            target_err = 100,
            v_ref = 9.0;

    while (robot.run() != -1) {
        Mat image = robot.getCameraImage();

        vector<vector<Point>> ball_contours = ImageProc::findContours(
                image,
                Scalar(105, 37, 0),
                Scalar(138, 238, 255)
        );

        vector<vector<Point>> target_contours = ImageProc::findContours(
                image,
                Scalar(88, 159, 0),
                Scalar(98, 242, 245)
        );

        //ImageProc::drawContours(image, ball_contours, false, true);
        //ImageProc::drawContours(image, target_contours, true, true);

        if (state == 0 && abs(target_err) <= .0) {
            double angle = robot.getCameraPosition(false);

            robot.turnCamera(angle);

            s = .0;
            state = 1;

            ball_contours.clear();
        } else if (state == 1 && abs(ball_err) <= .0) {
            state = 2;
        } else if (state == 2 && robot.getTouchSensorValue() == 1) {
            robot.passiveWait(1);
            state = 3;
        }

        if (state == 0) {
            if (!ball_contours.empty()) {
                vector<int> ball_centers = ImageProc::getContourCenter(ball_contours[0]);

                //double distance = ImageProc::getDistanceByArea(ball_contours[0], Robot::distanceByArea);

                ball_err = (cam_width_center - ball_centers.at(0));

                s = ball_err * 0.005;

                if (!target_contours.empty()) {
                    vector<int> target_centers = ImageProc::getContourCenter(target_contours[0]);

                    target_err = (target_centers[0] - ball_centers[0]);
                    double y = target_err * .05;

                    robot.setVelocities({y, y});

                    target_centers.clear();
                } else {
                    robot.setVelocities({v_ref, v_ref});
                }

                ball_centers.clear();
            }

            robot.setCameraVelocity(s);
        } else if (state == 1) {
            if (!ball_contours.empty()) {
                vector<int> ball_centers = ImageProc::getContourCenter(ball_contours[0]);

                ball_err = (cam_width_center - ball_centers[0]);

                s = .01 * ball_err;

                robot.setVelocities({-s, s});

                ball_centers.clear();
            } else {
                robot.setVelocities({v_ref, -v_ref});
            }
        } else if(state == 2) {
            if (!ball_contours.empty()) {
                s = compute_ball_err_s(ball_contours[0], cam_width_center, .01);

                robot.setVelocities({-s + v_ref, s + v_ref});
            } else {
                robot.setVelocities({v_ref, -v_ref});
            }
        } else {
            robot.setVelocities({.0, .0});
            robot.passiveWait(9999);
        }

        //imshow("output", image);
        //waitKey(SAMPLING_RATE);
    }

    return 0;
}

