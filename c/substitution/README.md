# Substitution Cipher

A C program that implements a substitution cipher, encrypting plaintext by replacing each letter with a corresponding letter from a provided 26-character key.

## 📜 Description

This program implements a substitution cipher where each letter in the plaintext is replaced by a letter from a substitution alphabet (key). The key must be exactly 26 unique alphabetical characters, representing a mapping from A-Z to the provided cipher alphabet.

## 🔐 How Substitution Cipher Works

1. **User provides a 26-character key** (e.g., `ZYXWVUTSRQPONMLKJIHGFEDCBA`)
2. **Program validates the key** (26 letters, all unique)
3. **User enters plaintext** to encrypt
4. **Program replaces each letter** with the corresponding key letter:
   - 'A' → first character of key
   - 'B' → second character of key
   - 'C' → third character of key
   - ...
   - 'Z' → 26th character of key
5. **Preserves case** - uppercase input maps to uppercase output, lowercase to lowercase
6. **Non-alphabetic characters** (spaces, punctuation, numbers) remain unchanged

## 🚀 How to Compile and Run

### Prerequisites
- GCC compiler
- CS50 library (for `get_string` function)

### Compilation

```bash
# Compile with CS50 library
gcc -o substitution substitution.c -lcs50

# Or with additional warnings
gcc -Wall -Wextra -o substitution substitution.c -lcs50
```

### Running the Program
```bash
# Basic usage
./substitution KEY

# Example with a key
./substitution ZYXWVUTSRQPONMLKJIHGFEDCBA
```

### 📋 Usage Examples
#### Example 1: Reverse Alphabet Key
```bash
$ ./substitution ZYXWVUTSRQPONMLKJIHGFEDCBA
plaintext:  Hello, World!
ciphertext: Svool, Dliow!
```
#### Example 2: Custom Key
```bash
$ ./substitution QWERTYUIOPASDFGHJKLZXCVBNM
plaintext:  The quick brown fox jumps over the lazy dog
ciphertext: Git wjcqk fzbpm fql nwqkr sbpg git vyzmg jfw
```
#### Example 3: Uppercase Preservation
```bash
$ ./substitution ABCDEFGHIJKLMNOPQRSTUVWXYZ
plaintext:  Hello World
ciphertext: Hello World
```

### 🔍 Key Validation Rules
#### The program validates the key with these rules:
|Rule|Error Message|
|----|----|
|Key must be exactly 26 characters|The key must be 26 letters|
|Key must contain only letters|The key must be alphabetical|
|All characters must be unique|All the characters must be unique|
#### Valid Keys Examples:
* `ABCDEFGHIJKLMNOPQRSTUVWXYZ` (identity)

* `ZYXWVUTSRQPONMLKJIHGFEDCBA` (reverse)

* `QWERTYUIOPASDFGHJKLZXCVBNM` (random)

* `TheQuickBrownFoxJumpsOverLazy` (case-insensitive, still valid)

#### Invalid Keys Examples:
```bash
$ ./substitution ABC
The key must be 26 letters

$ ./substitution ABC123DEF456GHI789JKL0MNO
The key must be alphabetical

$ ./substitution AABBCCDDEEFFGGHHIIJJKKLLMM
All the characters must be unique
```
### 🎮 Program Flow
1. Command Line Validation

* Check that exactly one argument is provided

* Display usage message if incorrect

2. Key Validation

* Verify key length = 26

* Verify all characters are alphabetical

* Verify all characters are unique (case-insensitive)

3. Input Collection

* Prompt user for plaintext using get_string()

4. Encryption

* Process each character:

* If lowercase: map to lowercase key character

* If uppercase: map to uppercase key character

* If non-alphabetic: preserve original character

5. Output

* Display the ciphertext result

### 🛠️ Technical Details
#### Key Mapping Algorithm
```c
// For lowercase letters (a-z)
int index = plaintext[i] - 'a';
ciphertext[i] = tolower(key[index]);

// For uppercase letters (A-Z)
int index = plaintext[i] - 'A';
ciphertext[i] = toupper(key[index]);
```
#### Character Mapping
|Input|Index|Output (with key `ZYXWVUTSRQPONMLKJIHGFEDCBA`)|
|---|---|---|
|'a'|0|'z' (key[0] = 'Z' → tolower = 'z')|
|'b'|1|'y' (key[1] = 'Y' → tolower = 'y')
|'A'|0|'Z' (key[0] = 'Z' → toupper = 'Z')
|'B'|1|'Y' (key[1] = 'Y' → toupper = 'Y')

### 📁 Project Structure
```text
pet-projects/c/substitution/
├── substitution.c    # Main program source code
├── Makefile          # Build automation
└── README.md         # This file
```

### 🧪 Makefile
#### Create a Makefile for easier compilation:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lcs50
TARGET = substitution
SRC = substitution.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(KEY)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild
```

### 🧩 Function Descriptions
|Function|Purpose|
|---|---|
|`validation()`|Validates the encryption key (length, alphabetical, uniqueness)|
|`cipher()`|Encrypts plaintext using the provided key|
|`main()`|Orchestrates the program flow|

### ⚠️ Error Handling
The program handles the following errors:

* Missing command-line argument

* Incorrect key length

* Non-alphabetic characters in key

* Duplicate characters in key

* Memory allocation for ciphertext

### 💡 Security Notes
* This is a simple substitution cipher and is not cryptographically secure

* Can be broken with frequency analysis

* Intended for educational purposes only

* Always use proper encryption algorithms (AES, etc.) for real security needs

### 🔧 Without CS50 Library
If you don't have the CS50 library installed, replace get_string() with:

```c
char* get_string(const char* prompt)
{
    static char buffer[100];
    printf("%s", prompt);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    return buffer;
}
```
And change `string` to `char*` throughout the code.

### 📊 Example Run
```text
$ ./substitution ZYXWVUTSRQPONMLKJIHGFEDCBA
plaintext:  Hello, World!
ciphertext: Svool, Dliow!

$ ./substitution QWERTYUIOPASDFGHJKLZXCVBNM
plaintext:  This is a secret message
ciphertext: Gjsj sj t hkckjg wjkktic
```

### 🎓 Learning Objectives
This project demonstrates:

* Command-line argument processing

* String manipulation in C

* Character encoding and ASCII values

* Memory management with malloc()

* Input validation techniques

* Case preservation in text processing

### 📄 License
This project is based on CS50's problem set and is created for educational purposes.

Encrypt your messages with a custom substitution cipher! 🔐