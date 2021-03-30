//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_CONTROLLER_HPP
#define IPE_FINAL_CONTROLLER_HPP

#include <webots/Supervisor.hpp>
#include <vector>

using webots::Supervisor;
using webots::Device;
using webots::PositionSensor;
using webots::DistanceSensor;
using webots::LightSensor;
using webots::TouchSensor;
using webots::Motor;

using std::vector;
using std::string;

namespace lib {
    class Controller {
    public:
        explicit Controller(Supervisor *supervisor, unsigned int samplingRate);

        ~Controller();

        double step();

        Supervisor *getSupervisor();

        vector<Device *> getAllDevices();

        vector<Device *> getDeviceByType(unsigned int nodeType);

        vector<PositionSensor *> getPositionSensors();

        vector<DistanceSensor *> getDistanceSensors();

        vector<LightSensor *> getLightSensors();

        vector<TouchSensor *> getTouchSensors();

        vector<Motor *> getMotors();

        Device *getDeviceByName(string name);

        double *getObjectPosition(const string &nodeDef);

        double *getObjectRotation(const string &nodeDef);

        void setObjectPosition(const string &nodeDef, double *position);

        void setObjectRotation(const string &nodeDef, double *rotation);

        double *getObjectVelocity(const string &nodeDef);

        void setupMotors(double position);

        void setMotorVelocity(unsigned int index, double velocity);

        double *getObjectOrientation(const string &nodeDef);

    private:
        Supervisor *supervisor;

        unsigned int samplingRate;
    };
};


#endif //IPE_FINAL_CONTROLLER_HPP
