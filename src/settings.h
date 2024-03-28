#ifndef SETTINGS_H
# define SETTINGS_H

// widht in pixel for all textures
# define TEXTURE_WIDTH 128

// FPS of the sprites
# define SPACE_FPS 4
# define WALL_FPS 4
# define PLAYER_FPS 4
# define EXIT_FPS 4
# define ITEM_FPS 2
# define ENEMY_FPS 4

// how fast does the player move in pixel
# define PLAYER_SPEED 5

// paths to the entity textures
# define SPACE_TEXTURE "textures/space/water.png"
# define WALL_TEXTURE "textures/walls/rocks.png"
# define PLAYER_TEXTURE "textures/player/boat.png"
# define EXIT_TEXTURE "textures/exit/exit.png"
# define ITEM_TEXTURE "textures/items/trash.png"
# define ENEMY_TEXTURE "textures/enemies/fish.png"

// in case of the player the different rows of the sprite sheet
// actually refer to different motions and not different variations
// this enum defines which motion is stored in which row
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
