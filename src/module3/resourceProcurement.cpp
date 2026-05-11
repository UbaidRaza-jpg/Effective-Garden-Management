#include<vector>
#include "../models/Supply.h"
#include "../utils/utils.h"
using namespace std;


class ResourceProcurement{
    private:
    vector<Supply> allSupplies;
    vector<vector<int>> memo; // don't worry this will be intialized before calling it in the knapsack()
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
