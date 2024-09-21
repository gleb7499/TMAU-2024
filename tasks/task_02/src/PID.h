/**
 * @file PID.h
 *
 * @brief The header file contains the definition of the PID controller.
 *
 * @author Loginov Gleb
 *
 * @version 1.0.0
 *
 * @date 21-09-2024
 */

#ifndef PID_S
#define PID_S

#include "models.h"
#include <vector>

/**
 * @brief The class implements the PID controller.
 *
 * The class contains the method to calculate the control signal by PID.
 */
class PID {
private:
    /// The coefficient K in the PID controller.
    double kp;
    /// The coefficient T in the PID controller.
    double ki;
    /// The coefficient TD in the PID controller.
    double kd;
    /// The vector of control signals.
    std::vector <double> control_signals;

public:
    /**
     * @brief The constructor of the PID controller.
     *
     * @param K The coefficient P in the PID controller.
     * @param T The coefficient I in the PID controller.
     * @param TD The coefficient D in the PID controller.
     */
    PID(double K, double T, double TD);
    /**
     * @brief The method to calculate the control signal by PID.
     *
     * @param error The vector of errors.
     */
    void calculate(const std::vector <double>& error);
    /**
     * @brief The method to get the control signals.
     *
     * @return The vector of control signals.
     */
    std::vector<double> getControlSignals() const;
};

#endif //PID_S
