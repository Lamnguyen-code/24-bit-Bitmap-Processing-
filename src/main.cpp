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
    // Image test_grayscale = imgProcessor.convertGrayscale(img); 
    // imgProcessor.writeImage(test_grayscale, dest_path + "test_grayscale.bmp");


    // ============== Test brightness modifying ===================
    // Image test_brightness1 = imgProcessor.modifyBrightness(img, 2.0);
    // Image test_brightness2 = imgProcessor.modifyBrightness(img, 0.5);

    // imgProcessor.writeImage(test_brightness1, dest_path + "test_brightness1.bmp");
    // imgProcessor.writeImage(test_brightness2, dest_path + "test_brightness2.bmp");


    // =============== Test reverse color ==========================
    // Image test_reverseColor = imgProcessor.reverseColor(img);
    // imgProcessor.writeImage(test_reverseColor, dest_path + "test_reverseColor.bmp");
    
    
    // =============== Test blur ==============================
    Image test_blur = imgProcessor.blur(img);
    // imgProcessor.writeImage(test_blur, dest_path + "test_blur.bmp");
    //
    Image much_more_blur = test_blur;
    // for (int i = 0; i < 50; ++i) 
    //     much_more_blur = imgProcessor.blur(much_more_blur);
    // imgProcessor.writeImage(much_more_blur, dest_path + "much_more_blur.bmp");


     // =============== Test Gaussian blur ==============================
    // Image test_gaussianBlur = imgProcessor.gaussianBlur(img);
    // imgProcessor.writeImage(test_gaussianBlur, dest_path + "test_gaussianBlur.bmp");
    //
    // Image much_more_gaussianBlur = test_gaussianBlur;
    // for (int i = 0; i < 50; ++i) 
    //     much_more_gaussianBlur = imgProcessor.gaussianBlur(much_more_gaussianBlur);
    // imgProcessor.writeImage(much_more_gaussianBlur, dest_path + "much_more_gaussianBlur.bmp");
    
    
    // ================= Test sharpen ===================================
    Image test_sharpen = imgProcessor.sharpen(test_blur);
    imgProcessor.writeImage(test_sharpen, dest_path + "test_sharpen.bmp");

    Image much_more_sharpen = much_more_blur;
    for (int i = 0; i < 20; ++i) 
        much_more_sharpen = imgProcessor.sharpen(much_more_sharpen);
    imgProcessor.writeImage(much_more_sharpen, dest_path + "much_more_sharpen.bmp");
    return 0;
}
