//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_ROBOT_HPP
#define IPE_FINAL_ROBOT_HPP

class Robot {
public:
    Robot(unsigned int sampling_rate, unsigned int wheels, float wheel_radius);

private:
    unsigned int sampling_rate;
    unsigned int wheels;

    float wheel_radius;
};

#endif //IPE_FINAL_ROBOT_HPP
