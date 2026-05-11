#include <iostream>
#include "utils/utils.h"
using namespace std;

// the linker will find these functions by self,
// as i don't have created .h files and inlcluding a .cpp is bad practice
// thta's why thi approach
void runPlantMgt();
void runWorkshopMgt();
void runResourceProcurement();

int main() {
    int choice;

    do {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║     GARDEN MANAGEMENT SYSTEM         ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║  1. Plant Management                 ║\n";
        cout << "║  2. Workshop Management              ║\n";
        cout << "║  3. Resource Procurement             ║\n";
        cout << "║  0. Exit                             ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        
        choice = getValidIntChoice(0, 3, "Enter choice: ");
        

        switch (choice) {
            case 1:
                runPlantMgt();
                break;
            case 2:
                runWorkshopMgt();
                break;
            case 3:
                runResourceProcurement();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter 0-3.\n";
        }

    } while (choice != 0);
}