#include "WasteBin.h"
#include <iomanip>

// --- TrashItem Implementation ---
TrashItem::TrashItem(string name, string type, double w) {
    itemName = name;
    wasteType = type;
    weightKg = w;
    next = nullptr;
}

TrashItem::~TrashItem() {
    // Destructor logic
}

// --- WasteBinList Implementation ---
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
        delete current;
        current = nextNode;
    }
}

// กำหนดลำดับ: Recyclable(1) -> Organic(2) -> General(3) -> Hazardous(4)
int WasteBinList::getPriority(string type) {
    if (type == "Recyclable") return 1;
    if (type == "Organic") return 2;
    if (type == "General") return 3;
    if (type == "Hazardous") return 4;
    return 5; // กรณีหลุดรอดมา (แต่เราจะกันไว้ที่ main แล้ว)
}

void WasteBinList::throwTrash(string name, string type, double weight) {
    TrashItem* newItem = new TrashItem(name, type, weight);
    itemCount++;
    totalWeight += weight;
    
    int newPrio = getPriority(type);

    // กรณี 1: ถังขยะว่าง หรือ ขยะชิ้นนี้สำคัญกว่าชิ้นแรก (เลขน้อยกว่า)
    // เช่น ในถังมี General อยู่ แล้วเราใส่ Recyclable เข้ามา -> Recyclable จะไปแทนที่หัว
    if (head == nullptr || newPrio < getPriority(head->wasteType)) {
        newItem->next = head;
        head = newItem;
    } 
    else {
        // กรณี 2: วิ่งหาตำแหน่งแทรก
        // เราจะวิ่งไปเรื่อยๆ ตราบใดที่ priority ของตัวถัดไป "น้อยกว่าหรือเท่ากับ" ตัวใหม่
        // แปลว่าถ้าเจอ Recycle เหมือนกัน มันจะวิ่งไปต่อท้าย Recycle ตัวสุดท้าย
        TrashItem* current = head;
        while (current->next != nullptr && getPriority(current->next->wasteType) <= newPrio) {
            current = current->next;
        }
        
        // แทรกตรงกลาง หรือ ต่อท้าย
        newItem->next = current->next;
        current->next = newItem;
    }
}

void WasteBinList::inspectBin() {
    if (head == nullptr) {
        cout << "The bin is empty." << endl;
        return;
    }

    cout << "\n--- Current Waste Queue (Auto-Sorted) ---" << endl;
    cout << left << setw(25) << "Item Name" << setw(15) << "Type" << setw(10) << "Weight(kg)" << endl;
    cout << "----------------------------------------------------" << endl;
    TrashItem* temp = head;
    while (temp != nullptr) {
        cout << left << setw(25) << temp->itemName << setw(15) << temp->wasteType << setw(10) << temp->weightKg << endl;
        temp = temp->next;
    }
    cout << "----------------------------------------------------\n" << endl;
}

void WasteBinList::separateWaste(string targetType) {
    cout << ">>> Sorting Line: Searching for [" << targetType << "] <<<" << endl;
    TrashItem* temp = head;
    bool found = false;
    while (temp != nullptr) {
        if (temp->wasteType == targetType) {
            cout << " - Found: " << temp->itemName << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << " - No " << targetType << " waste found." << endl;
    cout << endl;
}

void WasteBinList::showStats() {
    cout << "\n======================================" << endl;
    cout << "       MUIC GREEN SUMMARY REPORT      " << endl;
    cout << "======================================" << endl;
    cout << left << setw(25) << "Total Items Collected:" << itemCount << endl;
    cout << left << setw(25) << "Total Waste Weight:" << totalWeight << " kg" << endl;
    cout << "======================================\n" << endl;
}