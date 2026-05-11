#pragma once
#include<string>
#include<vector>
#include "../models/Supply.h"
using std::string;

bool isValidName(string name);
int getValidIntChoice(int minVal, int maxVal, const string& prompt);
string getValidName(const string& prompt);
vector<Supply> filterBySeason(vector<Supply> allSupplies, string season);
void printBestComb(vector<Supply>& result, int budget);