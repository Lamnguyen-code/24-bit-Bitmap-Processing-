#include "ImageProcessor.hpp"
#include <iostream>

static ImageProcessor imgProcessor;
static const std::string path = "lena.bmp";

int main() {
    Image img;

    try {
        imgProcessor.readImage(img, path);  
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "1\n";

    imgProcessor.writeImage(img, "test.bmp");
    return 0;
}
