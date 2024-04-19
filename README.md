# 42 so_long
## Utilization
### Cloning
Run the following command to clone the repo and build the executable:
```
git clone git@github.com:michmos/42_so_long.git && cd 42_so_long && make
```
### Running
Run the executable with the map-path as an argument. You can chose any map from the maps directory or create your own map.
```
./so_long maps/map1.ber
```
### Navigating
Use `WASD` to navigate the player through the map.
### Goal
You are ocean cleanup. Collect all the trash from the ocean and reach the exit without catching any fish.
## About the project
### Task
The task was to create a 2D game with a player, items and an exit. The program takes the path to a map as an input and checks the validity of the input with regard to criteria such as:
* the map must be rectangular
* the map must be surrounded by walls (1s)
* there is only one player and one exit and at least one item
* there must be a valid path from start to end
* ...
The bonus part required animations, randomly moving enemies and a step count.
### Learnings
This project introduced two new things:
* it was my first graphical project allowing me to learn about colors, pixels and animations.
* it was also the first project where we could use an external library (in our case MLX42) and everything that comes with it (documentation ;), hooks, leaks in the library, git submodules etc.)
### Theme
I went for an ocean cleanup theme but the project architecture allows to change the theme by just changing the images in the texture directory `*`.


`*` as long as you stick to the same formalities (e.g. rows on a sprite sheet represent a different variation, all variations on a sprite sheet have the same amount of frames ...)
