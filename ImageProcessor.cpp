#include "ImageProcessor.hpp"
#include <stdexcept>
#include <iostream>

void ImageProcessor::readImage(Image& img, const std::string& path) {
    // Open file
    std::ifstream inp(path, std::ios::binary);
    // Invalid path
    if (!inp) throw std::invalid_argument("Invalid path\n");

    // Read header
    inp.read(reinterpret_cast<char*>(&img.header), sizeof(img.header));
    std::cout << "header\n";
    
    if (img.header.signature != 0x4D42) // check 24bitmap format
        throw std::invalid_argument("Invalid file format");

    // Read dib
    inp.read(reinterpret_cast<char*>(&img.dib), sizeof(img.dib));
    std::cout << "dib\n";

    // Read pixel array
    int w = img.dib.width, h = img.dib.height;
    int padding = (4 - ((3 * w) % 4)) % 4; // Padding of each row

    img.pixelArr = new Pixel[w * h]; // allocate memory for pixel array
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            inp.read(reinterpret_cast<char*>(&(img.pixelArr)[i * w + j]), sizeof(Pixel));
        }

        // Skip padding
        inp.seekg(padding, std::ios::cur);
    }

    inp.close(); // close file
}

void ImageProcessor::writeImage(const Image& img, const std::string& path) {
    std::ofstream out(path, std::ios::binary); // Open file always sucess
   
    // Write header
    out.write(reinterpret_cast<const char*>(&img.header), sizeof(img.header));
    
    // Write DIB
    out.write(reinterpret_cast<const char*>(&img.dib), sizeof(img.dib));

    int w = img.dib.width, h = img.dib.height;
    int padding = (4 - ((3 * w) % 4)) % 4;
    uint8_t tmp = 0;

    // Write pixel array
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            out.write(reinterpret_cast<const char*>(&img.pixelArr[i * w + j]), sizeof(Pixel));
        }

        // Write padding
        for (int t = 0; t < padding; ++t) 
            out.write(reinterpret_cast<const char*>(&tmp), sizeof(tmp));
    }

    out.close();
}
