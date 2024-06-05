# miniRT: My First RayTracer with miniLibX

## Overview

Welcome to miniRT, a project that introduces you to the fascinating world of Ray Tracing! This project aims to help you create simple computer-generated images using the Ray Tracing technique. By the end of this project, you'll be able to render basic 3D scenes and understand the core concepts behind Ray Tracing.

## What is Ray Tracing?

Ray Tracing is a rendering technique used to create realistic images by simulating the way light interacts with objects. Unlike the more common "Rasterization" method used in most graphics engines, Ray Tracing can produce highly realistic images, although it is more computationally intensive.

## Project Goals

- Implement a basic Ray Tracer in C using MLX42.
- Render simple 3D scenes with basic geometric objects such as planes, spheres, and cylinders.
- Apply basic transformations (translation and rotation) to objects.
- Manage lighting to create effects like shadows, ambient lighting, reflections and shininess.

## Features

- **Basic Geometric Objects**: Render planes, spheres, and cylinders.
- **Transformations**: Apply translations and rotations to objects, lights, and cameras.
- **Lighting**: Implement ambient and diffuse lighting to enhance the realism of the scene.

## Explanation of the Scene File

### Ambient Light
| Symbol | Strength [0-1] | Color RGB [0-255] |
|--------|----------------|-------------------|
| A      | 0.25           | 255,255,255       |

### Camera
| Symbol | Position XYZ | Rotation XYZ | FOV [0-180] | (Nbr of Reflections) | (Nbr of Antialiasing) | (Nbr of Threads [1-32]) |
|--------|--------------|--------------|-------------|----------------------|-----------------------|-------------------------|
| C      | 0,1,0        | 0,0,1        | 70          | 1                    | 50                    | 8                       |

### Light
| Symbol | Position XYZ | Intensity [0-1] | Color RGB [0-255] |
|--------|--------------|-----------------|-------------------|
| L      | 0,74,100     | 0.7             | 255,255,255       |

### Objects

### Sphere
| Symbol | Position XYZ | Radius | Color RGB [0-255] | (Shininess [0-inf]) | (Reflectiveness [0-1]) |
|--------|--------------|--------|-------------------|---------------------|------------------------|
| sp     | 0,0,70       | 10     | 255,255,255       | 10                  | 0.5                    |

### Plane
| Symbol | Position XYZ | Rotation XYZ | Color RGB [0-255] | (Shininess [0-inf]) | (Reflectiveness [0-1]) | (Width) | (Height) |
|--------|--------------|--------------|-------------------|---------------------|------------------------|---------|----------|
| pl     | 0,20,120     | 1,1,0        | 255,255,255       | 3010                | 0.5                    | 20      | 15       |

### Cylinder
| Symbol | Position XYZ | Rotation XYZ  | Diameter | Height | Color RGB [0-255] | (Shininess [0-inf]) | (Reflectiveness [0-1]) |
|--------|--------------|---------------|----------|--------|-------------------|---------------------|------------------------|
| cy     | 30,-20,115   | -0.25,1,-0.75 | 15       | 40     | 255,255,255       | 1000                | 0.5                    |

### Cone
| Symbol | Position XYZ | Rotation XYZ | Diameter | Height | Color RGB [0-255] | (Shininess [0-inf]) | (Reflectiveness [0-1]) |
|--------|--------------|--------------|----------|--------|-------------------|---------------------|------------------------|
| co     | 0,10,0       | 0,0,1        | 2        | 10     | 255,255,255       | 500                 | 0.25                   |
