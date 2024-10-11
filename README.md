<img src="https://i.imgur.com/y2bQtnZ.png" width="150" height="150" alt="Logo" />

# 42-Cub3D
## Overview
**Cub3d** is a graphical project from **42 School** that involves creating a **simple 3D game engine using raycasting**. It is inspired by early 90s games like Wolfenstein 3D and aims to render a first-person 3D view based on a 2D map. The project covers several topics such as graphics rendering, handling input, and managing game mechanics like player movement and collision detection. It is designed to give students experience with low-level graphics programming and event-driven game loops.

## Getting started
This project is compatible on Linux and macOS.
> If you are on macOS, make sure you have installed **Xcode Command Line Tools**.
1. Clone this repository
```bash
git clone https://github.com/extrymes/42-Cub3D.git
cd 42-Cub3D
```
2. Compile and launch the program
```bash
make
./cub3d <maps/map.cub>
```
The map file must be in `.cub` format, as indicated in the cub3d specifications.

## Map requirements
Maps must conform to cub3d specifications, which are the following:
- The map must be composed of **only 6 possible characters**: `0` for an empty space, `1` for a wall, and `N`, `S` ,`E` or `W` for the player’s starting position and spawning orientation.
- The map must be **surrounded by walls**.
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any order in the file.
- The map must be parsed as it looks in the file. Spaces are a valid part of the map.
- Each element (except the map) first information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as:
	- NO ./path/to/the/north/texture
	- SO ./path/to/the/south/texture
	- WE ./path/to/the/west/texture
	- EA ./path/to/the/east/texture
	- F 70,70,70 (floor color)
	- C 80,180,220 (ceiling color)

The `maps` folder already contains some maps but you can create your own!

## Contributing
We welcome contributions from everyone! Whether you're fixing bugs, adding new features, improving documentation, or simply sharing your ideas, your input is greatly appreciated.

Thanks for visiting and happy coding!
