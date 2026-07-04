# s21_cat

A C implementation of the Unix cat utility developed as part of the School 21 curriculum.

The project implements the behavior of the GNU cat command for the supported options while providing hands-on experience with command-line argument parsing, file processing, and low-level input/output operations in C.

## Features

Implemented support for the following GNU cat options:

|**Option**|**Description**|
|---|---|
|-b, --number-nonblank|	Number non-empty output lines.|
|-e (implies -v), -E (without -v)| Display $ at line ends (displays ^M$ on Windows \r\n lines)|
|-n, --number| Number all output lines.|
|-s, --squeeze-blank| Suppress repeated empty output lines.|
|-t (implies -v), -T (without -v)| Display tab characters as ^I.|
|-v| Display non-printable characters using caret notation.|

## Technologies

* C (C11)
* GCC
* POSIX API
* Make
* Git

Project Structure

```plain text
.
├── Makefile
├── README.md
├── s21_cat.c
├── s21_cat.h
└── tests/
    ├── test_cat.sh
    └── test_files/
        ├── sample.txt
        └── mixed.txt
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

The repository includes an automated test script that compares the output of s21_cat with the system GNU cat utility.

Run the tests with:

```bash
cd tests
./test_cat.sh
```

The script verifies the supported flags, GNU long options, flag combinations, multiple-file input, and invalid arguments by comparing the output of both implementations.

Test files:

* **sample.txt** – general text for basic functionality.
* **mixed.txt** – blank lines, tabs, mixed letter case, numbers, and special characters for edge-case testing.

## Usage

```bash
./s21_cat [OPTIONS] file...
```

Example:

```bash
./s21_cat -ben example.txt
```

## Learning Outcomes

During this project I gained practical experience with:

* command-line argument parsing;
* file handling and stream processing;
* implementing Unix command-line utilities;
* handling text formatting and non-printable characters;
* writing modular and maintainable C code;
* creating automated Bash test scripts;
* comparing program behavior against the GNU implementation.

## License

This project was completed for educational purposes as part of the School 21 curriculum.