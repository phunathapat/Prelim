#ifndef WASTE_BIN_H
#define WASTE_BIN_H

#include <string>
#include <iostream>

// Using std:: explicitly in header files is good practice
using namespace std;

// ==========================================
// Class Node: TrashItem
// ==========================================
class TrashItem {
public:
    string itemName;
    string wasteType;
    double weightKg;
    TrashItem* next;

    // Constructor
    TrashItem(string name, string type, double w);
    
    // Destructor
    ~TrashItem();
};

// ==========================================
// Class Linked List: WasteBinList
// ==========================================
class WasteBinList {
private:
    TrashItem* head;
    int itemCount;       // To track how many items are in the bin
    double totalWeight;  // To track total weight

public:
    // Constructor
    WasteBinList();

    // Destructor
    ~WasteBinList();

    // Core Functions
    void throwTrash(string name, string type, double weight);
    void inspectBin();
    void separateWaste(string targetType);
    
    // New Function: Shows the summary table
    void showStats();
};

#endif