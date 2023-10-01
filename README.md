
# Ray Tracer Using C++

Welcome to the C++ Ray Tracer, an impressive and feature-rich rendering engine designed to render 3D scenes of spheres. It can create captivating visuals with ease.


## Features

- Render spherical objects
- Takes into account Reflection, Refraction, Total Internal Reflection, and Fuzzy Reflection of a light beam.
- Support for different material types including Metal, Dielectric and Lambertian.
- Multiple Samples per pixel to avoid aliasing at the edges
- Adjustable vertical field of view thereby achieving Zoom functionality
- Variable Camera Position.


## Run Locally

Clone the project

```bash
  git clone https://github.com/x0x/RayTracer
```

Go to the project directory

```bash
  cd my-project
```

Compile main.cpp file. Run the executable and redirect the output to a ppm file.

```bash
    g++ src/main.cpp && ./a.out > image.ppm
```



## Screenshots

### Metal Sphere

![Metal Sphere](https://github.com/x0x/RayTracer/blob/reflective_material/images/Metal_spheres.png)

### Dielectric Material 
![App Screenshot](https://github.com/x0x/RayTracer/blob/reflective_material/images/Dielectric_material.png)

### Hollow Sphere
![App Screenshot](https://github.com/x0x/RayTracer/blob/reflective_material/images/hollow_sphere.png)

### Zoomed In Image
![App Screenshot](https://github.com/x0x/RayTracer/blob/reflective_material/images/zoomed_image.png)

### Zoomed Out Image
![App Screenshot](https://github.com/x0x/RayTracer/blob/reflective_material/images/zoomed_out.png)

### Distant View
![App Screenshot](https://github.com/x0x/RayTracer/blob/reflective_material/images/camera_position_model.png)


