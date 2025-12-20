#include "ImageProcessor.hpp"
#include <iostream>

/*
 * @brief: Read an 24-bit bitmap
 * @param img: dest image to read in
 * @param path: image path to read
 */
void ImageProcessor::readImage(Image& img, const std::string& path) {
    // Open file
    std::ifstream inp(path, std::ios::binary);
    // Invalid path
    if (!inp) throw std::invalid_argument("Invalid path\n");

    // Read header
    inp.read(reinterpret_cast<char*>(&img.header), sizeof(img.header));
    
    if (img.header.signature != 0x4D42) // check 24bitmap format
        throw std::invalid_argument("Invalid file format");

    // Read dib
    inp.read(reinterpret_cast<char*>(&img.dib), sizeof(img.dib));

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

/*
 * @brief Write a 24-bit bitmap
 * @param img: source image
 * @param path: dest file to write
 */
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

/*
 * @brief Convert an image to grayscale
 * @param img: source image
 */
Image ImageProcessor::convertGrayscale(const Image& img) {
    Image res;

    // Copy header and dib, because header and dib of res image stay the same to img
    res.header = img.header;
    res.dib = img.dib;

    // Grayscale Pixel array
    int w = img.dib.width, h = img.dib.height;
    res.pixelArr = new Pixel[w * h]; // allocate memory

    // Process each Pixel
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int idx = i * w + j;
            uint8_t tmp = static_cast<uint8_t>(0.299*img.pixelArr[idx].red + 0.587*img.pixelArr[idx].green + 0.114*img.pixelArr[idx].blue);

            res.pixelArr[idx].red = res.pixelArr[idx].green = res.pixelArr[idx].blue = tmp; 
        }
    }

    return res;
}

/*
 * @brief Modify brightness of image
 * @param img: source image
 * @param bias: bias of brightness
 */
Image ImageProcessor::modifyBrightness(const Image& img, const double& rate) {
    if (fabs(rate) <= EPS) return Image(); // Check if rate == 0

    Image res;
    // Remain header and dib
    res.header = img.header;
    res.dib = img.dib;

    int w = img.dib.width, h = img.dib.height;
    res.pixelArr = new Pixel[w * h]; // allocate memory for Pixel array
    
    // Process pixel array
    int size = w * h;
    for (int i = 0; i < size; ++i) {
        // Modify red
        res.pixelArr[i].red = static_cast<uint8_t>(255 * pow((img.pixelArr[i].red * 1.0 / 255), 1.0/rate)); 

        // Modify green
        res.pixelArr[i].green = static_cast<uint8_t>(255 * pow((img.pixelArr[i].green * 1.0 / 255), 1.0/rate)); 

        // Modify blue
        res.pixelArr[i].blue = static_cast<uint8_t>(255 * pow((img.pixelArr[i].blue * 1.0 / 255), 1.0/rate)); 
    }

    return res;
}

/*
 * @brief Reverse color of an image
 * @param img: source image
 */
Image ImageProcessor::reverseColor(const Image& img) {
    Image res = img; // Create res with all attribute equal to img (deep copy)

    // Reverse each pixel
    for (int i = 0; i < img.dib.width * img.dib.height; ++i) {
        res.pixelArr[i].red = 255 - res.pixelArr[i].red;
        res.pixelArr[i].green = 255 - res.pixelArr[i].green;
        res.pixelArr[i].blue = 255 - res.pixelArr[i].blue;
    }

    return res;
}

/*
 * @brief Blur the image
 * @param img: source image
 */
Image ImageProcessor::blur(const Image& img) {
    Image res = img;
    
    int w = img.dib.width, h = img.dib.height;
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) { // iteratre through every pixel except for pixels on edges

            // iterate from (i - 1, j - 1) to (i + 1, j + 1)
            unsigned newRed = 0, newGreen = 0, newBlue = 0;
            for (int t = -1; t <= 1; ++t) {
                for (int k = -1; k <= 1; ++k) {

                    // add all surrouded pixels
                    newRed += img.pixelArr[img.idx(i + t, j + k)].red;
                    newGreen += img.pixelArr[img.idx(i + t, j + k)].green;
                    newBlue += img.pixelArr[img.idx(i + t, j + k)].blue;
                }
            }

            newRed /= 9, newBlue /= 9, newGreen /= 9;

            // assign new pixel color 
            res.pixelArr[res.idx(i, j)] = Pixel(newBlue, newGreen, newRed);
        } 
    }

    return res;
}

/*
 * @brief Blur the image (Gaussian)
 * @param img: source image
 */
Image ImageProcessor::gaussianBlur(const Image& img) {
    Image res = img;
    
    int w = img.dib.width, h = img.dib.height;
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) { // iteratre through every pixel except for pixels on edges

            // iterate from (i - 1, j - 1) to (i + 1, j + 1)
            unsigned newRed = 0, newGreen = 0, newBlue = 0;
            for (int t = -1; t <= 1; ++t) {
                for (int k = -1; k <= 1; ++k) {
                    // compute coefficient
                    unsigned int coef = pow(2, 2 - abs(t) - abs(k));

                    // add all surrouded pixels
                    newRed += coef * img.pixelArr[img.idx(i + t, j + k)].red;
                    newGreen += coef * img.pixelArr[img.idx(i + t, j + k)].green;
                    newBlue += coef * img.pixelArr[img.idx(i + t, j + k)].blue;
                }
            }

            newRed /= 16, newBlue /= 16, newGreen /= 16;

            // assign new pixel color 
            res.pixelArr[res.idx(i, j)] = Pixel(newBlue, newGreen, newRed);
        } 
    }

    return res;
}

/*
 * @brief Sharpen the image
 * @param img: source image
 */
Image ImageProcessor::sharpen(const Image& img) {
    Image res = img;
    
    // iterate through every pixels except for pixels on edges
    int w = img.dib.width, h = img.dib.height;
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            // compute new value
            int newRed = 5*img.pixelArr[img.idx(i, j)].red - img.pixelArr[img.idx(i - 1, j)].red - img.pixelArr[img.idx(i + 1, j)].red - img.pixelArr[img.idx(i, j - 1)].red - img.pixelArr[img.idx(i, j + 1)].red;
            int newGreen = 5*img.pixelArr[img.idx(i, j)].green - img.pixelArr[img.idx(i - 1, j)].green - img.pixelArr[img.idx(i + 1, j)].green - img.pixelArr[img.idx(i, j - 1)].green - img.pixelArr[img.idx(i, j + 1)].green;
            int newBlue = 5*img.pixelArr[img.idx(i, j)].blue - img.pixelArr[img.idx(i - 1, j)].blue - img.pixelArr[img.idx(i + 1, j)].blue - img.pixelArr[img.idx(i, j - 1)].blue - img.pixelArr[img.idx(i, j + 1)].blue;

            // assign and normalize to (0, 255)
            res.pixelArr[res.idx(i, j)].red = static_cast<uint8_t>(std::max(0, std::min(newRed, 255))); 
            res.pixelArr[res.idx(i, j)].green = static_cast<uint8_t>(std::max(0, std::min(newGreen, 255))); 
            res.pixelArr[res.idx(i, j)].blue = static_cast<uint8_t>(std::max(0, std::min(newBlue, 255))); 
        }
    }

    return res;
}
