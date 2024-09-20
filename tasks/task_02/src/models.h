#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <vector>

class ModelingObject {
public:
    virtual void calculate(const int& time) = 0;
    void print(const std::map<int, double>& temps, const std::string& name);
    std::vector<double> getTemp(const std::map<int, double>& temps);
};

class LinearModel : public ModelingObject {
private:
    double A;
    double B;
    double current_temperature;
    double warm;
    std::map<int, double> temps;

public:
    LinearModel(double a, double b, double current_temperature, double warm);
    void calculate(const int& time);
    void print();
    std::vector<double> getTemp();
};

class NonLinearModel : public ModelingObject {
private:
    double A;
    double B;
    double C;
    double D;
    double current_temperature;
    double previous_temperature;
    double warm;
    std::map<int, double> temps;

public:
    NonLinearModel(double A, double B, double C, double D, double current_temperature, double warm);
    void calculate(const int& time);
    void print();
    std::vector<double> getTemp();
};

#endif  // MODELS_H

