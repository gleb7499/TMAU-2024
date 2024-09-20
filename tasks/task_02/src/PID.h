#ifndef PID_S
#define PID_S

#include "models.h"
#include <vector>

class PID {
private:
    double kp;
    double ki;
    double kd;
    std::vector <double> control_signals;

public:
    PID(double kp, double ki, double kd);
    void calculate(const std::vector <double>& error);
    std::vector<double> getControlSignals() const;
};

#endif //PID_S