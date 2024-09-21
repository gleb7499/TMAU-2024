#include <iostream>
#include <vector>
#include "models.h"
#include "PID.h"

using namespace std;

/**
 * @file main.cpp
 *
 * @brief The program implements a controller for a system with two models,
 * a linear and a non-linear one.
 *
 * @author Loginov Gleb
 *
 * @version 1.0.0
 *
 * @date 21-09-2024
 */

void start();
bool choice_input(int &choice);
PID get_pig();
LinearModel get_liner_model();
NonLinearModel get_nonlinear_model();
vector <double> get_error(const vector <double>& temps_linear, const vector <double>& temps_nonlinear);

/**
 * @brief The main function.
 *
 * @return 0 if everything is OK.
 */

/**
 * @brief The array of functions to switch between them.
 */
int main() {
    void (*point[])() = { []() { exit(0); }, start};
    int choice;
    while (true) {
        cout << "\n\tInput choice (0 - exit, 1 - start)\n";
        if (!choice_input(choice)) {
            cerr << "\n\a\t\t***Input value is not correct***\n\n";
            continue;
        }
        point[choice]();
    }
    return 0;
}

/**
 * @brief The function to start the program.
 *
 * The function starts the program, input data for the Linear and Nonlinear models,
 * calculate the error, calculate the control signal by PID and output the results.
 */
void start() {
    cout << "\tFill in the data for the Linear model\n";
    LinearModel liner_model = get_liner_model();
    cout << "\tFill in the data for the Nonlinear model\n";
    NonLinearModel non_liner_model = get_nonlinear_model();

    cout << "\tFill in the data for the Nonlinear model\n";
    PID pid = get_pig();

    vector <double> temps_linear = liner_model.getTemp();
    vector <double> temps_nonlinear = non_liner_model.getTemp();
    vector <double> error = get_error(temps_linear, temps_nonlinear);

    pid.calculate(error);

    vector <double> control_signals = pid.getControlSignals();

    // Output
    cout.setf(ios::left);
    cout << setw(10) << "TIME";
    cout << setw(17) << "LINAR MODEL";
    cout << setw(20) << "NONLINAR MODEL";
    cout << setw(17) << "ERROR";
    cout << setw(19) << "CONTROL SIGNAL" << endl;
    cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
    for (int i = 0; i < control_signals.size(); ++i) {
        cout << setw(10) << (i + 1);
        cout << setw(17) << temps_linear[i];
        cout << setw(20) << temps_nonlinear[i];
        cout << setw(17) << error[i];
        cout << setw(19) << control_signals[i] << endl;
    }
}

/**
 * @brief The template function to input value.
 *
 * @param value The value to input.
 * @param name The name of the value.
 *
 * @return True if everything is OK.
 */
template<typename T> bool input_value(T &value, const string &name) {
    while (true) {
        cout << "Input " << name << ": ";
        if (cin >> value) {
            return true;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "\n\a\t\t***Input value is not correct***\n\n";
        }
    }
}

/**
 * @brief The function to input data for the Linear Model.
 *
 * @return The Linear Model.
 */
LinearModel get_liner_model() {
    double A, B, current_temperature, warm;
    int time;
    input_value(A, "A");
    input_value(B, "B");
    input_value(current_temperature, "current_temperature");
    input_value(warm, "warm");
    input_value(time, "time");
    LinearModel model(A, B, current_temperature, warm);
    model.calculate(time);
    model.print();
    return model;
}

/**
 * @brief The function to input data for the Nonlinear Model.
 *
 * @return The Nonlinear Model.
 */
NonLinearModel get_nonlinear_model() {
    double A, B, C, D, current_temperature, warm;
    int time;
    input_value(A, "A");
    input_value(B, "B");
    input_value(C, "C");
    input_value(D, "D");
    input_value(current_temperature, "current_temperature");
    input_value(warm, "warm");
    input_value(time, "time");
    NonLinearModel model(A, B, C, D, current_temperature, warm);
    model.calculate(time);
    model.print();
    return model;
}

/**
 * @brief The function to calculate the error.
 *
 * @param temps_linear The temperatures of the Linear Model.
 * @param temps_nonlinear The temperatures of the Nonlinear Model.
 *
 * @return The error.
 */
vector <double> get_error(const vector <double>& temps_linear, const vector <double>& temps_nonlinear) {
    if (temps_linear.size() != temps_nonlinear.size()) {
        cerr << "\n\a\t\t*The sizes of the models are not equal*\n\n";
    }
    vector <double> error;
    for (int i = 0; i < temps_linear.size() && i < temps_nonlinear.size(); ++i) {
        error.push_back(temps_linear[i] - temps_nonlinear[i]);
    }
    return error;
}

/**
 * @brief The function to input data for the PID.
 *
 * @return The PID.
 */
PID get_pig() {
    double P, I, D;
    input_value(P, "P");
    input_value(I, "I");
    input_value(D, "D");
    PID pid(P, I, D);
    return pid;
}

/**
 * @brief The function to input choice.
 *
 * @param choice The choice.
 *
 * @return True if everything is OK.
 */
bool choice_input(int &choice) {
    while (true) {
        if (input_value(choice, "choice")) {
            if (choice >= 0 && choice <= 2) {
                return true;
            }
            else {
                cerr << "\n\a\t\t***Input value is not correct***\n\n";
            }
        }
    }
}
