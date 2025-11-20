#include "WasteBin.h"
#include <iomanip> // For std::setw (formatting)

// ==========================================
// TrashItem Implementations
// ==========================================
TrashItem::TrashItem(string name, string type, double w) {
    itemName = name;
    wasteType = type;
    weightKg = w;
    next = nullptr;
}

TrashItem::~TrashItem() {
    // Logic happens when item is deleted
    cout << "  [Recycling Process]: " << itemName << " is being processed." << endl;
}

// ==========================================
// WasteBinList Implementations
// ==========================================
WasteBinList::WasteBinList() {
    head = nullptr;
    itemCount = 0;
    totalWeight = 0.0;
    cout << ">>> MUIC Green Waste Bin Initialized <<<" << endl;
}

WasteBinList::~WasteBinList() {
    cout << "\n>>> Emptying the Waste Bin (Destructor Called) <<<" << endl;
    TrashItem* current = head;
    while (current != nullptr) {
        TrashItem* nextNode = current->next;
        delete current; // Triggers TrashItem destructor
        current = nextNode;
    }
}

void WasteBinList::throwTrash(string name, string type, double weight) {
    TrashItem* newItem = new TrashItem(name, type, weight);

    // Update stats
    itemCount++;
    totalWeight += weight;

    // Linked List Insertion (at end)
    if (head == nullptr) {
        head = newItem;
    } else {
        TrashItem* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

void WasteBinList::inspectBin() {
    if (head == nullptr) {
        cout << "The bin is empty." << endl;
        return;
    }

    cout << "\n--- Detailed Waste Log (Linked List Traversal) ---" << endl;
    cout << left << setw(20) << "Item Name" 
         << setw(15) << "Type" 
         << setw(10) << "Weight(kg)" << endl;
    cout << "----------------------------------------------" << endl;

    TrashItem* temp = head;
    while (temp != nullptr) {
        cout << left << setw(20) << temp->itemName 
             << setw(15) << temp->wasteType 
             << setw(10) << temp->weightKg << endl;
        temp = temp->next;
    }
    cout << "----------------------------------------------\n" << endl;
}

void WasteBinList::separateWaste(string targetType) {
    cout << ">>> Sorting Line: Searching for [" << targetType << "] <<<" << endl;
    TrashItem* temp = head;
    bool found = false;
    int countType = 0;

    while (temp != nullptr) {
        if (temp->wasteType == targetType) {
            cout << " - Found: " << temp->itemName << endl;
            found = true;
            countType++;
        }
        temp = temp->next;
    }
    
    if (found) {
        cout << "   (Total " << targetType << " items found: " << countType << ")" << endl;
    } else {
        cout << " - No " << targetType << " waste found." << endl;
    }
    cout << endl;
}

void WasteBinList::showStats() {
    cout << "======================================" << endl;
    cout << "       MUIC GREEN SUMMARY REPORT      " << endl;
    cout << "======================================" << endl;
    cout << left << setw(25) << "Total Items Collected:" << itemCount << endl;
    cout << left << setw(25) << "Total Waste Weight:" << totalWeight << " kg" << endl;
    cout << "======================================\n" << endl;
}