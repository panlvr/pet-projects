# Largest Prime Factor Finder

A C program that finds the largest prime factor of a given integer. The program handles positive and negative integers, validates input, and implements mathematical operations without using the modulo or division operators.

## 📜 Description

This program finds the largest prime factor of an integer. It uses custom implementations of modulo and division operations (without using the built-in `%` and `/` operators) to demonstrate algorithmic thinking and manual arithmetic operations.

## 🔢 How It Works

The program follows these steps:

1. **Input Validation** - Checks if input is a valid integer
2. **Input Sanitization** - Handles special cases (-1, 0, 1) and converts negative numbers to positive
3. **Factor Out 2's** - Removes all factors of 2 from the number
4. **Find Largest Prime Factor** - Checks odd divisors from 3 upwards to find the largest prime factor

## 🚀 How to Compile and Run

### Compilation

```bash
# Basic compilation
gcc -o prime_factor prime_factor.c

# With warnings
gcc -Wall -Wextra -o prime_factor prime_factor.c

# With optimization
gcc -O2 -o prime_factor prime_factor.c
```
### Running the Program
```bash
# Basic usage
./prime_factor

# Enter a number when prompted
```
## 📋 Usage Examples
### Example 1: Positive Number
```bash
$ ./prime_factor
12
3
```
Explanation: Prime factors of 12 are 2 and 3. Largest is 3.

### Example 2: Prime Number
```bash
$ ./prime_factor
17
17
```
Explanation: 17 is prime, so its largest prime factor is itself.

### Example 3: Negative Number
```bash
$ ./prime_factor
-28
7
```
Explanation: Program converts -28 to 28, factors are 2, 2, 7. Largest is 7.

### Example 4: Power of 2
```bash
$ ./prime_factor
16
2
```
Explanation: 16 = 2⁴, largest prime factor is 2.

### Example 5: Large Prime Factor
```bash
$ ./prime_factor
13195
29
```
Explanation: 13195 = 5 × 7 × 13 × 29, largest is 29.

## 🔍 Input Validation
The program validates input with these rules:

|Input Type|Behavior|
|---|---|
|Valid integer|Process the number|
|Non-numeric input|Output "n/a"|
|Extra characters after number|Output "n/a"|
|-1, 0, 1|Output "n/a" (no prime factors)|
|Negative numbers|Convert to positive for processing|

### Valid Input Examples:
* `12` → Processes normally

* `-28` → Converts to 28

* `13195` → Returns 29

### Invalid Input Examples:
```bash
$ ./prime_factor
abc
n/a

$ ./prime_factor
12abc
n/a

$ ./prime_factor
0
n/a

$ ./prime_factor
1
n/a
```

## 🛠️ Function Descriptions
|Function|Purpose|Implementation Details|
|`check()`|Validates and normalizes input|Handles -1, 0, 1; converts negatives to positive|
|`modulo()`|Custom modulo operation|Repeated subtraction without using %|
|`division()`|Custom division operation|Counts how many times divisor fits|
|`even()`|Removes all factors of 2|Uses bitwise operations for efficiency|
|`odd()`|Finds largest odd prime factor|Checks odd divisors up to √n|

## 🔧 Algorithm Details
### Removing Factors of 2
```c
// Using bitwise operations for efficiency
while ((n & 1) == 0) {
    n >>= 1;  // Equivalent to n = n / 2
}
```
### Finding Largest Prime Factor
```c
// Check odd divisors from 3 upwards
while (div * div <= n) {
    while (modulo(n, div) == 0) {
        n = division(n, div);  // Divide n by div
        largest = div;          // Update largest factor
    }
    div += 2;  // Check next odd number
}
```
### Custom Arithmetic Operations
#### Modulo without `%`:

```c
int modulo(int n, int div) {
    while (n - div >= 0) {
        n -= div;
    }
    return n;
}
```
Division without `/`:

```c
int division(int n, int div) {
    int cnt = 0;
    while (n - div >= 0) {
        n -= div;
        cnt++;
    }
    return cnt;
}
```

## 📁 Project Structure
```text
prime_factor/
├── prime_factor.c    # Main program source code
├── Makefile          # Build automation
└── README.md         # This file
```
### 🧪 Makefile
Create a Makefile for easier compilation:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = prime_factor
SRC = prime_factor.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

debug: CFLAGS += -g
debug: clean all

.PHONY: all run clean rebuild debug
```
## 🧮 Test Cases
|Input|Expected Output|Explanation|
|---|---|---|
|2|2|Prime number|
|3|3|Prime number|
|15|5|15 = 3 × 5|
|21|7|21 = 3 × 7|
|13195|29|13195 = 5 × 7 × 13 × 29|

## ⚠️ Error Handling
The program handles the following errors:

* Non-numeric input

* Extra characters after number

* Numbers without prime factors `(-1, 0, 1)`

* All errors output `"n/a"`

## 💡 Learning Objectives
This project demonstrates:

* Custom implementation of arithmetic operations

* Prime factorization algorithms

* Input validation techniques

* Bitwise operations for optimization

* Loop-based arithmetic without built-in operators

* Handling edge cases and invalid input


## 🐛 Debugging Tips
If the program isn't working as expected:

* Check input format - Ensure no extra spaces or characters

* Test small numbers first - Start with 2, 3, 4, etc.

* Verify algorithm - For number 12, steps should be:

    * Remove 2's: 12 → 3

    * Check odd divisors: 3 is prime

    * Largest factor = 3

## 📄 License
This project is created for educational purposes to demonstrate algorithmic thinking and custom arithmetic operations.