
#include "../so_long.h"
#include <stdio.h>

static void	move_sprites(t_entity *entity, enum e_direction direction)
{
	int	vars;
	int	frames;


	vars = 0;
	while(vars < entity->num_variations)
	{
		frames = 0;
		while(frames < entity->num_frames)
		{
			if (direction == UP)
				entity->sprites[vars][frames]->instances[0].y -= PLAYER_SPEED;
			else if (direction == LEFT)
				entity->sprites[vars][frames]->instances[0].x -= PLAYER_SPEED;
			else if (direction == DOWN)
				entity->sprites[vars][frames]->instances[0].y += PLAYER_SPEED;
			else if (direction == RIGHT)
				entity->sprites[vars][frames]->instances[0].x += PLAYER_SPEED;
			frames++;
		}
		vars++;
	}
}

static enum e_player_motion	get_motion(int last_motion, int direction)
{
	if (direction == LEFT)
		return (MOVING_LEFT);
	else if (direction == RIGHT)
		return (MOVING_RIGHT);
	else if (direction == -1)
	{
		if (last_motion == MOVING_LEFT)
			return (STANDING_LEFT);
		else if (last_motion == MOVING_RIGHT)
			return (STANDING_RIGHT);
	}
	return (last_motion);
}

static void	update_variation(t_entity *player, int direction, int last_motion, int current_frame)
{
	enum e_player_motion	motion;


	motion = get_motion(last_motion, direction);

	if (last_motion != motion)
	{
		player->sprites[last_motion][current_frame]->enabled = false;
		player->sprites[motion][current_frame]->enabled = true;
		player->current_variation = motion;
	}
}

static int	get_steering_key(mlx_t	*mlx)
{

	if (mlx_is_key_down(mlx, MLX_KEY_W))
		return (UP);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		return (DOWN);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		return (LEFT);
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		return (RIGHT);
	else
		return (-1);
}

void	update_map(t_map *map, int direction)
{
	static unsigned int	steps;

	if (direction == UP)
		map->pixel_delta[0] += PLAYER_SPEED;
	else if (direction == DOWN)
		map->pixel_delta[0] -= PLAYER_SPEED;
	else if (direction == LEFT)
		map->pixel_delta[1] -= PLAYER_SPEED;
	else if (direction == RIGHT)
		map->pixel_delta[1] += PLAYER_SPEED;

	if (map->pixel_delta[0] < (-1) * TEXTURE_WIDTH)
	{
		map->player_pos[0] -= 1;
		map->pixel_delta[0] += TEXTURE_WIDTH;
		steps++;
	}
	if (map->pixel_delta[0] >  TEXTURE_WIDTH)
	{
		map->player_pos[0] += 1;
		map->pixel_delta[0] -= TEXTURE_WIDTH;
		steps++;
	}
	if (map->pixel_delta[1] >  TEXTURE_WIDTH)
	{
		map->player_pos[1] += 1;
		map->pixel_delta[1] -= TEXTURE_WIDTH;
		steps++;
	}
	if (map->pixel_delta[1] <  (-1) * TEXTURE_WIDTH)
	{
		map->player_pos[1] -= 1;
		map->pixel_delta[1] += TEXTURE_WIDTH;
		steps++;
	}
}

void	move_player(mlx_t *mlx, t_entity *player, t_map *map)
{
	int	direction;

	direction = get_steering_key(mlx);
	if (direction != UP && direction != DOWN)
		update_variation(player, direction, player->current_variation, player->current_frame);
	update_map(map, direction);
	// check_movability()
	move_sprites(player, direction);
	// update steps

}
