#include "../include/vec3.h"
#include "../include/color.h"
#include <iostream>

int main() {
    const int imageWidth = 256;
    const int imageHeight = 256;


    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = imageHeight-1 ; j>=0 ; j-- ) {
        std::cerr << "\rScanlines remaining: " <<j << " " << std::flush;
        for(int i = 0 ; i< imageWidth ; i++) {
            auto r = double(i) / (imageWidth-1);
            auto g = double(j) / (imageWidth-1);
            auto b = 0.25;

            color pixelColor(r,g,b);
            writeColor(std::cout , pixelColor);

        }
    }

    std::cerr << "\nDone.\n";
}
