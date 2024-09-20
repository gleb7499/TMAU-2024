#include "models.h"
#include "PID.h"
#include <iostream>

using namespace std;

bool choice_input(int &choice);
LinearModel get_liner_model();
NonLinearModel get_nonlinear_model();
PID get_pig();
void start();
vector <double> get_error(const vector <double>& temps_linear, const vector <double>& temps_nonlinear);

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

PID get_pig() {
    double P, I, D;
    input_value(P, "P");
    input_value(I, "I");
    input_value(D, "D");
    PID pid(P, I, D);
    return pid;
}

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