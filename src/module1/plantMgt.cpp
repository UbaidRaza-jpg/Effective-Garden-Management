#include <iostream>
#include "../utils/utils.h" // ../ means go back one folder
using namespace std;

struct Plant {
    string name;
    int growthRate;
    int sunlightHours;
    int waterLevel;
    int avlHeight;
    Plant* left;
    Plant* right;
};

string getStatus(int g) {
    if (g >= 7) return "Thriving";
    if (g <= 3) return "Struggling";
    return "Normal";
}


Plant takeInput() {
    Plant p;
    p.name = getValidName("Enter Plant Name: ");
    p.growthRate = getValidIntChoice(1, 10, "Enter Growth Rate (1-10): ");
    p.sunlightHours = getValidIntChoice(0, 24, "Enter Daily Sunlight Hours: ");
    p.waterLevel = getValidIntChoice(1, 10, "Enter Water Level (1-10): ");
    return p;
}

void printPlant(Plant* p) {
    if (!p) return;
    cout << "Name: " << p->name << "\n";
    cout << "Growth Rate: " << p->growthRate << " (" << getStatus(p->growthRate) << ")\n";
    cout << "Sunlight Hours: " << p->sunlightHours << " hrs\n";
    cout << "Water Level: " << p->waterLevel << "/10\n";
}


/* ---AVL Functions--- */
int maxOf(int a, int b) { return (a > b) ? a : b; }

int getAvlHeight(Plant* node) { return (node == nullptr) ? 0 : node->avlHeight; }

int getBalance(Plant* node) { return (node == nullptr) ? 0 : getAvlHeight(node->left) - getAvlHeight(node->right); }

Plant* rightRotate(Plant* y) {
    Plant* x = y->left;
    Plant* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->avlHeight = 1 + maxOf(getAvlHeight(y->left), getAvlHeight(y->right));
    x->avlHeight = 1 + maxOf(getAvlHeight(x->left), getAvlHeight(x->right));
    return x;
}

Plant* leftRotate(Plant* x) {
    Plant* y = x->right;
    Plant* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->avlHeight = 1 + maxOf(getAvlHeight(x->left), getAvlHeight(x->right));
    y->avlHeight = 1 + maxOf(getAvlHeight(y->left), getAvlHeight(y->right));
    return y;
}

Plant* insertPlant(Plant* root, Plant newPlant) {
    if (root == nullptr) {
        Plant* newNode = new Plant(newPlant);
        newNode->avlHeight = 1;
        newNode->left = newNode->right = nullptr;
        cout << "Plant added successfully!\n";
        return newNode;
    }

    if (newPlant.name < root->name)
        root->left = insertPlant(root->left, newPlant);
    else if (newPlant.name > root->name)
        root->right = insertPlant(root->right, newPlant);
    else {
        cout << "Plant '" << newPlant.name << "' already exists!\n";
        return root;
    }

    root->avlHeight = 1 + maxOf(getAvlHeight(root->left), getAvlHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && newPlant.name < root->left->name)
        return rightRotate(root);
    if (balance < -1 && newPlant.name > root->right->name)
        return leftRotate(root);
    if (balance > 1 && newPlant.name > root->left->name) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && newPlant.name < root->right->name) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Plant* searchPlant(Plant* root, string name) {
    if (root == nullptr || root->name == name) return root;
    return (name < root->name) ? searchPlant(root->left, name) : searchPlant(root->right, name);
}

void updatePlant(Plant* root, string name) {
    Plant* plant = searchPlant(root, name);
    if (!plant) {
        cout << "Plant '" << name << "' not found!\n";
        return;
    }
    cout << "\n--- Before Update ---\n";
    cout << "Growth Rate: " << plant->growthRate << " (" << getStatus(plant->growthRate) << ")\n";
    if (plant->growthRate <= 3) {
        plant->growthRate += 2;
    } else if (plant->growthRate <= 6) {
        plant->growthRate += 1;
    } else {
        cout << "Plant is already Thriving! No update needed.\n";
        return;
    }
    if (plant->growthRate > 10)
        plant->growthRate = 10;

    cout << "\n--- After Update ---\n";
    cout << "Growth Rate: " << plant->growthRate << " (" << getStatus(plant->growthRate) << ")\n";
}

// Daily growth tracking function
void dailyGrowthUpdate(Plant* root) {
    if (!root) return;
    dailyGrowthUpdate(root->left);

    if (root->sunlightHours >= 6 && root->waterLevel >= 5)
        root->growthRate++;
    else
        root->growthRate--;

    if (root->growthRate > 10)
        root->growthRate = 10;
    if (root->growthRate < 1)
        root->growthRate = 1;

    dailyGrowthUpdate(root->right);
}

void displayPlants(Plant* root) {
    if (!root) return;
    displayPlants(root->left);
    cout << "----------------------------------------\n";
    printPlant(root);
    cout << "----------------------------------------\n";
    displayPlants(root->right);
}

void showThrivingPlants(Plant* root) {
    if (!root) return;
    showThrivingPlants(root->left);
    if (root->growthRate >= 7)
        cout << " - " << root->name << " (Growth Rate: " << root->growthRate << ")\n";
    showThrivingPlants(root->right);
}

void showStrugglingPlants(Plant* root) {
    if (!root) return;
    showStrugglingPlants(root->left);
    if (root->growthRate <= 3)
        cout << " - " << root->name << " (Growth Rate: " << root->growthRate << ")\n";
    showStrugglingPlants(root->right);
}


/* ---main function for this module--- */ 
void runPlantMgt(){

    Plant* root = nullptr;
    int choice;

    do {
        cout << "\n===== PLANT MANAGEMENT SYSTEM (AVL TREE) =====\n";
        cout << "1. Add Plant\n";
        cout << "2. Search Plant\n";
        cout << "3. Update Plant\n";
        cout << "4. Daily Growth Update\n";
        cout << "5. Display All Plants\n";
        cout << "6. Show Thriving Plants\n";
        cout << "7. Show Struggling Plants\n";
        cout << "8. Exit\n";
        choice = getValidIntChoice(1, 8, "Enter your choice: ");

        switch (choice) {
            case 1:
                root = insertPlant(root, takeInput());
                break;
            case 2: {
                string name = getValidName("Enter Plant Name: ");
                Plant* found = searchPlant(root, name);
                
                if (found) { cout << "Plant Found!\n"; printPlant(found); }
                else cout << "Plant not found.\n";
                break;
            }
            case 3: {
                string name = getValidName("Enter Plant Name to update: ");
                updatePlant(root, name);
                break;
            }
            case 4:
                if (!root) cout << "No plants in the system.\n";
                else {
                    dailyGrowthUpdate(root);
                    cout << "Daily growth updated!\n";
                }
                break;
            case 5:
                if (!root) cout << "No plants in the system.\n";
                else displayPlants(root);
                break;
            case 6:
                if (!root) cout << "No plants in the system.\n";
                else showThrivingPlants(root);
                break;
            case 7:
                if (!root) cout << "No plants in the system.\n";
                else showStrugglingPlants(root);
                break;
            case 8:
                cout << "Exiting system. Goodbye!\n";
        }
    } while (choice != 8);
    
}