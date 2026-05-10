#include "utils.h"
#include <iostream>
using namespace std;

bool isValidName(string name) {
    return !name.empty();
}

int getInt(int minVal, int maxVal, const string& prompt) {
    int val;
    cout << prompt;
    cin >> val;
    while (cin.fail() || val < minVal || val > maxVal) {
        cout << "Invalid input! Enter between " << minVal << "-" << maxVal << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> val;
    }
    return val;
}

string getValidName(const string& prompt) {
    string name;
    cout << prompt;
    cin.ignore(1000, '\n');
    getline(cin, name);
    while (!isValidName(name)) {
        cout << "Invalid name! Name cannot be empty.\n" << prompt;
        getline(cin, name);
    }
    return name;
}