#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

// Function prototypes
void addName(string* &roster, int &numNames, int &maxSize);
void saveRoster(const string* roster, const int numNames);
void readRoster(string* &roster, int &numNames, int &maxSize);
void displayNames(const string* roster, const int numNames);
void searchRoster(const string* roster, const int numNames);
void deleteRoster(string* &roster, int &numNames, int &maxSize);

int main() {
    // Initialize roster variables
    string* roster = nullptr;
    int numNames = 0;
    int maxSize = 0;
    
    // Display menu
    int choice = 0;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add a name" << endl;
        cout << "2. Save roster to file" << endl;
        cout << "3. Read roster from file" << endl;
        cout << "4. Display all names in alphabetical order" << endl;
        cout << "5. Search for a name" << endl;
        cout << "6. Delete roster" << endl;
        cout << "7. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        // Execute choice
        switch (choice) {
            case 1:
                addName(roster, numNames, maxSize);
                break;
            case 2:
                saveRoster(roster, numNames);
                break;
            case 3:
                readRoster(roster, numNames, maxSize);
                break;
            case 4:
                displayNames(roster, numNames);
                break;
            case 5:
                searchRoster(roster, numNames);
                break;
            case 6:
                deleteRoster(roster, numNames, maxSize);
                break;
            case 7:
                // Do nothing, loop will exit
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
                break;
        }

        // Print newline to separate menu choices
        cout << endl;
    } while (choice != 7);

    // Delete dynamically allocated memory
    delete[] roster;

    return 0;
}

void addName(string* &roster, int &numNames, int &maxSize) {
    // If roster is empty, allocate memory for initial roster size
    if (roster == nullptr) {
        maxSize = 5;
        roster = new string[maxSize];
    }
    
    // Check if roster is full and needs to be resized
    if (numNames == maxSize) {
        // Double roster size
        maxSize *= 2;
        string* tempRoster = new string[maxSize];

        // Copy existing roster to new array
        for (int i = 0; i < numNames; i++) {
            tempRoster[i] = roster[i];
        }

        // Delete old roster and set pointer to new array
        delete[] roster;
        roster = tempRoster;
    }
    
    // Prompt user for name and add to roster
    string name;
    cout << "Enter a name: ";
    cin >> name;
    roster[numNames] = name;
    numNames++;
    
    // Sort roster in alphabetical order
    sort(roster, roster + numNames);
}
void saveRoster(const string* roster, const int numNames) {
    // Open file for writing
    ofstream outFile("roster.txt");
    
    // Check if file was successfully opened
    if (!outFile.is_open()) {
        cout << "Error: could not open file for writing." << endl;
        return;
    }
    outFile << numNames << endl;
    // Write each name to file
    for (int i = 0; i < numNames; i++) {
        outFile << roster[i] << endl;
    }
    
    // Close file
    outFile.close();
    
    cout << "Roster saved to file." << endl;
}

void readRoster(string* &roster, int &numNames, int &maxSize) {
    // Prompt user for filename
    string filename;
    cout << "Enter the filename to read from: ";
    cin >> filename;
    
    // Attempt to open file
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }
    delete[] roster;
    roster = nullptr;
    // Read number of names from file
    int fileNumNames;
    inputFile >> fileNumNames;
    // Resize the roster
    maxSize = max(5, fileNumNames);
    roster = new string[maxSize];
    
    // Read names from file and add to roster
    for (int i = 0; i < fileNumNames; i++) {
        string name;
        inputFile >> name;
        roster[i] = name;
    }

    // Update numNames variable to reflect number of names read from file
    numNames = fileNumNames;

    // Sort roster in alphabetical order
    sort(roster, roster + numNames);

    cout << "Roster successfully read from file " << filename << endl;
}
void displayNames(const string* roster, const int numNames) {
    // Check if roster is empty
    if (numNames == 0) {
        cout << "Roster is empty." << endl;
        return;
    }

    // Print each name in the roster in alphabetical order
    cout << "Roster:" << endl;
    for (int i = 0; i < numNames; i++) {
        cout << roster[i] << endl;
    }
}
void searchRoster(const string* roster, const int numNames) {
    // Prompt user for name to search
    string searchName;
    cout << "Enter a name to search: ";
    cin >> searchName;

    // Check if name was found and print result
    if (binary_search(roster, roster + numNames, searchName)) {
        cout << searchName << " was found in the roster." << endl;
    } else {
        cout << searchName << " was not found in the roster." << endl;
    }
}
void deleteRoster(string* &roster, int &numNames, int &maxSize) {
    // Delete dynamically allocated memory and reset variables
    delete[] roster;
    roster = nullptr;
    numNames = 0;
    maxSize = 0;

    cout << "Roster deleted." << endl;
}