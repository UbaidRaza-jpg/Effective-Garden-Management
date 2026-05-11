#include<iostream>
#include<vector>
#include "../models/Supply.h"
#include "../utils/utils.h"
using namespace std;

class ResourceProcurement{
    private:
    vector<Supply> allSupplies;
    vector<vector<int>> memo; // don't worry, this will be intialized before calling it in the knapsack()
    vector<Supply> selectedSupplies;
    
    // the knapsack logic
    int knapsack(vector<Supply>& s, int budget, int n){
        if(n == 0 || budget == 0) return 0;

        if(memo[n][budget] != -1) return memo[n][budget];
        
        int notTake = knapsack(s, budget, n-1);

        int take = 0;
        if (s[n-1].price <= budget) {
            take = s[n-1].benefitScore + knapsack(s, budget - s[n-1].price, n-1);
        }

        return memo[n][budget] = max(take, notTake);
    }

    // now from our memo we are building the vector of selected supplies
    void findItems(vector<Supply>& s, int budget, int n) {
        if (n == 0 || budget == 0) return;

        int notTake = knapsack(s, budget, n-1);
        int take = 0;

        if (s[n-1].price <= budget) {
            take = s[n-1].benefitScore + knapsack(s, budget - s[n-1].price, n-1);
        }

        if (take > notTake) { // this item was taken            
            selectedSupplies.push_back(s[n-1]);
            findItems(s, budget - s[n-1].price, n-1);
        }
        else { // this item was skipped            
            findItems(s, budget, n-1);
        }
    }
    
public:
    
    // add supply into system
    void addSupply(Supply s){
        allSupplies.push_back(s);
    }

    // main function to get best combination (this will be called in main)
    vector<Supply> getBestCombination(int budget, string season){

        // clear old selected supplies
        selectedSupplies.clear();

        // filter supplies according to season
        vector<Supply> filteredSupplies = filterBySeason(allSupplies ,season);

        int n = filteredSupplies.size();

        // initialize memo table
        memo.resize(n + 1, vector<int>(budget + 1, -1));

        // run knapsack
        knapsack(filteredSupplies, budget, n);

        // build selected supplies vector (memo was built by the above call)
        findItems(filteredSupplies, budget, n);

        return selectedSupplies;
    }

};

void runResourceProcurement() {

    // sample data
    vector<Supply> supplies = {        
        Supply{ "Sunscreen SPF50",      15,     8,      {true,  false,  false,  true }},
        Supply{ "Insect Repellent",     10,     7,      {true,  false,  true,   false}},
        Supply{ "Wool Blanket",         40,     9,      {false, true,   true,   false}},
        Supply{ "Thermal Flask",        25,     8,      {false, true,   true,   true }},
        Supply{ "Rain Poncho",          20,     9,      {false, false,  true,   true }},
        Supply{ "Portable Fan",         30,     7,      {true,  false,  false,  false}},
        Supply{ "First Aid Kit",        35,     10,     {true,  true,   true,   true }},
        Supply{ "Water Purifier",       50,     10,     {true,  false,  true,   false}},
        Supply{ "Snow Boots",           60,     9,      {false, true,   false,  false}},
        Supply{ "Gardening Gloves",     12,     6,      {false, false,  false,  true }},
        Supply{ "Portable Heater",      55,     9,      {false, true,   false,  false}},
        Supply{ "Cooling Towel",        10,     6,      {true,  false,  false,  false}},
        Supply{ "Allergy Medicine",     18,     8,      {false, false,  false,  true }},
        Supply{ "Emergency Rations",    45,     10,     {true,  true,   true,   true }},
        Supply{ "Waterproof Bag",       22,     7,      {true,  false,  true,   true }},
    };
    
    int budget;
    string season;
    ResourceProcurement rp;

    for (auto &s : supplies) {
        rp.addSupply(s);
    }

    cout << "\n===== Resource Procurement System =====\n";
    budget = getValidInt("Enter your budget: ");

    do {
        cout << "Enter season (summer/winter/autumn/spring): ";
        cin >> season;

        // Convert to lowercase so "Summer" or "SUMMER" also works
        for (char& c : season) c = tolower(c);

        if (season == "summer" || season == "winter" ||
            season == "autumn" || season == "spring") {
            break;
        }
        cout << "Invalid! Enter one of: summer, winter, autumn, spring\n";
    } while (true);   

    vector<Supply> best = rp.getBestCombination(budget, season);

    cout << "\n--- Best Supply Combination ---\n";

    if (best.empty()) {
        cout << "No supplies found for the given budget and season.\n";
        return;
    }

    float totalCost = 0;
    int totalBenefit = 0;

    for (auto& s : best) {
        cout << "- " << s.name
             << " | Price: " << s.price
             << " | Benefit Score: " << s.benefitScore
             << "\n";
        totalCost    += s.price;
        totalBenefit += s.benefitScore;
    }

    cout << "\nTotal Cost   : " << totalCost    << "\n";
    cout << "Total Benefit: " << totalBenefit  << "\n";
    cout << "=======================================\n";
}