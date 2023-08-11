#include "../include/color.h"
#include "../include/vec3.h"
#include "../include/ray.h"
#include <iostream>


color ray_color(const ray& r) {

    vec3 unitVector = unit_vector(r.direction());
    auto temp = 0.5 * (unitVector.y() + 1);
    return (1-temp) * color(1,0,0) + temp * color(0,0,1);
    
}

int main() {

  const double aspectRatio = 16.0 / 9.0;
  const int imageWidth = 1020;
  const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

  auto focalLength = 1.0;
  auto viewportHeight = 1.5;
  auto viewportWidth =
      viewportHeight * (static_cast<double>(imageWidth / imageHeight));
  auto cameraPosition = vec3(0, 0, 0);

  auto viewportX = vec3(viewportWidth, 0, 0);
  auto viewportY = vec3(0, -viewportHeight, 0);

  auto deltaX = viewportX / imageWidth;
  auto deltaY = viewportY / imageHeight;

  auto viewportUpperLeft = cameraPosition - viewportX / 2.0 - viewportY / 2.0 -
                           vec3(0, 0, focalLength);

  auto pixel00Location = viewportUpperLeft + (deltaX / 2.0) + (deltaY / 2.0);

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int j = imageHeight - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << std::flush;
    for (int i = 0; i < imageWidth; i++) {

      auto pixelCentre = pixel00Location + i * deltaX + j * deltaY;
      auto rayDirection = pixelCentre - cameraPosition;

      ray r (cameraPosition , rayDirection);
      color pixelColor = ray_color(r);
      writeColor(std::cout, pixelColor);

    }
  }
  std::cerr << "\nDone.\n";
}
