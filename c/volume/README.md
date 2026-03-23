# WAV Volume Modifier

A C program that adjusts the volume of a WAV audio file by scaling each audio sample by a user-specified factor.

## 📜 Description

This program reads a WAV file, preserves the 44-byte header, multiplies each audio sample by a scaling factor, and saves the result to a new file. This allows you to increase or decrease the volume of any 16-bit PCM WAV file.

## 🚀 How to Compile and Run

### Compilation
```bash
gcc -o volume volume.c
```
### Usage
```bash
./volume input.wav output.wav factor
```

### Examples
```bash
# Double the volume
./volume music.wav louder.wav 2.0

# Half the volume
./volume music.wav quieter.wav 0.5

# Mute the audio
./volume music.wav silent.wav 0.0
```

## 🔊 How It Works
1. Reads WAV header (44 bytes) and copies it unchanged

2. Reads audio samples as 16-bit integers (int16_t)

3. Multiplies each sample by the scaling factor

4. Writes modified samples to the output file

## ⚠️ Important Notes
* Factor > 1.0 = Louder (risk of clipping/distortion)

* Factor < 1.0 = Quieter

* Factor = 1.0 = No change

* Works with standard 16-bit PCM WAV files only

## 📁 Project Structure
```text
pet-projects/c/volume/
├── volume.c    # Source code
├── input.wav   # Example audio
├── Makefile    # Build automation
└── README.md   # This file
```

## 🧪 Makefile (Optional)
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = volume
SRC = volume.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild
```
## 📄 License
This project is based on CS50's problem set and is created for educational purposes.
