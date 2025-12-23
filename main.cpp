#include <iostream>
#include <vector>
#include <fstream>
#include "Appliance.h"
#include <sstream>
using namespace std;
double calculateBill(double units) {
    double bill = 0;

    if (units <= 30) {
        bill = units * 3.34;
    }
    else if (units <= 50) {
        bill = (30 * 3.34)
             + ((units - 30) * 4.27)
             + 71;
    }
    else if (units <= 150) {
        bill = (30 * 3.34)
             + (20 * 4.27)
             + ((units - 50) * 5.23)
             + 124;
    }
    else if (units <= 300) {
        bill = (30 * 3.34)
             + (20 * 4.27)
             + (100 * 5.23)
             + ((units - 150) * 6.61);
    }
    else {
        bill = (30 * 3.34)
             + (20 * 4.27)
             + (100 * 5.23)
             + (150 * 6.61)
             + ((units - 300) * 6.80);
    }

    return bill;
}


vector<Appliance> appliances;

void addAppliance() {
    string name;
    double power, hours,duty;

    cout << "Enter appliance name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter power rating (W): ";
    cin >> power;

    cout << "Enter usage per day (hours): ";
    cin >> hours;

    cout << "Enter duty cycle (0-1): ";
    cin >> duty;
    if (duty <= 0 || duty > 1) {
    cout << "Invalid duty cycle. Setting to 1.0\n";
    duty = 1.0;
}


    appliances.push_back(Appliance(name, power, hours,duty));

    ofstream file("data.txt", ios::app);
    file << name << " " << power << " " << hours << " "<< duty<< endl;
    file.close();

    cout << "Appliance added successfully!\n";
}

void loadFromFile() {
    ifstream file("data.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        string name;
        double power, hours;
        double duty = 1.0;  // default fallback

        stringstream ss(line);
        ss >> name >> power >> hours;

        // Optional fields (future-proof)
        if (!(ss >> duty)) duty = 1.0;

        appliances.push_back(Appliance(name, power, hours, duty));
    }

    file.close();
}
void calculateConsumption() {
    int days;
    double cost;
    double totalEnergy = 0;

    cout << "Enter number of days: ";
    cin >> days;

    cout << "\nAppliance-wise Consumption:\n";
    for (auto &a : appliances) {
        double energy = a.monthlyEnergy(days);
        totalEnergy += energy;
        cout << a.getName() << ": " << energy << " kWh\n";
    }
double bill = calculateBill(totalEnergy);

    cout << "\nTotal Energy: " << totalEnergy << " kWh";
   cout << "\nEstimated Bill (Slab-wise): Rs" << bill << endl;

}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n--- Energy Consumption Calculator ---\n";
        cout << "1. Add Appliance\n";
        cout << "2. Calculate Consumption\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addAppliance(); break;
            case 2: calculateConsumption(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
