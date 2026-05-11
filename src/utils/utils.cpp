#include <iostream>
#include "utils.h"
#include "../models/Gardener.h"
#include "../models/Workshop.h"
using namespace std;

bool isValidName(string name) {
    return !name.empty();
}

int getValidIntChoice(int minVal, int maxVal, const string& prompt) {
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

// ---For Module 3---
vector<Supply> filterBySeason(vector<Supply>& allSupplies, string season){
    vector<Supply> filtered;

    for (Supply s : allSupplies) {
        if (season == "summer" && s.seasons.su) filtered.push_back(s);
        else if (season == "winter" && s.seasons.wi) filtered.push_back(s);
        else if (season == "autumn" && s.seasons.au) filtered.push_back(s);
        else if (season == "spring" && s.seasons.sp) filtered.push_back(s);
    }
    return filtered;
}

void printBestComb(vector<Supply>& result, int budget) {
    if (result.empty()) {
        cout << "No supplies fit within the budget." << endl;
        return;
    }

    int totalCost = 0, totalBenefit = 0;
    cout << "\n===== Best Supply Combination =====" << endl;
    for (auto& s : result) {
        cout << "- " << s.name
             << " | Price: "   << s.price
             << " | Benefit: " << s.benefitScore << endl;
        totalCost    += s.price;
        totalBenefit += s.benefitScore;
    }
    cout << "-----------------------------------" << endl;
    cout << "Budget:        " << budget       << endl;
    cout << "Total Cost:    " << totalCost    << endl;
    cout << "Total Benefit: " << totalBenefit << endl;
    cout << "===================================" << endl;
}

// ---For Module 2---

void showGardener(const Gardener& g) {
    cout << "  ID     : " << g.id << "\n";
    cout << "  Name   : " << g.name << "\n";
    cout << "  Status : " << (g.isWorking ? "Currently Working" : "Available") << "\n";
}

void showWorkshop(const Workshop& w) {
    cout << "┌─────────────────────────────┐\n";
    cout << "  Workshop #" << w.no << ": " << w.name << "\n";
    cout << "  Timing    : " << w.timing << "\n";
    cout << "  Slots     : " << w.remainingSlots << " / " << w.totalSlots << " remaining\n";

    if (w.remainingSlots == 0)
        cout << "  Status    : FULL\n";
    else if ((double)w.remainingSlots / w.totalSlots <= 0.3)
        cout << "  Status    : ⚠ Limited Spaces!\n";
    else
        cout << "  Status    : Open\n";

    cout << "  Registered Gardeners (" << w.registrations.size() << "):\n";
    if (w.registrations.empty()) {
        cout << "    (none yet)\n";
    } else {
        for (const Gardener& g : w.registrations) {
            cout << "  ───────────\n";
            showGardener(g);
        }
    }
    cout << "└─────────────────────────────┘\n";
}