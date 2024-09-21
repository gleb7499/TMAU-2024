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
LinearModel get_liner_model(const int &T0);
NonLinearModel get_nonlinear_model(const int &T0);
template<typename T> bool input_value(T &value, const string &name);
void output(const vector <vector<double>>& control_signals, const string& name);

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
    double w;
    int T0;

    cout << "Enter the algorithm of the system functioning\n";
    input_value(w, "w(t)");

    cout << "Enter the step\n";
    input_value(T0, "T0");

    cout << "\tFill in the data for the Linear model\n";
    LinearModel liner_model = get_liner_model(T0);

    vector <double> temps_linear = liner_model.getTemp();

    PID pid_liner, pid_nonlinear;

    pid_liner.calculate(w, T0, temps_linear);

    vector <vector<double>> control_signals_liner = pid_liner.getControlSignals();

    cout << "\tFill in the data for the Nonlinear model\n";
    NonLinearModel non_liner_model = get_nonlinear_model(T0);

    vector <double> temps_nonlinear = non_liner_model.getTemp();

    pid_nonlinear.calculate(w, T0, temps_nonlinear);

    vector <vector<double>> control_signals_nonlinear = pid_nonlinear.getControlSignals();

    output(control_signals_liner, "Linear model");
    output(control_signals_nonlinear, "Nonlinear model");
    
}

void output(const vector <vector<double>>& control_signals, const string& name) {
    cout << "\n\t\t\t\t\t\t\t\tRESULTS\n\n";
    cout << "\t\t\t\t\t\t\t" << name << "\n\n";
    cout.setf(ios::left);
    cout << setw(15) << "TIME (T0)";
    cout << setw(20) << "DEVIATION (e)";
    cout << setw(27) << "OUTPUT VARIABLE (Yt)";
    cout << setw(35) << "CONTROLLING INFLUENCE (Uk)" << endl;
    cout << setfill('=') << setw(85) << "" << setfill(' ') << endl;
    int i = 1;
    for (const auto& signal : control_signals) {
        cout << setw(15) << i++;
        cout << setw(20) << signal[0];
        cout << setw(27) << signal[1];
        cout << setw(35) << signal[2] << endl;
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
LinearModel get_liner_model(const int& T0) {
    double A, B, current_temperature, warm;
    input_value(A, "A");
    input_value(B, "B");
    input_value(current_temperature, "current_temperature");
    input_value(warm, "warm");
    LinearModel model(A, B, current_temperature, warm);
    model.calculate(T0);
    return model;
}

/**
 * @brief The function to input data for the Nonlinear Model.
 *
 * @return The Nonlinear Model.
 */
NonLinearModel get_nonlinear_model(const int& T0) {
    double A, B, C, D, current_temperature, warm;
    input_value(A, "A");
    input_value(B, "B");
    input_value(C, "C");
    input_value(D, "D");
    input_value(current_temperature, "current_temperature");
    input_value(warm, "warm");
    NonLinearModel model(A, B, C, D, current_temperature, warm);
    model.calculate(T0);
    return model;
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
