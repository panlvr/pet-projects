# s21_grep

A C implementation of the Unix grep utility developed as part of the School 21 curriculum.

The project implements the behavior of the GNU grep command for the supported options while providing practical experience with regular expressions, command-line argument parsing, and text processing in C.

## Features

Implemented support for the following options:

|**Option**|**Description**|
|---|---|
|-e| Specify a search pattern.|
|-i|	Ignore case distinctions.|
|-v|	Select non-matching lines.|
|-c|	Print only the number of matching lines.|
|-l|	Print only the names of files containing matches.|
|-n|	Prefix matching lines with their line numbers.|

## Technologies

* C (C11)
* GCC
* POSIX API
* POSIX Regular Expressions (regex.h)
* Make
* Git

## Project Structure

```plain text
.
├── Makefile
├── README.md
├── s21_grep.c
├── s21_grep.h
└── tests/
    ├── test_grep.sh
    └── test_files/
        ├── sample.txt
        ├── mixed.txt
        ├── poem.txt
        └── server.log
```

## Building

Compile the project:

```bash
make
```

Remove build files:

```bash
make clean
```
Rebuild the project:

```bash
make rebuild
```

## Testing

The repository includes an automated test script that compares the output of s21_grep with the system GNU grep utility.

Run the tests with:

```bash
cd tests
./test_grep.sh
```

The script verifies supported flags, flag combinations, regular expressions, multiple-file searches, and invalid arguments by comparing the output with the GNU implementation.

Test files:

* **sample.txt** – general text for basic functionality.
* **mixed.txt** – mixed formatting, blank lines, tabs, numbers, and different letter cases.
* **poem.txt** – natural-language text for realistic pattern matching.
* **server.log** – simulated server log used to test searches in structured log files.

## Usage

```bash
./s21_grep [OPTIONS] PATTERN file...
```

Example:

```bash
./s21_grep -in "error" test_files/server.log
```

## Learning Outcomes

During this project I gained practical experience with:

* command-line argument parsing;
* file handling in C;
* POSIX regular expressions;
* text searching and pattern matching;
* modular software design;
* debugging and testing console applications;
* creating automated Bash test scripts;
* validating program behavior against the GNU implementation.

## License

This project was completed for educational purposes as part of the School 21 curriculum.
