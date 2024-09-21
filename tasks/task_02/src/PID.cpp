/**
 * @file PID.cpp
 *
 * @brief The file contains the implementation of the PID controller.
 *
 * @author Loginov Gleb
 *
 * @version 1.0.0
 *
 * @date 21-09-2024
 */

#include "PID.h"

/**
 * @brief The constructor of the PID controller.
 *
 * @param K The coefficient P in the PID controller.
 * @param T The coefficient I in the PID controller.
 * @param TD The coefficient D in the PID controller.
 */

PID::PID(double K, double T, double TD) : kp(K), ki(T), kd(TD) {}

/**
 * @brief The method to calculate the control signal by PID.
 *
 * @param error The vector of errors.
 */
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

/**
 * @brief The method to get the control signals.
 *
 * @return The vector of control signals.
 */
std::vector<double> PID::getControlSignals() const {
    return this->control_signals;
}

