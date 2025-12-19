#pragma once

#include "Image.hpp"
#include <string>
#include <fstream>
#include <exception>

class ImageProcessor {
private:
public:
    void readImage(Image&, const std::string&); // Read image from path
    void writeImage(const Image&, const std::string&); // Write image to path
};
