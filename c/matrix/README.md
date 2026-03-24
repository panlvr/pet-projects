# Matrix Operations Program

A C program that demonstrates different memory allocation techniques for 2D matrices, allowing users to input and display matrices using four distinct approaches.

## 📜 Description

This program showcases four different ways to work with 2D matrices in C, highlighting various memory allocation strategies:
1. **Static allocation** (fixed-size array)
2. **Dynamic allocation** (pointer-to-pointer)
3. **Flat array** (1D array accessed as 2D)
4. **Block allocation** (single block with row pointers)

## 🎮 Menu Options

| Option | Allocation Method | Memory Pattern |
|--------|------------------|----------------|
| 1 | Static Array | `int data[100][100]` |
| 2 | Pointer-to-Pointer | `int **data` with individual row allocations |
| 3 | Flat Array | `int *data` with index calculation |
| 4 | Block Allocation | Single block + row pointer array |

## 🚀 How to Compile and Run

### Compilation

```bash
# Basic compilation
gcc -o matrix matrix.c

# With warnings
gcc -Wall -Wextra -o matrix matrix.c

# With debugging
gcc -g -o matrix matrix.c
```

### Running the Program
```bash
./matrix
```

## 📋 Usage Examples
### Example 1: Static Matrix (Option 1)
```bash
$ ./matrix
1
2 3
1 2 3
4 5 6
```
#### Output:
```text
1 2 3
4 5 6
```
### Example 2: Dynamic Matrix (Option 2)
```bash
$ ./matrix
2
2 3
1 2 3
4 5 6
```
#### Output:
```text
1 2 3
4 5 6
```
### Example 3: Flat Array (Option 3)
```bash
$ ./matrix
3
2 3
1 2 3 4 5 6
```
#### Output:
```text
1 2 3
4 5 6
```

### Example 4: Block Allocation (Option 4)
```bash
$ ./matrix
4
2 3
1 2 3
4 5 6
```

#### Output:
```text
1 2 3
4 5 6
```

## 🔍 Input Format
### First Input Line
```text
[choice] 
[rows] [cols]
```
`choice`: 1-4 (matrix type)

`rows`: Number of rows (> 0)

`cols`: Number of columns (> 0)

### Matrix Data
Enter the matrix elements row by row:

```text
a11 a12 a13 ... a1n
a21 a22 a23 ... a2n
...
```

## 🛠️ Memory Allocation Techniques
### 1. Static Allocation (Option 1)
```c
int data[100][100];
```
* Pros: Simple, fast allocation

* Cons: Fixed size (100×100 maximum)

* Use when: Matrix size known at compile time

### 2. Pointer-to-Pointer (Option 2)
```c
int **data = malloc(rows * sizeof(int *));
for (int i = 0; i < rows; i++) {
    data[i] = malloc(cols * sizeof(int));
}
```
* Pros: Flexible size, natural 2D indexing

* Cons: Multiple allocations, memory overhead

* Use when: Different row sizes needed

### 3. Flat Array (Option 3)
```c
int *data = malloc(rows * cols * sizeof(int));
// Access: data[i * cols + j]
```
* Pros: Single allocation, cache-friendly

* Cons: Manual index calculation

* Use when: Performance is critical

### 4. Block Allocation (Option 4)
```c
int *block = malloc(rows * cols * sizeof(int));
int **data = malloc(rows * sizeof(int *));
for (int i = 0; i < rows; i++) {
    data[i] = block + i * cols;
}
```
* Pros: Single data block, 2D indexing

* Cons: Two allocations

* Use when: Best of both worlds

## 📊 Memory Layout Comparison
|Method|Memory Layout|Access Pattern|
|---|---|---|
|Static|Contiguous|data[i][j]|
|Pointer-to-Pointer|Fragmented|data[i][j]|
|Flat|Array	Contiguous|data[i*cols+j]|
|Block|Contiguous|data[i][j]|

## ⚠️ Error Handling
The program validates:

* Input choice (1-4)

* Matrix dimensions (> 0)

* Matrix elements (valid integers)

#### Error Messages
`n/a`- Invalid input or memory allocation failure

## 📝 Input Validation Examples
### Valid Input
```bash
1
3 3
1 2 3
4 5 6
7 8 9
```
### Invalid Input Examples
```bash
# Invalid choice
5
n/a

# Invalid dimensions
2
-2 3
n/a

# Missing elements
1
2 2
1 2
n/a
```

## 📁 Project Structure
```text
matrix/
├── matrix.c      # Main program source
├── Makefile      # Build automation
└── README.md     # This file
```

## 🧪 Makefile
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = matrix
SRC = matrix.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

## 📄 License
This project is created for educational purposes as part of a programming course.
