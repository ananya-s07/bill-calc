#ifndef APPLIANCE_H
#define APPLIANCE_H

#include <string>
using namespace std;


class Appliance {
private:
    string name;
    double power;   // watts
    double hours;   // hours/day
    double dutyCycle; // between 0 and 1(how much time is it acutaly drawing power)

public:
    Appliance(string n, double p, double h, double d);

    string getName();
    double dailyEnergy();            // kWh
    double monthlyEnergy(int days);  // kWh
};

#endif
