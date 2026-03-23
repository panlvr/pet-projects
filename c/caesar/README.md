# Caesar Cipher

A C program that implements the classic Caesar cipher encryption algorithm, shifting each letter in the plaintext by a specified number of positions in the alphabet.

## 📜 Description

This program implements the Caesar cipher, one of the simplest and most well-known encryption techniques. Named after Julius Caesar, who used it to communicate with his generals, this cipher works by shifting each letter in the plaintext by a fixed number of positions down the alphabet.

## 🔐 How the Caesar Cipher Works

The Caesar cipher replaces each letter with a letter a fixed number of positions away in the alphabet:

- **Encryption**: Each letter is shifted forward by the key value
- **Preserves case**: Uppercase letters remain uppercase, lowercase remain lowercase
- **Wraps around**: After 'Z' or 'z', the alphabet wraps to 'A' or 'a'
- **Non-letters**: Spaces, numbers, and punctuation remain unchanged

### Example with Key = 3
```text
Plaintext: HELLO WORLD
Ciphertext: KHOOR ZRUOG
```

## 🚀 How to Compile and Run

### Prerequisites
- GCC compiler
- CS50 library (for `get_string` function)

### Compilation

```bash
# Compile with CS50 library
gcc -o caesar caesar.c -lcs50

# Or with additional warnings
gcc -Wall -Wextra -o caesar caesar.c -lcs50
```
### Running the Program
```bash
# Basic usage with a numeric key
./caesar KEY

# Example with key 13 (ROT13)
./caesar 13
```

## 📋 Usage Examples

#### Example 1: Basic Encryption
```bash
$ ./caesar 3
plaintext:  HELLO WORLD
ciphertext: KHOOR ZRUOG
```
#### Example 2: ROT13 (Key 13)
```bash
$ ./caesar 13
plaintext:  The quick brown fox jumps over the lazy dog
ciphertext: Gur dhvpx oebja sbk whzcf bire gur ynml qbt
```
#### Example 3: Uppercase Preservation
```bash
$ ./caesar 5
plaintext:  Hello World! 123
ciphertext: Mjqqt Btwqi! 123
```
#### Example 4: Wrapping Around
```bash
$ ./caesar 1
plaintext:  ZEBRA
ciphertext: AFCSB
```
#### Example 5: Large Key Values
```bash
$ ./caesar 27  # Same as key 1 (27 mod 26 = 1)
plaintext:  ABC
ciphertext: BCD
```

## 🔍 Input Validation
The program validates input with these rules:

|Validation|Error Message|
|---|---|
|Missing command-line argument|Ooops, missing a value. Please indicate a key.|
|Key contains non-digit characters|Usage: ./caesar key|
|Memory allocation failure|Memory allocation failed!|

### Valid Input Examples:
```bash
./caesar 3
./caesar 13
./caesar 25
./caesar 0  # No shift (returns original text)
```
### Invalid Input Examples:
```bash
$ ./caesar
Ooops, missing a value. Please indicate a key.

$ ./caesar abc
Usage: ./caesar key

$ ./caesar 3a
Usage: ./caesar key
```

## 🛠️ Technical Details

### Encryption Algorithm
```c
// For uppercase letters (A-Z, ASCII 65-90)
ciphertext[i] = ((plaintext[i] - 65 + key) % 26) + 'A';

// For lowercase letters (a-z, ASCII 97-122)
ciphertext[i] = ((plaintext[i] - 97 + key) % 26) + 'a';
```
### How the Math Works
1. Convert letter to number: `plaintext[i] - 'A'` gives 0-25 for A-Z

2. Add the key: `+ key` shifts the number

3. Wrap around: `% 26` ensures result stays in 0-25 range

4. Convert back to letter: `+ 'A'` converts number back to ASCII character

### Example with 'Z' and key = 1
```text
'Z' = 90
90 - 65 = 25
25 + 1 = 26
26 % 26 = 0
0 + 65 = 65 = 'A'  ✓
```
## 📁 Project Structure
```text
pet-prjects/c/caesar/
├── caesar.c          # Main program source code
└── README.md         # This file
```
## 🧪 Makefile
Create a Makefile for easier compilation:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lcs50
TARGET = caesar
SRC = caesar.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(KEY)

clean:
	rm -f $(TARGET)

rebuild: clean all

debug: CFLAGS += -g
debug: clean all

.PHONY: all run clean rebuild debug
```

## 🧩 Function Descriptions
|Function|Purpose|
|---|---|
|rotate()|Encrypts plaintext by shifting each letter by the key value|
|main()|Validates input, gets plaintext, and displays ciphertext|

## 🔧 Without CS50 Library
If you don't have the CS50 library installed, replace get_string() and string with:

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef char* string;

char* get_string(const char* prompt)
{
    static char buffer[100];
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }
    buffer[strcspn(buffer, "\n")] = 0;
    return buffer;
}

// Rest of your code remains the same...
```

## ⚠️ Security Notes
* Not secure for real encryption: The Caesar cipher is easily broken with brute force (only 25 possible keys) or frequency analysis

* Educational purposes only: This implementation is meant for learning C programming and cryptography concepts

* For real security: Use modern encryption algorithms like AES

## 🔍 Debugging Tips
If the program isn't working as expected:

* Check key validation: Ensure key contains only digits

* Verify memory allocation: Check that malloc() succeeds

* Test with small inputs: Start with single letters

* Verify wrap-around: Test 'Z' with key 1 should become 'A'

* Check case preservation: Ensure case is maintained in output

## 🚀 Extensions
### Decryption Feature
```c
// Decryption is just encryption with negative key
string decrypt(int key, string ciphertext) {
    return rotate(26 - (key % 26), ciphertext);
}
```

### Support for Custom Alphabets
```c
// Add support for custom character sets
const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
```

## 📄 License
This project is based on CS50's problem set and is created for educational purposes.