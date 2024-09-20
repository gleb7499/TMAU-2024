#include "PID.h"

PID::PID(double kp, double ki, double kd) : kp(kp), ki(ki), kd(kd) {}

void PID::calculate(const std::vector<double> &error) {
    double integralError = 0.0;
    double derivativeError = 0.0;
    double controlSignal = 0.0;
    double previous_error = 0.0;
    for (int i = 0; i < error.size(); ++i) {
        integralError += error[i];
        derivativeError = error[i] - previous_error;
        previous_error = error[i];
        controlSignal = kp * error[i] + ki * integralError + kd * derivativeError;
        this->control_signals.push_back(controlSignal);
    }
}

std::vector<double> PID::getControlSignals() const {
    return this->control_signals;
}
