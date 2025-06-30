
# cub3D - Our First RayCaster with miniLibX

A realistic 3D graphical representation of a maze from a first-person perspective, built using raycasting principles and the miniLibX graphics library.

## 🎯 Project Overview

This project is an introduction to raycasting, a vintage yet elegant technique that allowed early 3D games like **Wolfenstein 3D** to render 3D graphics using only 2D calculations. The result delivers an immersive first-person maze exploration experience.

### Core Concept

Raycasting works by casting rays from the player's position for each vertical column of pixels on the screen. Each ray travels through the map until it hits a wall, and the distance determines the wall's rendered height - creating the illusion of 3D depth.

## 🏗️ Implementation Architecture

### 1. Configuration Parsing
The program accepts `.cub` files containing:
- **Texture paths**: North (NO), South (SO), East (EA), West (WE) wall textures
- **Colors**: Floor (F) and ceiling (C) RGB values in format `R,G,B`
- **Map layout**: Grid-based maze with walls (`1`), empty spaces (`0`), and player spawn (`N/S/E/W`)

Example configuration:
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,230,255

111111
100101
101001
1100N1
111111
```

### 2. Mathematical Foundation

#### Vector-Based Direction System
Instead of using traditional Euclidean angles, this implementation uses **vectors** for intuitive direction handling:

- **Position Vector**: Player's (x, y) coordinates in the map
- **Direction Vector**: Where the player faces (e.g., North = `(0, -1)`, East = `(1, 0)`)
- **Camera Plane**: Perpendicular to direction vector, represents the field of view

#### Ray Calculation
Every point along a ray follows the formula:
```
Ray Point = Player Position + (Distance × Direction Vector)
```

For each screen column, the ray direction is calculated as:
```c
ray_dir.x = player->dir.x + player->plane.x * camera_x;
ray_dir.y = player->dir.y + player->plane.y * camera_x;
```

### 3. DDA Algorithm (Digital Differential Analyzer)

The DDA algorithm efficiently traces rays through the grid-based map:

1. **Delta Distance**: How far the ray travels to cross one grid cell
2. **Side Distance**: Distance to the next grid boundary
3. **Stepping**: Move through grid cells until hitting a wall
4. **Wall Detection**: Check if current cell contains a wall (`'1'`)

Key advantages:
- **Efficiency**: Only checks grid intersections, not every point
- **Accuracy**: Guarantees finding the closest wall
- **Simplicity**: Pure integer arithmetic in the main loop

### 4. Rendering Pipeline

#### Wall Rendering
1. **Distance Calculation**: Get perpendicular distance to avoid fisheye effect
2. **Height Calculation**: `wall_height = screen_height / distance`
3. **Texture Mapping**: Map wall textures based on hit side (N/S/E/W)
4. **Column Drawing**: Render textured wall column with proper scaling

#### Perspective Correction
The implementation uses perpendicular distance rather than Euclidean distance to prevent the "fisheye" distortion effect common in naive raycasting implementations.

## 🎮 Controls

| Input | Action |
|-------|--------|
| `W A S D` | Move forward/left/backward/right |
| `←` `→` | Look left/right |
| `ESC` | Exit program |
| `Red X` | Close window |

## 🛠️ Technical Features

### Graphics Engine
- **miniLibX Integration**: Cross-platform graphics using X11
- **Framebuffer Rendering**: Double-buffered smooth animation
- **Texture System**: XPM image loading and mapping
- **Color Management**: RGB ceiling and floor rendering

### Performance Optimizations
- **Efficient Ray Traversal**: DDA algorithm minimizes calculations
- **Boundary Checking**: Safe memory access with map validation
- **Vector Mathematics**: Optimized direction calculations
- **Smooth Movement**: Collision detection and fluid player movement

## 📁 Project Structure

```
cub3D/
├── src/
│   ├── raycasting/         # Core raycasting algorithms
│   │   ├── raycasting.c    # Main ray casting loop
│   │   └── dda.c           # DDA algorithm implementation
│   ├── render/             # Graphics rendering
│   │   ├── draw_textured_wall.c
│   │   └── init_wall.c
│   ├── init/               # Initialization systems
│   │   ├── init_player.c
│   │   ├── init_texture.c
│   │   └── init_data.c
│   ├── event/              # Input handling
│   │   ├── hook.c
│   │   ├── movement.c
│   │   └── update_position.c
│   └── minimap/            # 2D debug view
├── inc/
│   ├── cub3D.h
│   └── structures.h
└── Makefile
```

## 🔧 Compilation & Usage

### Requirements
- **miniLibX**: Graphics library (included)
- **libft**: 42's standard library
- **Math Library**: Link with `-lm`
- **X11**: For Linux systems

### Build
```bash
make                    # Compile the project
make clean             # Remove object files
make fclean            # Full cleanup
make re                # Rebuild everything
```

### Run
```bash
./cub3D maps/map.cub
```

## 🎓 Learning Outcomes

This project provides deep understanding of:
- **3D Graphics Fundamentals**: How early 3D engines worked
- **Vector Mathematics**: Practical application in game development
- **Algorithm Optimization**: Efficient grid traversal techniques
- **Graphics Programming**: Real-time rendering and texture mapping
- **Memory Management**: Safe handling of dynamic data structures

## 📚 References

- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting guide
- **Wolfenstein 3D**: Historical reference for raycasting in games
- **miniLibX Documentation**: 42's graphics library reference

## 🏆 42 School Project

This project is part of the 42 School curriculum, focusing on:
- **Graphics programming** fundamentals
- **Mathematical concepts** in computer graphics
- **Algorithm implementation** and optimization
- **C programming** best practices

---

*"The elegance of raycasting lies in its simplicity - creating the illusion of 3D worlds through the clever manipulation of 2D mathematics."*
