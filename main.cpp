#include "WasteBin.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    WasteBinList myBin;
    string inputName, inputType;
    double inputWeight;

    cout << "=============================================" << endl;
    cout << "   MUIC GREEN WASTE SYSTEM - SMART BIN" << endl;
    cout << "=============================================" << endl;

    while (true) {
        // 1. รับชื่อ
        cout << "\n> Enter Item Name (or type 'exit' to finish): ";
        getline(cin, inputName);
        if (inputName == "exit" || inputName == "Exit") break;

        // 2. รับประเภท (พร้อมระบบป้องกันการพิมพ์ผิด)
        while (true) {
            cout << "> Enter Waste Type (Recyclable, Organic, General, Hazardous): ";
            cin >> inputType;

            // เช็คคำสะกด (ต้องเป๊ะตามนี้)
            if (inputType == "Recyclable" || inputType == "Organic" || 
                inputType == "General" || inputType == "Hazardous") {
                break; // ถ้าถูก ให้ออกจาก Loop ถามประเภท ไปถามน้ำหนักต่อ
            } else {
                cout << "   [Error] Invalid Type! Please enter only allowed types.\n";
            }
        }

        // 3. รับน้ำหนัก
        cout << "> Enter Weight (kg): ";
        while (!(cin >> inputWeight)) { // กันคนใส่น้ำหนักเป็นตัวหนังสือ
            cout << "   [Error] Invalid Number! Enter Weight (kg): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // เคลียร์ buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        // 4. ใส่ลงถัง (มันจะจัดคิวให้เองในฟังก์ชันนี้)
        myBin.throwTrash(inputName, inputType, inputWeight);
        cout << "   [+] Item added and sorted into queue!" << endl;
    }

    // แสดงผล
    myBin.showStats();
    myBin.inspectBin();

    return 0;
}