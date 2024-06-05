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
