#pragma once

#include "Image.hpp"
#include <string>
#include <fstream>
#include <exception>
#include <limits>
#include <cmath>
#include <vector>

const double EPS = std::numeric_limits<double>::epsilon();

class ImageProcessor {
private:
public:
    void readImage(Image&, const std::string&); // Read image from path
    void writeImage(const Image&, const std::string&); // Write image to path
    Image convertGrayscale(const Image&); // Convert image to grayscale 
    Image modifyBrightness(const Image&, const double&); // Modify brightness of image
    Image reverseColor(const Image&); // Reverse color of an image
    Image blur(const Image&); // blur the image
    Image gaussianBlur(const Image&);// gaussian blur the image
    Image sharpen(const Image&); // sharpen image
    Image rotateLeft_90(const Image&); // rotate image 90 degree clockwisely
    Image rotateRight_90(const Image&); // rotate image 90 degree anti-clockwisely
    Image verticalFlip(const Image&); // Flip the image veritcally
    Image horizontalFlip(const Image&); // Flip the image horizontally
    Image crop(const Image&, double, double, double, double); // crop image, params are top, bottom, right, left
    Image resize(const Image&, double, double); // resize image
}; 
