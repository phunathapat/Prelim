//runcode = make compile run


#include "WasteBin.h"
#include <iostream>
#include <limits> // Required for clearing input buffer

using namespace std;

int main() {
    WasteBinList myBin;
    
    string inputName;
    string inputType;
    double inputWeight;
    string continueChoice;

    cout << "=============================================" << endl;
    cout << "   MUIC GREEN WASTE SYSTEM - DATA ENTRY" << endl;
    cout << "=============================================" << endl;

    while (true) {
        // 1. Input Item Name (Using getline to allow spaces, e.g., "Amazon Cafe Cup")
        cout << "\n> Enter Item Name (or type 'exit' to finish): ";
        getline(cin, inputName);

        // Check exit condition
        if (inputName == "exit" || inputName == "Exit") {
            break;
        }

        // 2. Input Waste Type
        cout << "> Enter Waste Type (General/Recyclable/Organic/Hazardous): ";
        cin >> inputType;

        // 3. Input Weight
        cout << "> Enter Weight (kg): ";
        cin >> inputWeight;

        // --- CRITICAL STEP ---
        // cin leaves a 'newline' character in the buffer. 
        // We must clear it, otherwise the next 'getline' will skip automatically.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        // 4. Add to Linked List
        myBin.throwTrash(inputName, inputType, inputWeight);
        cout << "   [+] Item added successfully!" << endl;
    }

    // Show the Summary Table
    cout << "\n\nGenerating Report..." << endl;
    myBin.showStats();
    myBin.inspectBin();

    // Interactive Separation
    cout << "Would you like to filter by waste type? (y/n): ";
    char filterChoice;
    cin >> filterChoice;

    if (filterChoice == 'y' || filterChoice == 'Y') {
        cout << "Enter type to search (e.g., Recyclable): ";
        string searchType;
        cin >> searchType;
        myBin.separateWaste(searchType);
    }

    cout << "Program Finished." << endl;
    return 0;
}