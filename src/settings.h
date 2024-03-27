#ifndef SETTINGS_H
# define SETTINGS_H

# define TEXTURE_WIDTH 128

# define SPACE_FPS 4
# define SPACE_TEXTURE "textures/space/water.png"
# define WALL_FPS 4
# define WALL_TEXTURE "textures/walls/rocks.png"
# define PLAYER_FPS 4
# define PLAYER_TEXTURE "textures/player/boat.png"
# define EXIT_FPS 4
# define EXIT_TEXTURE "textures/exit/exit.png"
# define ITEM_FPS 2
# define ITEM_TEXTURE "textures/items/trash.png"
# define ENEMY_FPS 4
# define ENEMY_TEXTURE "textures/enemies/fish.png"
# define PLAYER_SPEED 5

enum e_player_motion
{
	STANDING_RIGHT = 0,
	STANDING_LEFT,
	MOVING_RIGHT,
	MOVING_LEFT,
	ENDING_RIGHT,
	ENDING_LEFT
};

#endif
