#include <iostream>
#include <vector>
#include <string>
#include "../models/Gardener.h"
#include "../models/Workshop.h"
#include "../utils/utils.h"

using namespace std;

// ─────────────────────────────────────────
//  WORKSHOPMANAGEMENT CLASS
// ─────────────────────────────────────────

class WorkshopManagement {
private:

    // ── Hash Table internals ──
    vector<Workshop> table;
    vector<int> state;   // 0 = empty, 1 = occupied, 2 = deleted (for each cell of hash table)
    int capacity;
    int count; // we'll increase it after adding workshop, will be help to check capacity of hashtable

    static const int INITIAL_CAPACITY = 7; // prime number — better distribution

    // ── Hash function ──
    int hash(int key) {
        return key % capacity;
    }

    // ── Linear probing: find index for a key ──
    // Returns index where key exists OR first empty/deleted slot
    int probe(int key) {
        int idx = hash(key);
        int start = idx;

        while (state[idx] == 1 && table[idx].no != key) {
            idx = (idx + 1) % capacity;
            if (idx == start) return -1; // table full (shouldn't happen after rehash)
        }
        return idx;
    }

    // ── Rehash into doubled capacity ──
    void rehash() {
        int newCapacity = capacity * 2 + 1; // keep it odd (closer to prime)
        vector<Workshop> newTable(newCapacity);
        vector<int>      newState(newCapacity, 0);

        for (int i = 0; i < capacity; i++) {
            if (state[i] == 1) {
                int idx = table[i].no % newCapacity;
                // linear probe in new table
                while (newState[idx] == 1)
                    idx = (idx + 1) % newCapacity;
                newTable[idx] = table[i];
                newState[idx] = 1;
            }
        }

        table = newTable;
        state = newState;
        capacity = newCapacity;

        cout << "[Rehash] Table resized to capacity: " << capacity << "\n";
    }

    // ── Load factor check ──
    bool needsRehash() {
        return (double)count / capacity >= 0.7;
    }

public:

    // ── Constructor ──
    WorkshopManagement() {
        capacity = INITIAL_CAPACITY;
        count    = 0;
        table.resize(capacity);
        state.assign(capacity, 0);
    }

    // ────────────────────────────────────────────
    // 1. addWorkshop(Workshop)
    // ────────────────────────────────────────────
    void addWorkshop(Workshop w) {
        if (needsRehash()) rehash();

        int idx = probe(w.no);

        if (idx == -1) {
            cout << "Error: Hash table is full even after rehash.\n";
            return;
        }
        if (state[idx] == 1 && table[idx].no == w.no) {
            cout << "Error: Workshop #" << w.no << " already exists.\n";
            return;
        }

        table[idx] = w;
        state[idx] = 1;
        count++;
        cout << "Workshop \"" << w.name << "\" added successfully.\n";
    }

    // ---input function---
    // ── take input for workshop — also checks uniqueness against hashtable ──
    Workshop inputWorkshop() {
        Workshop w;

        while (true) {
            w.no = getValidInt("Enter Workshop number:");
            

            // uniqueness check
            int idx = probe(w.no);
            if (idx != -1 && state[idx] == 1 && table[idx].no == w.no) {
                cout << "Workshop #" << w.no << " already exists. Try a different number.\n";
            } else {
                break;
            }
        }

        cin.ignore();
        w.name = getValidName("Enter Workshop name: ");
        w.timing = getValidTiming("Enter Timing (HHMM-HHMM): ");
        w.totalSlots = getValidInt("Enter total slots: ");

        w.registrations.resize(w.totalSlots); // fixed-size circular queue (limiting the size of vector)
        w.front  = 0;
        w.isEmpty = true;
        return w;
    }

    // ────────────────────────────────────────────
    // 2. assignSlotToGardener(Gardener)
    //    - inputGardener checks unique ID
    //    - Asks which workshop, uses circular queue
    // ────────────────────────────────────────────

    // Check if gardener ID already exists in any workshop
    bool gardenerExists(int gid) {

        for (int i = 0; i < capacity; i++) {
            if (state[i] != 1) continue;
            Workshop& w = table[i];
            int size = w.totalSlots - w.remainingSlots;
            int idx  = w.front;
            for (int j = 0; j < size; j++) {
                if (w.registrations[idx].id == gid) return true;
                idx = (idx + 1) % w.totalSlots;
            }
        }
        return false;
    }

    // ---input finction---
    Gardener inputGardener() {
        Gardener g;

        while (true) {
            g.id = getValidInt("Enter gardener ID: ");
            
            if (gardenerExists(g.id)) {
                cout << "Gardener ID " << g.id << " already registered somewhere. Try another.\n";
            } else {
                break;
            }
        }

        cin.ignore();
        g.name = getValidName("Enter gardener name: ");
        
        return g;
    }

    void assignSlotToGardener(Gardener g) {
        int wno;
        wno = getValidInt("Enter Workshop Number to register in: ");
        
        
        int idx = probe(wno);

        if (idx == -1 || state[idx] != 1 || table[idx].no != wno) {
            cout << "Workshop #" << wno << " not found.\n";
            return;
        }

        Workshop& w = table[idx];

        if (w.remainingSlots == 0) {
            cout << "Workshop \"" << w.name << "\" is full. Cannot register.\n";
            return;
        }

        // Circular queue: rear = (front + registered count) % totalSlots
        int registered = w.totalSlots - w.remainingSlots;
        int rear = (w.front + registered) % w.totalSlots;

        w.registrations[rear] = g;
        w.remainingSlots--;
        w.isEmpty = false;

        cout << "Gardener \"" << g.name << "\" registered in workshop \"" << w.name << "\". Remaining slots: " << w.remainingSlots << "\n";
    }

    // ────────────────────────────────────────────
    // 3. showWorkshopDetails(int workshopNo)
    // ────────────────────────────────────────────
    void showWorkshopDetails(int workshopNo) {
        int idx = probe(workshopNo);

        if (idx == -1 || state[idx] != 1 || table[idx].no != workshopNo) {
            cout << "Workshop #" << workshopNo << " not found.\n";
            return;
        }

        Workshop& w = table[idx];
        int registered = w.totalSlots - w.remainingSlots;

        cout << "\n┌─────────────────────────────┐\n";
        cout << "  Workshop #" << w.no << ": " << w.name << "\n";
        cout << "  Timing    : " << w.timing << "\n";
        cout << "  Slots     : " << w.remainingSlots << " / " << w.totalSlots << " remaining\n";

        if (w.remainingSlots == 0)
            cout << "  Status    : FULL\n";
        else if ((double)w.remainingSlots / w.totalSlots <= 0.3)
            cout << "  Status    : ⚠ Limited Spaces!\n";
        else
            cout << "  Status    : Open\n";

        cout << "  Registered Gardeners (" << registered << "):\n";

        if (w.isEmpty || registered == 0) {
            cout << "    (none yet)\n";
        } else {
            int i = w.front;
            for (int j = 0; j < registered; j++) {
                Gardener& g = w.registrations[i];
                cout << "  ───────────\n";
                cout << "  ID     : " << g.id   << "\n";
                cout << "  Name   : " << g.name << "\n";
                cout << "  Status : " << (g.isWorking ? "Working" : "Available") << "\n";
                i = (i + 1) % w.totalSlots;
            }
        }

        cout << "└─────────────────────────────┘\n\n";
    }

    // ────────────────────────────────────────────
    // 4. removeGardener(int gardenerId)
    //    Removes from whichever workshop they're in
    // ────────────────────────────────────────────
    void removeGardener(int gardenerId) {
        for (int i = 0; i < capacity; i++) {
            if (state[i] != 1) continue;

            Workshop& w = table[i];
            int registered = w.totalSlots - w.remainingSlots;
            int idx = w.front;

            for (int j = 0; j < registered; j++) {
                if (w.registrations[idx].id == gardenerId) {

                    // Shift everyone after this one back by one (preserve queue order)
                    int cur  = idx;
                    int next = (cur + 1) % w.totalSlots;

                    for (int k = j; k < registered - 1; k++) {
                        w.registrations[cur] = w.registrations[next];
                        cur  = (cur  + 1) % w.totalSlots;
                        next = (next + 1) % w.totalSlots;
                    }

                    w.remainingSlots++;
                    if (w.remainingSlots == w.totalSlots) w.isEmpty = true;

                    cout << "Gardener ID " << gardenerId
                         << " removed from workshop \"" << w.name << "\".\n";
                    return;
                }
                idx = (idx + 1) % w.totalSlots;
            }
        }

        cout << "Gardener ID " << gardenerId << " not found in any workshop.\n";
    }
};

void runWorkshopMgt() {
    WorkshopManagement wm;
    int choice;

    do {
        cout << "\n\n+--------------------------------+\n";
        cout << "|   Workshop Management Menu     |\n";
        cout << "+--------------------------------+\n";
        cout << "|  1. Add Workshop               |\n";
        cout << "|  2. Register Gardener          |\n";
        cout << "|  3. Show Workshop Details      |\n";
        cout << "|  4. Remove Gardener            |\n";
        cout << "|  0. Exit                       |\n";
        cout << "+--------------------------------+\n\n";
        
        choice = getValidIntChoice(0, 4, "Enter choice: ");
        
        switch (choice) {

            case 1: {
                cout << "\n";
                Workshop w = wm.inputWorkshop();
                wm.addWorkshop(w);
                break;
            }

            case 2: {
                cout << "\n";
                Gardener g = wm.inputGardener();
                wm.assignSlotToGardener(g);
                break;
            }

            case 3: {
                cout << "\n";
                int wno;
                wno = getValidInt("Enter workshop number: ");
                
                wm.showWorkshopDetails(wno);
                break;
            }

            case 4: {
                cout << "\n";
                int gid;
                gid = getValidInt("Enetr Gardener ID to remove: ");
                
                wm.removeGardener(gid);
                break;
            }

            case 0:
                cout << "\n";
                cout << "Exiting Workshop Management.\n";
                break;

            default:
                cout << "\n";
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}