#ifndef WASTE_BIN_H
#define WASTE_BIN_H

#include <string>
#include <iostream>

using namespace std;

class TrashItem {
public:
    string itemName;
    string wasteType;
    double weightKg;
    TrashItem* next;

    TrashItem(string name, string type, double w);
    ~TrashItem();
};

class WasteBinList {
private:
    TrashItem* head;
    int itemCount;
    double totalWeight;

    // Helper: แปลงประเภทขยะเป็นตัวเลขเพื่อจัดลำดับ
    // 1=Recyclable, 2=Organic, 3=General, 4=Hazardous
    int getPriority(string type);

public:
    WasteBinList();
    ~WasteBinList();

    // แก้ไข: ฟังก์ชันนี้จะแทรกตามลำดับความสำคัญทันที
    void throwTrash(string name, string type, double weight);
    
    void inspectBin();
    void separateWaste(string targetType);
    void showStats();
};

#endif