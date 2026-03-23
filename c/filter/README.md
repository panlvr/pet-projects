# BMP Image Filter

A C program that applies various filters to 24-bit uncompressed BMP images. The program supports four different filters: grayscale, sepia, blur, and reflection (reverse).

## 📜 Description

This program reads a 24-bit uncompressed BMP image file, applies a user-specified filter, and saves the filtered image to a new file. It demonstrates image processing concepts, file I/O operations, and memory management in C.

## 🎨 Available Filters

| Filter | Flag | Description |
|--------|------|-------------|
| **Grayscale** | `g` | Converts the image to black and white by averaging RGB values |
| **Sepia** | `s` | Applies a warm brown tone, giving an antique photograph effect |
| **Blur** | `b` | Smooths the image by averaging pixel values with neighbors |
| **Reflection (Reverse)** | `r` | Horizontally flips the image (mirror effect) |

## 🚀 How to Compile and Run

### Prerequisites
- GCC compiler
- BMP image files (24-bit uncompressed format)
- Helper files: `helpers.h`, `helpers.c`, `bmp.h`

### Project Structure
```text
pet-projects/c/filter/
├── filter.c # Main program
├── helpers.c # Filter implementation functions
├── helpers.h # Filter function prototypes
├── bmp.h # BMP structure definitions
├── Makefile # Build automation
├── image.bmp # An example input image
└── README.md # This file
```

### Compilation

```bash
# Compile all files
gcc -o filter filter.c helpers.c -lm

# Or with warnings and optimizations
gcc -Wall -Wextra -O2 -o filter filter.c helpers.c -lm

# Using Makefile
make
```

### Running the Program
```bash
# Basic usage
./filter [flag] infile.bmp outfile.bmp

# Examples
./filter g image.bmp grayscale_output.bmp   # Grayscale
./filter s image.bmp sepia_output.bmp       # Sepia
./filter b image.bmp blur_output.bmp        # Blur
./filter r image.bmp reversed_output.bmp    # Reflection
```

## 🔍 Input Validation
The program validates the input BMP file with these requirements:

|Requirement|Value|Description|
|--|--|--|
|File Type|0x4d42 ("BM")|Must be a BMP file|
|Header Size|54 bytes|Standard BMP header (no extra data)|
|Info Header Size|40 bytes|BITMAPINFOHEADER structure|
|Bits Per Pixel	24|24-bit|true color (no palette)|
|Compression|0 (BI_RGB)|Uncompressed format|

### Error Messages
|Error|Message|Exit Code|
|---|---|---|
|Invalid filter|Invalid filter.|1|
|Multiple filters|Only one filter allowed.|2|
|Wrong arguments|Usage: ./filter [flag] infile outfile|3|
|Cannot open input|Could not open %s.|4|
|Cannot create output|Could not create %s.|5|
|Unsupported format|Unsupported file format.|6|
|Memory allocation|Not enough memory to store image.|7|

## 🛠️ BMP File Structure
BITMAPFILEHEADER (14 bytes)
```c
typedef struct {
    unsigned short bfType;      // "BM" (0x4d42)
    unsigned int bfSize;        // File size in bytes
    unsigned short bfReserved1; // Reserved (0)
    unsigned short bfReserved2; // Reserved (0)
    unsigned int bfOffBits;     // Offset to pixel data (54)
} BITMAPFILEHEADER;
```
BITMAPINFOHEADER (40 bytes)
```c
typedef struct {
    unsigned int biSize;        // Header size (40)
    int biWidth;                // Image width in pixels
    int biHeight;               // Image height in pixels
    unsigned short biPlanes;    // Color planes (1)
    unsigned short biBitCount;  // Bits per pixel (24)
    unsigned int biCompression; // Compression (0 = none)
    unsigned int biSizeImage;   // Image size (can be 0)
    int biXPelsPerMeter;        // Horizontal resolution
    int biYPelsPerMeter;        // Vertical resolution
    unsigned int biClrUsed;     // Colors used (0)
    unsigned int biClrImportant;// Important colors (0)
} BITMAPINFOHEADER;
```
RGBTRIPLE Structure
```c
typedef struct {
    unsigned char rgbtBlue;   // Blue value (0-255)
    unsigned char rgbtGreen;  // Green value (0-255)
    unsigned char rgbtRed;    // Red value (0-255)
} RGBTRIPLE;
```

## 🎨 Filter Implementation Details
### 1. Grayscale Filter
```c
// Average the RGB values
int average = (red + green + blue) / 3;
// Set all channels to the average
red = green = blue = average;
```

### 2. Sepia Filter
```c
// Apply sepia transformation formulas
int sepiaRed = 0.393 * red + 0.769 * green + 0.189 * blue;
int sepiaGreen = 0.349 * red + 0.686 * green + 0.168 * blue;
int sepiaBlue = 0.272 * red + 0.534 * green + 0.131 * blue;
// Cap values at 255
```
### 3. Blur Filter
```c
// Average pixel values with surrounding 3x3 grid
// For each pixel, sum values from neighboring pixels
// Divide by number of valid neighbors (9 for interior, less for edges)
```
### 4. Reflection Filter
```c
// Swap pixels horizontally
// For each row, swap pixel[i] with pixel[width - 1 - i]
```

## 🔧 BMP File Requirements
To use this program, your BMP files must be:

* Uncompressed (no RLE compression)

* 24-bit color depth (true color)

* No color palette (standard 24-bit format)

* Standard headers (BITMAPFILEHEADER + BITMAPINFOHEADER)

### Converting Images to Correct Format
If your image isn't in the correct format, use these tools:

#### Using ImageMagick
```bash
# Convert to 24-bit uncompressed BMP
convert input.jpg -compress none BMP3:output.bmp
```
#### Using GIMP
1. Open image in GIMP

2. File → Export As

3. Choose BMP format

4. Select "24 bits" and uncheck "RLE compression"

#### Using Windows Paint
1. Open image in Paint

2. File → Save As → BMP Picture

3. Automatically saves as 24-bit uncompressed BMP

## ⚠️ Common Issues and Solutions
|Issue|Solution|
|---|---|
|"Unsupported file format"|Convert image to 24-bit uncompressed BMP|
|Memory allocation error|Image is too large; try a smaller image|
|Blur filter too slow|Blur is O(n × w × h); use smaller images for testing|
|Colors look wrong|Check RGB order (BMP stores as BGR, not RGB)|

## 📄 License
This project is for educational purposes, demonstrating image processing concepts in C.