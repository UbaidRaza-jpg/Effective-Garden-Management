#pragma once
#include<string>
#include<vector>
#include "../models/Supply.h"
#include "../models/Gardener.h"
#include "../models/Workshop.h"
using std::string;

bool isValidName(string name);
int getValidIntChoice(int minVal, int maxVal, const string& prompt);
string getValidName(const string& prompt);
vector<Supply> filterBySeason(vector<Supply>& allSupplies, string season);
void printBestComb(vector<Supply>& result, int budget);
void showGardener(const Gardener& g);
void showWorkshop(const Workshop& w);
int getValidInt(const string& prompt);
bool isValidTime(const string& time);
string getValidTiming(const string& prompt);