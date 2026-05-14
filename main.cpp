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

// Constants
const int BITS = 8;      // number of bits per character
const char ZERO = ' ';   // visual representation of 0
const char ONE = '█';    // Unicode full block character for visual representation of 1

// =====================
// CLASS DEFINITION
// =====================
class QRCode {
    private:
        vector<string> grid;  // stores the visual grid row by row
        string message;       // original message

    public:
        // Constructor
        QRCode() {
            grid.clear();
            message = "";
        }

        // --- PERSON 1: Encoding + Decoding ---
        string charToBinary(char c);        // converts char to 8-bit binary
        string messageToBinary(string msg); // converts entire message to binary
        string encode(string msg);          // main encoding function
        string decode();                    // main decoding function
        string binaryToChar(string bits);   // converts 8-bit binary to char

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

// Note: For simplicity, we will assume the message only contains standard ASCII characters (0-127).
// Thought process for charToBinary:
// - We want to convert a character (like 'A') into its binary representation (like "01000001").
// - We can do this by repeatedly dividing the ASCII value of the character by 2 and recording the remainders.
// - We need to ensure we get exactly 8 bits, so we can pad with leading zeros if necessary.
// Source for charToBinary logic: https://www.geeksforgeeks.org/convert-character-binary-string-cpp/
string QRCode::charToBinary(char c) {
    string binary = "";
    int value = (int)c;         // convert char to its ASCII integer value
    for (int i = 0; i < 8; i++) {
        if (value % 2 == 0) {
            binary = "0" + binary;  // prepend 0 if remainder is 0
        }
        else {
            binary = "1" + binary;  // prepend 1 if remainder is 1
        }
        value = value / 2;          // shift right by 1 bit (divide by 2)
    }
    return binary;
}

// Converts full message into continuous binary string
// Concept: string traversal + ASCII conversion
// Source: https://www.geeksforgeeks.org/cpp-program-to-iterate-over-characters-of-a-string/
string QRCode::messageToBinary(string msg) {
    string binaryMessage = "";
    for (int i = 0; i < (int)msg.size(); i++) {
        binaryMessage += charToBinary(msg.at(i)); // convert each char and append
    }
    return binaryMessage;
}

// Main encode pipeline:
// 1. store original message
// 2. convert to binary
// 3. build visual grid
// 4. add team signature on top
string QRCode::encode(string msg) {
    message = msg;                      // store original message
    string binary = messageToBinary(msg); // convert to binary
    buildGrid(binary);                  // build visual grid from binary
    addSignature();                     // add team signature to grid
    return binary;                      // return binary for potential debugging
}

// Main decode pipeline:
// 1. remove signature before reading
// 2. convert grid back to binary
// 3. manually grab 8 bits at a time (no substr -- not covered in class)
// 4. convert each 8-bit chunk back to a character
string QRCode::decode() {
    removeSignature();          // remove signature before decoding
    string binary = gridToBinary(); // read grid back to binary
    string decodedMessage = "";

    for (int i = 0; i < (int)binary.size(); i += 8) {
        string bits = "";
        for (int j = i; j < i + 8; j++) {  // grab 8 bits manually
            bits += binary.at(j);
        }
        decodedMessage += binaryToChar(bits); // convert to char and append
    }

    return decodedMessage;
}

// Converts 8-bit binary string back to a character
// Concept: binary to decimal conversion using positional values
// Source: https://www.geeksforgeeks.org/program-binary-decimal-conversion/
string QRCode::binaryToChar(string bits) {
    int value = 0;
    for (int i = 0; i < BITS; i++) {
        value = value * 2 + (bits.at(i) - '0'); // build decimal value bit by bit
    }
    return string(1, (char)value); // convert integer back to character
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