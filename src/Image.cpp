#include "Image.hpp"

int Image::idx(int r, int c) const {
    return r * dib.width + c;
}

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
