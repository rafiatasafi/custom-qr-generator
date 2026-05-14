// QR Code Generator - Final Project
// Authors: [Name 1], [Name 2], [Name 3]
// Course: CS103, Spring 2026
// Sources: claude.ai conversation May 2026
//          https://dev.to/maxart2501/series/13444 (conceptual reference)
//          zyBooks Ch. 9.7 (file I/O)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// =====================
// CLASS DEFINITION
// =====================
class QRCode {
    private:
        vector<string> grid;  // stores the visual grid row by row
        string message;       // original message

    public:

        // Initially planned on using stringToBinary and binaryToString, but it was easier to break down into char-level functions for the grid
        string QRCode::charToBinary(char c);        // converts one char to 8-bit string
        string binary= "";
        int value = (int)c;
        for (int i = 7; i >= 0; i--) {
            if (value % 2 == 0) {
                binary = "0" + binary;
            } else {
                binary = "1" + binary;
            }
            value /= 2;
        }
        return binary;
    }



        string messageToBinary(string msg); // converts whole message to binary
        string encode(string msg);          // full encode pipeline
        string decode();                    // full decode pipeline
        string binaryToChar(string bits);   // converts 8 bits back to char

        // --- PERSON 2: Grid + Checksum ---
        void buildGrid(string binary);      // turns binary into visual grid
        string gridToBinary();              // reads grid back to binary
        void displayGrid();                 // prints grid to terminal
        int checksum(string text);          // sum of ASCII values
        void addSignature();                // adds team signature to grid
        void removeSignature();             // strips signature before decode

        // --- PERSON 3: File I/O + Utility ---
        void saveToFile(string filename);   // writes grid to txt
        void loadFromFile(string filename); // reads grid from txt
        void printSignatureExplanation();   // explains signature to user
};

// =====================
// PERSON 1 FUNCTIONS
// =====================
string QRCode::charToBinary(char c) {
    // TODO
}

string QRCode::messageToBinary(string msg) {
    // TODO
}

string QRCode::encode(string msg) {
    // TODO
}

string QRCode::decode() {
    // TODO
}

string QRCode::binaryToChar(string bits) {
    // TODO
}

// =====================
// PERSON 2 FUNCTIONS
// =====================
void QRCode::buildGrid(string binary) {
    // TODO
}

string QRCode::gridToBinary() {
    // TODO
}

void QRCode::displayGrid() {
    // TODO
}

int QRCode::checksum(string text) {
    // TODO
}

void QRCode::addSignature() {
    // TODO
}

void QRCode::removeSignature() {
    // TODO
}

// =====================
// PERSON 3 FUNCTIONS
// =====================
void QRCode::saveToFile(string filename) {
    // TODO
}

void QRCode::loadFromFile(string filename) {
    // TODO
}

void QRCode::printSignatureExplanation() {
    // TODO
}

// =====================
// MAIN MENU
// =====================
int main() {
    QRCode qr;
    
    while (true) {
        cout << "\n=== QR Code Generator ===" << endl;
        cout << "1. Encode a message" << endl;
        cout << "2. Decode from terminal" << endl;
        cout << "3. Decode from file" << endl;
        cout << "4. Exit" << endl;
        cout << "Pick an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // TODO - Person 1 + 2 + 3 connect here
        }
        else if (choice == 2) {
            // TODO
        }
        else if (choice == 3) {
            // TODO - Person 3
        }
        else if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}