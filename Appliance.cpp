#include "Appliance.h"

Appliance::Appliance(string n, double p, double h, double d) {
    name = n;
    power = p;
    hours = h;
    dutyCycle=d;
}

string Appliance::getName() {
    return name;
}

double Appliance::dailyEnergy() {
    return (power * hours * dutyCycle) / 1000.0;
}

double Appliance::monthlyEnergy(int days) {
    return dailyEnergy() * days;
}
