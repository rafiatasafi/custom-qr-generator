// QR Code Generator - Final Project
// Authors: Rafia, Hamza, Zakai
// Course: CS103, Spring 2026
// Reference for QR encoding concept:
// https://dev.to/maxart2501/series/13444 (conceptual reference)
// https://github.com/nayuki/QR-Code-generator
// Used for understanding data-to-grid mapping (not copied)
// zyBooks Ch. 9.7 (file I/O)
// https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/ (vector insert/erase)
// AI Assistance: Claude (Anthropic) via claude.ai
// Used for: debugging, code structure guidance, and concept explanation
// Note: All code written and understood by team members



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// Constants
const int BITS = 8;      // number of bits per character
const string ZERO = " "; // visual representation of 0
const string ONE = "█";  // Unicode full block character for visual representation of 1
const int SIG_ROWS = 15; // number of signature rows (5 rows per letter x 3 letters)

// CLASS DEFINITION

class QRCode {
    private:
        vector<string> grid;  // stores the visual grid row by row
        string message;       // original message
        int originalChecksum; // stores checksum of original message for verification

    public:
        // Constructor
        QRCode() {
            grid.clear();
            message = "";
            originalChecksum = 0;
        }

        // Encoding + Decoding ---
        string charToBinary(char c);        // converts char to 8-bit binary
        string messageToBinary(string msg); // converts entire message to binary
        string encode(string msg);          // main encoding function
        string decode();                    // main decoding function
        string binaryToChar(string bits);   // converts 8-bit binary to char

        // Grid + Checksum ---
        void buildGrid(string binary);      // turns binary into visual grid
        string gridToBinary();              // reads grid back to binary
        void displayGrid();                 // prints grid to terminal
        int checksum(string text);          // sum of ASCII values
        void addSignature();                // adds RHZ signature to grid
        void removeSignature();             // strips signature before decode

        // File I/O + Utility ---
        void saveToFile(string filename);   // writes grid to txt
        void loadFromFile(string filename); // reads grid from txt
        void printSignatureExplanation();   // explains signature to user

        // getter for originalChecksum so main can access it
        int getOriginalChecksum() { return originalChecksum; }
};


// Our 10+ FUNCTIONS

// Note: For simplicity, we will assume the message only contains standard ASCII characters (0-127).
// Thought process for charToBinary:
// - We want to convert a character (like 'A') into its binary representation (like "01000001").
// - We can do this by repeatedly dividing the ASCII value by 2 and recording the remainders.
// - We need exactly 8 bits, padding with leading zeros if necessary.
// Source: https://www.geeksforgeeks.org/convert-character-binary-string-cpp/
string QRCode::charToBinary(char c) {
    string binary = "";
    int value = (int)c;         // convert char to its ASCII integer value
    for (int i = 0; i < 8; i++) {
        if (value % 2 == 0) {
            binary = "0" + binary;  // prepend 0 if remainder is 0
        } else {
            binary = "1" + binary;  // prepend 1 if remainder is 1
        }
        value = value / 2;          // shift right by 1 bit (divide by 2)
    }
    return binary;
}

// Converts full message into one continuous binary string
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
// 1. store original message and its checksum
// 2. convert to binary
// 3. build visual grid
// 4. add RHZ signature on top
string QRCode::encode(string msg) {
    message = msg;                          // store original message
    originalChecksum = checksum(msg);       // store checksum BEFORE encoding for later verification
    string binary = messageToBinary(msg);   // convert to binary
    buildGrid(binary);                      // build visual grid from binary
    addSignature();                         // add RHZ signature to grid
    return binary;                          // return binary for potential debugging
}

// Main decode pipeline:
// 1. remove RHZ signature before reading
// 2. convert grid back to binary
// 3. manually grab 8 bits at a time (no substr -- not covered in class)
// 4. convert each 8-bit chunk back to a character
string QRCode::decode() {
    removeSignature();              // remove RHZ signature before decoding
    string binary = gridToBinary(); // read grid back to binary
    string decodedMessage = "";

    for (int i = 0; i + (BITS - 1) < (int)binary.size(); i += BITS) {
    string bits = "";

    for (int j = i; j < i + BITS; j++) {
        bits += binary.at(j);
    }

    decodedMessage += binaryToChar(bits);
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

// FUNCTIONS related to grid construction and display

// Builds the visual grid from a binary string
// Each row holds exactly 8 bits (1 character worth of data)
void QRCode::buildGrid(string binary) {
    grid.clear();
    string row = "";

    for (int i = 0; i < (int)binary.size(); i++) {
        row += binary.at(i); // add current bit to row

        if ((int)row.size() == 8) { // once we have 8 bits, store as a row
            grid.push_back(row);
            row = ""; // reset for next row
        }
    }

    // if there are leftover bits, store them as the final row
    if (row != "") {
        grid.push_back(row);
    }
}

// Reads the grid back into a continuous binary string
string QRCode::gridToBinary() {
    string binary = "";

    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid.at(i).size(); j++) {
            binary += grid.at(i).at(j); // add each bit back
        }
    }

    return binary;
}

// Displays the grid visually using ONE (█) for 1 and ZERO (space) for 0
void QRCode::displayGrid() {
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid.at(i).size(); j++) {
            if (grid.at(i).at(j) == '1') {
                cout << ONE;  // █
            } else {
                cout << ZERO; // space
            }
        }
        cout << endl;
    }
}

// Checksum: sum of ASCII values of all characters
// Used to verify data integrity after decode
// If input checksum == decoded checksum, data was not corrupted
int QRCode::checksum(string text) {
    int sum = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        sum += (int)text.at(i); // add ASCII value of each character
    }
    return sum;
}

// RHZ pixel art designed manually by our team
// R = Rafia, H = Hamza, Z = Zakai
// Each letter is 5 rows of 8 bits = 15 signature rows total
// Inserted BEFORE message rows so it does not corrupt message data
// Source for vector insert: https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/
// RHZ pixel art designed manually by our team
// Each letter drawn on an 8-column grid where:
// 1 = filled block (█), 0 = empty space
// We sketched each letter on graph paper and 
// converted each row to its binary representation
// Similar concept to bitmap fonts:
// Source: https://en.wikipedia.org/wiki/Computer_font#Bitmap_fonts
void QRCode::addSignature() {
    vector<string> sig = {
        "11111100", "11001100", "11111100", "11011000", "11001100", // R (Rafia)
        "11001100", "11001100", "11111100", "11001100", "11001100", // H (Hamza)
        "11111100", "00011000", "00110000", "01100000", "11111100"  // Z (Zakai)
    };

    // insert in reverse so rows end up in correct order at top of grid
    for (int i = (int)sig.size() - 1; i >= 0; i--) {
        grid.insert(grid.begin(), sig.at(i));
    }
}

// Removes the 15 RHZ signature rows from the top of the grid before decoding
// Source for vector erase: https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/
void QRCode::removeSignature() {
    for (int i = 0; i < SIG_ROWS; i++) {
        if ((int)grid.size() > 0) {
            grid.erase(grid.begin()); // remove first row each time
        }
    }
}

// FUNCTIONS related to file I/O and user explanation

// Saves the grid to a text file line by line
// First line is the original checksum so we can verify after loading
// Source: zyBooks Ch. 9.7
void QRCode::saveToFile(string filename) {
    ofstream outFile(filename);
    outFile << originalChecksum << endl; // save checksum as first line for verification
    for (int i = 0; i < (int)grid.size(); i++) {
        outFile << grid.at(i) << endl;
    }
    outFile.close();
    cout << "Grid saved to " << filename << " successfully!" << endl;
}

// Loads a grid from a text file line by line
// First line is the original checksum, rest is the grid
// Source: zyBooks Ch. 9.7
void QRCode::loadFromFile(string filename) {
    ifstream inFile(filename);
    grid.clear();

    // read checksum from first line and convert string to int manually
    // Source for manual string to int: zyBooks string operations
    string csLine;
    getline(inFile, csLine);
    int cs = 0;
    for (int i = 0; i < (int)csLine.size(); i++) {
        cs = cs * 10 + (csLine.at(i) - '0'); // build integer digit by digit
    }
    originalChecksum = cs; // restore original checksum for verification

    // read rest of file as grid rows
    string filerow;
    while (getline(inFile, filerow)) {
        if (!filerow.empty()) {
            grid.push_back(filerow);
        }
    }
    inFile.close();
    cout << "Grid loaded from " << filename << " successfully!" << endl;
}

// Explains our unique RHZ signature to the user
void QRCode::printSignatureExplanation() {
    cout << "\n=== UNIQUE SIGNATURE INFO ===========================" << endl;
    cout << " Our team signature is the initials R, H, Z" << endl;
    cout << " drawn in pixel art using 1s and 0s." << endl;
    cout << " It appears as the first 15 rows of every encoded grid:" << endl;
    cout << "   5 rows for R (Rafia)" << endl;
    cout << "   5 rows for H (Hamza)" << endl;
    cout << "   5 rows for Z (Zakai)" << endl;
    cout << " Visually it looks like:" << endl;
    cout << " █████   ██  ██  █████ " << endl;
    cout << " ██  ██  ██  ██    ██  " << endl;
    cout << " █████   ██████   ██   " << endl;
    cout << " ██ ██   ██  ██  ██    " << endl;
    cout << " ██  ██  ██  ██  █████ " << endl;
    cout << " The decoder automatically removes these 15 rows" << endl;
    cout << " before reading the message data." << endl;
    cout << "=====================================================" << endl;
}


int main() {
    QRCode qr;

    while (true) {
        cout << "\n=== QR Code Generator ===" << endl;
        cout << "1. Encode a message" << endl;
        cout << "2. Decode from file" << endl;
        cout << "3. Exit" << endl;
        cout << "Pick an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cin.ignore(); // flush leftover newline from cin >> choice
            string msg;
            cout << "Enter your message: ";
            getline(cin, msg);

            qr.encode(msg);
            qr.displayGrid();

            // show original checksum for user to note
            cout << "\nOriginal Checksum: " << qr.getOriginalChecksum() << endl;

            qr.printSignatureExplanation();

            // ask if user wants to save to file
            string saveChoice;
            cout << "\nSave to file? (yes/no): ";
            cin >> saveChoice;
            if (saveChoice == "yes") {
                string filename;
                cout << "Enter filename (e.g. output.txt): ";
                cin >> filename;
                qr.saveToFile(filename);
                cout << "Share this file and the filename with your recipient!" << endl;
            }
        }
        else if (choice == 2) {
            // decode from file -- most reliable method
            // file stores checksum on first line so we can verify integrity
            string inputfile;
            cout << "Enter filename to load: ";
            cin >> inputfile;
            qr.loadFromFile(inputfile);

            string decoded = qr.decode();

            if (!decoded.empty()) {
                int decodedCS = qr.checksum(decoded);
                int originalCS = qr.getOriginalChecksum();

                cout << "\nDecoded message: " << decoded << endl;
                cout << "\nOriginal Checksum:  " << originalCS << endl;
                cout << "Decoded Checksum:   " << decodedCS << endl;

                // verify checksums match
                if (decodedCS == originalCS) {
                    cout << "Checksum MATCH -- data integrity verified!" << endl;
                } else {
                    cout << "Checksum MISMATCH -- data may be corrupted!" << endl;
                }
            }
            qr.printSignatureExplanation();
        }
        else if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
