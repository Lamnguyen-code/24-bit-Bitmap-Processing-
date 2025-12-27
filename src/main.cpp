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
    // Image test_blur = imgProcessor.blur(img);
    // imgProcessor.writeImage(test_blur, dest_path + "test_blur.bmp");
    //
    // Image much_more_blur = test_blur;
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
    // Image test_sharpen = imgProcessor.sharpen(test_blur);
    // imgProcessor.writeImage(test_sharpen, dest_path + "test_sharpen.bmp");
    //
    // Image much_more_sharpen = much_more_blur;
    // for (int i = 0; i < 20; ++i) 
    //     much_more_sharpen = imgProcessor.sharpen(much_more_sharpen);
    // imgProcessor.writeImage(much_more_sharpen, dest_path + "much_more_sharpen.bmp");


    // ================= Test rotate ===================================
    // Image test_rotateLeft90 = imgProcessor.rotateLeft_90(img);
    // imgProcessor.writeImage(test_rotateLeft90, dest_path + "test_rotateLeft90.bmp");
    //
    // Image test_rotateRight90 = imgProcessor.rotateRight_90(img);
    // imgProcessor.writeImage(test_rotateRight90, dest_path + "test_rotateRight90.bmp");


    // =================== Test Flip ====================================
    // Image test_verticalFlip = imgProcessor.verticalFlip(img);
    // imgProcessor.writeImage(test_verticalFlip, dest_path + "test_verticalFlip.bmp");
    //
    // Image test_horizontalFlip = imgProcessor.horizontalFlip(img);
    // imgProcessor.writeImage(test_horizontalFlip, dest_path + "test_horizontalFlip.bmp");


    // ==================== Test crop ===================================
    // Image test_crop = imgProcessor.crop(img, 0.1, 0.2, 0.2, 0.15);
    // imgProcessor.writeImage(test_crop, dest_path + "test_crop.bmp");


    // ===================== Test resize ================================
    Image test_resize1 = imgProcessor.resize(img, 2, 2);
    Image test_resize2 = imgProcessor.resize(img, 0.5, 0.5);

    imgProcessor.writeImage(test_resize1, dest_path + "test_resize1.bmp");
    imgProcessor.writeImage(test_resize2, dest_path + "test_resize2.bmp");

    return 0;
}
