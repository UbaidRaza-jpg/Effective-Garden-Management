#pragma once
#include <string>
using namespace std;

struct Season {
    bool su = false;
    bool wi = false;
    bool au = false;
    bool sp = false;
};

struct Supply {
    string name;
    float price;
    int benefitScore;
    Season seasons;
};