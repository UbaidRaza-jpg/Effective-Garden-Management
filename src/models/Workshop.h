#pragma once
#include "Gardener.h"
#include<string>
#include<vector>
using namespace std;

struct Workshop{
    int no;
    string name;
    string timing;
    int totalSlots = 0;
    int remainingSlots = totalSlots;
    vector<Gardener> registrations;
    int front = 0;
    bool isEmpty = true;
};