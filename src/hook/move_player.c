
#include "../so_long.h"
#include <stdio.h>

static void	print_step_count(mlx_t *mlx, t_map *map, int steps)
{
	mlx_image_t	*steps_img;
	static int	count;
	char 		*temp;

	temp = ft_itoa(steps); // TODO: protect
	if (!temp)
		;
	if (count == 0)
	{
		if(!mlx_put_string(mlx, "steps: ", STEP_COUNT_POS_X, STEP_COUNT_POS_Y))
			; // TODO: protect. dont forget temp
	}
	else
	{
		mlx_delete_image(mlx, map->step_count);
	}
	map->step_count = mlx_put_string(mlx, temp, STEP_COUNT_POS_X + 80, STEP_COUNT_POS_Y);
	free(temp);
	if (!map->step_count)
		; // TODO: protect
	count++;
}

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

static bool	is_valid_overlap(double pos, int allowed_overlap)
{
	double	limit;
	
	limit = (double) allowed_overlap / 100.0;
	return (fmod(pos, 1.0) < limit || fmod(pos, 1.0) > 1.0 - limit);
}

static int	is_wall(char **map_2d, t_vector *new_pos)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	y1 = ceil(new_pos->y);
	y2 = floor(new_pos->y);
	if (is_valid_overlap(new_pos->y, P_W_OVERLAP_Y))
	{
		y1 = round(new_pos->y);
		y2 = y1;
	}
	x1 = ceil(new_pos->x);
	x2 = floor(new_pos->x);
	if (is_valid_overlap(new_pos->x, P_W_OVERLAP_X))
	{
		x1 = round(new_pos->x);
		x2 = x1;
	}
	if (map_2d[y1][x1] == WALL || map_2d[y1][x2] == WALL 
		|| map_2d[y2][x1] == WALL || map_2d[y2][x2] == WALL)
	{
		return (1);
	}
	return (0);
}

static int	update_pos(t_map *map, int direction, unsigned int *steps)
{
	t_vector			new_pos;

	new_pos.x = map->player_pos.x;
	new_pos.y = map->player_pos.y;
	if (direction == UP)
		new_pos.y -= ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == DOWN)
		new_pos.y += ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == LEFT)
		new_pos.x -= ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == RIGHT)
		new_pos.x += ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);

	if (is_wall(map->map_2d, &new_pos))
		return (WALL);
	if (round(new_pos.y) != round(map->player_pos.y) || round(new_pos.x) != round(map->player_pos.x))
		*steps += 1;
	map->player_pos.x = new_pos.x;
	map->player_pos.y = new_pos.y;
	return (0);
}

void	move_player(mlx_t *mlx, t_entity *player, t_map *map)
{
	int					direction;
	static unsigned int	steps;
	unsigned int		temp;

	direction = get_steering_key(mlx);
	update_motion(player, direction, player->current_variation, player->current_frame);
	temp = steps;
	if (update_pos(map, direction, &steps) == WALL)
		return ;
	move_sprites(player, direction);
	if (temp != steps)
		print_step_count(mlx, map, steps);
}
