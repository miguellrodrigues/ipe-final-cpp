//
// Created by miguel on 30/03/2021.
//

#include "../../include/_webots/Encoder.hpp"

using lib::Encoder;

lib::Encoder::Encoder(const string &name, float wheel_radius, unsigned int sampling_rate) : PositionSensor(name),
                                                                                            wheel_radius(wheel_radius) {
    this->enable((int) sampling_rate);
}

double lib::Encoder::getPosition() {
    return (this->getValue() * this->wheel_radius) - this->offset;
}

void lib::Encoder::setOffset(double o) {
    this->offset = o;
}
