# cub3D: An Initiation to Raycasting

Raycasting is a rendering technique from the early 1990s that creates the illusion of 3D using only 2D calculations. It originated from Wolfenstein, the first first-person shooter video game. During that era, computers didn't have the extravagant power and capabilities our modern machines possess. To overcome this obstacle, developers had to think cleverly and imagine creative, surprising ways to create such impressive results—and that's how Wolfenstein and raycasting techniques were born.

## The Project
This is a 42 school project that challenges students to create their first raycasting engine. The goal is to render a 3D environment using a raycasting engine, featuring a player wandering through a maze surrounded by textured cubic walls.

A configuration file serves as the program's sole argument. This file contains information about texture paths, ceiling and floor colors, and the map layout. The configuration file must be parsed to verify that the map and data are valid before initializing the game.

Graphic rendering is accomplished using MinilibX, a graphical library developed by 42 (an API built on X11 - check [here](https://x.org/wiki/)) designed for beginners in graphics programming. You can find the repository [here](https://github.com/42paris/minilibx-linux) and essential documentation [here](https://harm-smits.github.io/42docs/libs/minilibx). For additional MinilibX guidance, check out the excellent tutorials by Oceano on [YouTube](https://www.youtube.com/@onaecO).

### Raycasting Implementation
There are multiple ways to develop a raycasting engine. In this implementation, we follow the tutorial by Lode Vandevenne ([available here](https://lodev.org/cgtutor/raycasting.html))—an excellent C++ tutorial that we adapted step by step.

In this implementation, we work with vectors rather than Euclidean angles. (Check [here](https://www.mathsisfun.com/algebra/vectors.html) to refresh your understanding of vector arithmetic—it's quite simple but worth reviewing).

We use 3 vectors:
- **Player position**
- **Direction vector** the player is facing (e.g., (0, -1) = North)
- **Plane vector**: This represents our player's field of view and defines what we render in 3D. The plane vector must always be perpendicular to the direction vector. Its magnitude defines our field of view angle. To simulate human vision, we set this value to 0.66 and multiply the perpendicular direction by this magnitude.

### Raycasting Pipeline
We draw on a framebuffer that refreshes every frame.

To render a 3D wall maze, we cast one ray per screen width pixel in different directions. These rays travel through the map until they hit a wall. We can then determine the distance from the player to the wall, and based on this distance, we draw the wall with appropriate height. This creates as many pixel columns on screen as there are pixels in width.

##### 1. Calculate Ray Direction
We map the screen onto our plane vector using linear interpolation. We then calculate the ray direction based on the player's facing direction and the product of the plane vector with the interpolation result.

##### 2. Perform DDA
The Digital Differential Analyzer is an optimized algorithm that helps us check at every grid boundary the ray traverses whether that grid contains a wall. With proper distance incrementation, we can efficiently check each time we cross a new grid cell on the x or y axis.

##### 3. Get Wall Distance
Working with vectors allows us to avoid the "fisheye effect"—a well-known phenomenon in raycasting. This effect is avoided by using the perpendicular wall distance from the player position.

##### 4. Draw the Textured Wall
The final step involves rendering the wall. For a textured wall, we need the exact point where the ray hits the wall—this gives us the texture column to work with. We then extract the color pixel from this texture pixel and draw it to our buffer.

## Usage
```bash
make
./cub3D maps/example.cub
```

## Controls
- **WASD**: Move around the maze
- **Arrow keys**: Look left/right  
- **ESC**: Exit the program

## Configuration File Format
The .cub file defines textures, colors, and the map layout:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## Resources
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - The main tutorial we followed
- [MinilibX Repository](https://github.com/42paris/minilibx-linux) - Graphics library
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Essential documentation  
- [Oceano's YouTube Tutorials](https://www.youtube.com/@onaecO) - Additional MinilibX guidance
- [Vector Mathematics Refresher](https://www.mathsisfun.com/algebra/vectors.html) - Vector arithmetic basics
