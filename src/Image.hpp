#pragma once

#include <cstdint>
#include <vector>

// For ensuring that complier doesn't add padding to struct
#pragma pack(push, 1)

struct Pixel {
    uint8_t blue, green, red;
};

struct Header {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct DIB {
    uint32_t dibSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t depth;
    uint32_t compress_algo;
    uint32_t pixelArrSize;
    uint32_t horizontalResolution;
    uint32_t verticalResolution;
    uint32_t numOfColor;
    uint32_t numOfImportantColor;
};

struct Image {
    Header header;
    DIB dib;
    Pixel* pixelArr;
   
    Image() {}
    
    // Copy constructor
    Image(const Image&);

    // Avoid memory leak
    ~Image();

    // Assignment operator
    Image& operator = (const Image&);
};

Image::Image(const Image& img) {
    header = img.header;
    dib = img.dib;

    int w = dib.width, h = dib.height;
    int size = w * h;

    pixelArr = new Pixel[w * h];
    for (int i = 0; i < size; ++i) 
        pixelArr[i] = img.pixelArr[i];
}

Image::~Image() {
    if (pixelArr) 
        delete[] pixelArr;
}
 
Image& Image::operator = (const Image& img) {
    header = img.header;
    dib = img.dib;

    int w = dib.width, h = dib.height;
    
    // Create Pixel array
    Pixel* buff = new Pixel[w * h];
    int size = w * h;
    for (int i = 0; i < size; ++i) {
        buff[i] = img.pixelArr[i];
    }

    // Delete old pixel array
    delete[] this -> pixelArr;

    // Assign to buffer
    this -> pixelArr = buff;

    return *this;
}


#pragma pack(pop)
