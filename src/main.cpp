#include "ImageProcessor.hpp"
#include <iostream>

static ImageProcessor imgProcessor;
static const std::string src_path = "../src_images/lena.bmp";
static const std::string dest_path = "../res_images/";

int main() {
    Image img;

    // Read image
    try {
        imgProcessor.readImage(img, src_path);  
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    
    // ============= Test Grayscale ===============================
    Image test_grayscale = imgProcessor.convertGrayscale(img); 
    imgProcessor.writeImage(test_grayscale, dest_path + "test_grayscale.bmp");


    // ============== Test brightness modifying ===================
    Image test_brightness1 = imgProcessor.modifyBrightness(img, 2.0);
    Image test_brightness2 = imgProcessor.modifyBrightness(img, 0.5);

    imgProcessor.writeImage(test_brightness1, dest_path + "test_brightness1.bmp");
    imgProcessor.writeImage(test_brightness2, dest_path + "test_brightness2.bmp");


    // =============== Test reverse color ==========================
    Image test_reverseColor = imgProcessor.reverseColor(img);
    imgProcessor.writeImage(test_reverseColor, dest_path + "test_reverseColor.bmp");
    return 0;
}
