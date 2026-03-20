# Runoff Voting System

A C implementation of a ranked-choice voting system (also known as instant-runoff voting) where voters rank candidates by preference. The program simulates a runoff election, eliminating the least popular candidates until a winner emerges with more than 50% of the votes.

## 📜 Description

This program implements an instant-runoff voting system where voters rank candidates in order of preference. If no candidate receives more than 50% of first-choice votes, the candidate with the fewest votes is eliminated, and votes for that candidate are redistributed to the next preference. This process continues until a candidate wins or a tie occurs.

## 🗳️ How Runoff Voting Works

1. Voters rank candidates from 1 to N (where N is the number of candidates)
2. If a candidate has more than 50% of the first-choice votes, they win
3. If not, the candidate with the fewest votes is eliminated
4. Votes for eliminated candidates are redistributed to the next preference
5. The process repeats until a winner is found or a tie is declared

## 🚀 How to Compile and Run

### Prerequisites
- GCC compiler
- CS50 library (for `get_string` and `get_int` functions)
- Terminal/command line

### Installation of CS50 Library

#### On Linux/Mac:
```bash
# Install CS50 library
git clone https://github.com/cs50/libcs50.git
cd libcs50
sudo make install
On Windows with WSL:
Follow the same Linux instructions, or use the CS50 IDE/Sandbox.
```
## Compilation
```bash
# Compile with CS50 library
gcc -o runoff runoff.c -lcs50

# Or with additional warnings
gcc -Wall -Wextra -o runoff runoff.c -lcs50
```
## Running the Program
```bash
# Basic usage with candidate names
./runoff Alice Bob Charlie

# With more candidates (up to 9)
./runoff Candidate1 Candidate2 Candidate3 Candidate4
```
### 📋 Usage Example
```text
$ ./runoff Alice Bob Charlie
Number of voters: 3
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

### 🎮 Program Flow
1. Input Validation

* Checks for at least one candidate

* Ensures candidate count doesn't exceed maximum (9)

* Validates voter count (max 100)

2. Voting

* Each voter ranks all candidates

* Invalid votes (non-existent candidates) cause immediate exit

3. Tabulation

* Counts votes for non-eliminated candidates

* Each vote counts for the highest-ranked non-eliminated candidate

4. Winner Check

* If any candidate has >50% of votes, they win

5. Elimination

* Find minimum vote count among remaining candidates

* If tie between all remaining, all win

* Otherwise, eliminate candidates with minimum votes

6. Repeat

* Reset vote counts

* Continue until winner found or tie declared

### 🔧 Technical Specifications
Parameter	Limit
Maximum Voters	100
Maximum Candidates	9
Vote Counting Method	Instant-runoff
Winner Threshold	>50% of votes

### 📁 Project Structure
```text
pet-projects/c/runoff/
├── runoff.c           # Main program source code
├── Makefile           # Build automation
└── README.md          # This file
```

### 🛠️ Makefile
Create a Makefile for easier compilation:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lcs50
TARGET = runoff
SRC = runoff.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

debug: CFLAGS += -g
debug: clean all

.PHONY: all run clean rebuild debug
```
Then compile with:

```bash
make          # Build the program
make run      # Build and run
make clean    # Remove binary
```
### 🧩 Function Descriptions
|Function|Purpose|
|----|----|
|vote()|Records voter preferences if the candidate exists|
|tabulate()|Counts votes for non-eliminated candidates|
|print_winner()|Checks if any candidate has >50% of votes|
|find_min()|Finds the lowest vote count among remaining candidates|
|is_tie()|Determines if all remaining candidates are tied|
|eliminate()|Eliminates candidates with the minimum votes|

### 📊 Sample Outputs
#### Regular Win
```text
$ ./runoff Alice Bob Charlie
Number of voters: 5
[Voting input...]
Alice
Tie Scenario
text
$ ./runoff Alice Bob
Number of voters: 2
Rank 1: Alice
Rank 2: Bob
Rank 1: Bob
Rank 2: Alice

Alice
Bob
```
#### Invalid Input Handling
```text
$ ./runoff
Usage: runoff [candidate ...]

$ ./runoff Alice Bob Charlie Dave Eve Frank George Henry Irene John
Maximum number of candidates is 9
```
### ⚠️ Error Handling
The program handles the following errors:

* No candidates provided

* Too many candidates (>9)

* Too many voters (>100)

* Invalid candidate names during voting

* Empty input

### 🎓 Learning Objectives
This project demonstrates:

* Ranked-choice voting algorithms

* Struct usage in C

* 2D arrays for storing preferences

* Modular function design

* Boolean logic and control flow

* String manipulation and comparison

### 📝 Notes
* All candidates must be ranked by each voter

* Voter count must be provided as an integer

* Candidate names are case-sensitive

* The program exits immediately on invalid votes

* In case of a complete tie, all remaining candidates are declared winners

### 🔍 Debugging Tips
If votes aren't counting correctly:

* Check that candidates are being properly eliminated

* Verify that tabulate() is finding each voter's next preference

* Ensure vote counts are reset after each elimination round

### 📄 License
This project is based on CS50's problem set and is created for educational purposes.
