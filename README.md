# Custom QR Code Generator (C++)

This project implements a simplified QR-like encoding and decoding system using C++. It converts text into binary, maps the binary into a visual grid, embeds a custom signature, and allows full reconstruction of the original message with checksum verification.

---

## Features

- Convert text to binary representation (ASCII-based)
- Encode binary into a 2D grid format
- Custom pixel-art signature (RHZ) embedded into the grid
- Decode grid back into original message
- Checksum validation to verify data integrity
- Save and load encoded grids from files

---

## How It Works

### Encoding Pipeline
1. Input message is converted into binary (8 bits per character)
2. Binary is grouped into rows and stored in a grid
3. A custom RHZ signature is inserted at the top of the grid
4. Grid can be displayed or saved to a file

### Decoding Pipeline
1. Signature rows are removed from the grid
2. Grid is converted back into a continuous binary string
3. Binary is read in 8-bit chunks
4. Each chunk is converted back to a character
5. Checksum is compared to verify correctness

---

## Custom Signature

We designed a unique signature using the initials **R, H, Z** (Rafia, Hamza, Zakai).  
Each letter was sketched on graph paper, converted into binary rows, and embedded into the grid.

This signature:
- Appears as the first 15 rows of every encoded grid (5 rows per letter)
- Is automatically removed before decoding
- Does not interfere with message data

Visually it renders in the terminal as:
```
█████   ██  ██  █████
██  ██  ██  ██    ██
█████   ██████   ██
██ ██   ██  ██  ██
██  ██  ██  ██  █████
```

---

## Compilation & Execution

To compile and run the program:
```bash
g++ main.cpp -o main -std=c++11 && ./main
```

---

## Menu Options

```
=== QR Code Generator ===
1. Encode a message
2. Decode from file
3. Exit
```

**Option 1 — Encode:**
- Type any message
- Program displays the visual grid with RHZ signature
- Shows checksum of original message
- Option to save encoded grid to a `.txt` file

**Option 2 — Decode:**
- Enter the filename of a saved encoded grid
- Program loads the grid, removes the signature, and reconstructs the message
- Compares original and decoded checksums to verify integrity

---

## Checksum Verification

The checksum is the sum of ASCII values of all characters in the message.  
It is saved as the first line of the output file during encoding, and compared after decoding.

```
Original Checksum:  1038
Decoded Checksum:   1038
Checksum MATCH -- data integrity verified! ✓
```

---

## File Format

When saved, the output `.txt` file looks like:
```
1038          ← checksum (first line)
11111100      ← start of RHZ signature
11001100
...           ← rest of grid rows
01101000      ← message data rows
```

---

## Team

| Name  | Role |
|-------|------|
| Rafia | Core algorithm — charToBinary, messageToBinary, encode, decode, binaryToChar |
| Hamza | Grid construction, display, checksum, RHZ signature |
| Zakai | File I/O, main menu, program structure |

---

## Sources & Citations

- [DEV Community — QR Code Generator Series](https://dev.to/maxart2501/series/13444) — conceptual reference
- [nayuki/QR-Code-generator](https://github.com/nayuki/QR-Code-generator) — conceptual reference for data-to-grid mapping 
- zyBooks Chapter 9.7 — file I/O
- [GeeksForGeeks — char to binary](https://www.geeksforgeeks.org/convert-character-binary-string-cpp/)
- [GeeksForGeeks — binary to decimal](https://www.geeksforgeeks.org/program-binary-decimal-conversion/)
- [GeeksForGeeks — vector insert/erase](https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/)
- [Wikipedia — Bitmap Fonts](https://en.wikipedia.org/wiki/Computer_font#Bitmap_fonts) — concept behind RHZ pixel art signature
- AI Assistance: Claude (Anthropic) via claude.ai — debugging and concept explanation

---

## Course

CS103 — Introduction to Computer Science  
The City College of New York (CUNY), Spring 2026
