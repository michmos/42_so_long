
#include "../so_long.h"
#include <math.h>
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
	else if (direction == UP || direction == DOWN)
	{
		if (last_motion == MOVING_LEFT || last_motion == STANDING_LEFT)
			return (MOVING_LEFT);
		if (last_motion == MOVING_RIGHT || last_motion == STANDING_RIGHT)
			return (MOVING_RIGHT);
	}
	else if (direction == -1)
	{
		if (last_motion == MOVING_LEFT)
			return (STANDING_LEFT);
		else if (last_motion == MOVING_RIGHT)
			return (STANDING_RIGHT);
	}
	return (last_motion);
}

static void	update_motion(t_entity *player, int direction, int last_motion, int current_frame)
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

static int	is_wall(char **map_2d, t_vector *new_pos)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = (int) new_pos->x;
	x2 = round(new_pos->x);
	y1 = (int) new_pos->y;
	y2 = round(new_pos->y);
	if (map_2d[y1][x1] == WALL || map_2d[y1][x2] == WALL 
		|| map_2d[y2][x1] == WALL || map_2d[y2][x2] == WALL)
	{
		return (1);
	}
	return (0);
}

void	update_map(t_map *map, int direction)
{
	static unsigned int	steps;
	t_vector			new_pos;

	if (direction == UP)
		new_pos.y = map->player_pos.y - ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == DOWN)
		new_pos.y = map->player_pos.y + ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == LEFT)
		new_pos.x = map->player_pos.x - ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == RIGHT)
		new_pos.x = map->player_pos.x + ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);

	if (is_wall(map->map_2d, &new_pos))
		;
	if (round(new_pos.y) != round(map->player_pos.y) || round(new_pos.x) != round(map->player_pos.x))
		steps++;
	map->player_pos.x = new_pos.x;
	map->player_pos.y = new_pos.y;
}

static int	wall_check(int pixel_delta[2], t_map *map)
{
	int	y;
	int	x;

	y = map->player_pos[0];
	x = map->player_pos[1];
	if (pixel_delta[0] < 0 && y > 0 && map->map_2d[y - 1][x] == WALL)
		return (1);
	else if (pixel_delta[0] > 0 && y < map->height - 1 && map->map_2d[y + 1][x] == WALL)
		return (1);
	else if (pixel_delta[1] < 0 && x > 0 && map->map_2d[y][x - 1] == WALL)
		return (1);
	else if (pixel_delta[1] > 0 && x < map->width - 1 && map->map_2d[y][x + 1] == WALL)
		return (1);
	else
		return (0);
}

static int update_player_pos(int direction, t_map *map, t_entity *player)
{
	int			step;
	static int	pixel_delta[2];
	int			backup[2];

	printf("pixel delta y %i x %i\n", pixel_delta[0], pixel_delta[1]);
	step = 0;
	ft_memcpy(backup, pixel_delta, sizeof(int) * 2);
	update_pixel_delta(direction, pixel_delta);
	if (wall_check(pixel_delta, map) == true)
	{
		ft_memcpy(pixel_delta, backup, sizeof(int) * 2);
		return (0);
	}
	map->player_pos[0] += pixel_delta[0] / TEXTURE_WIDTH;
	map->player_pos[1] += pixel_delta[1] / TEXTURE_WIDTH;
	if (pixel_delta[0] / TEXTURE_WIDTH != 0 || pixel_delta[1] / TEXTURE_WIDTH != 0)
		step = 1;
	pixel_delta[0] %= TEXTURE_WIDTH;
	pixel_delta[1] %= TEXTURE_WIDTH;
	move_sprites(player, direction);
	return (step);
}


void	move_player(mlx_t *mlx, t_entity *player, t_map *map)
{
	int					direction;
	static unsigned int	steps;

	direction = get_steering_key(mlx);
	if (direction != UP && direction != DOWN)
		update_variation(player, direction, player->current_variation, player->current_frame);
	update_map(map, direction);
	move_sprites(player, direction);
}
