
#include "../so_long.h"

static void	move_sprites(t_entity *entity, enum e_direction direction)
{
	size_t	vars;
	size_t	frames;


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

static bool	is_inbetween_fields(double pos, int allowed_overlap)
{
	double	limit;
	
	limit = (double) allowed_overlap / 100.0;
	return (fmod(pos, 1.0) > limit && fmod(pos, 1.0) < 1.0 - limit);
}

static bool	is_valid_pos(char **map_2d, t_vector *new_pos)
{
	size_t	x1;
	size_t	x2;
	size_t	y1;
	size_t	y2;

	if (is_inbetween_fields(new_pos->y, P_W_OVERLAP_Y))
	{
		y1 = ceil(new_pos->y);
		y2 = floor(new_pos->y);
	}
	else
	{
		y1 = round(new_pos->y);
		y2 = y1;
	}
	
	if (is_inbetween_fields(new_pos->x, P_W_OVERLAP_X))
	{
		x1 = ceil(new_pos->x);
		x2 = floor(new_pos->x);
	}
	else
	{
		x1 = round(new_pos->x);
		x2 = x1;
	}

	if (map_2d[y1][x1] == WALL || map_2d[y1][x2] == WALL 
		|| map_2d[y2][x1] == WALL || map_2d[y2][x2] == WALL)
	{
		return (false);
	}
	return (true);
}

static t_vector	get_new_pos(int direction, t_vector old_pos)
{
	t_vector	new_pos;

	new_pos = old_pos;
	if (direction == UP)
		new_pos.y -= ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == DOWN)
		new_pos.y += ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == LEFT)
		new_pos.x -= ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	else if (direction == RIGHT)
		new_pos.x += ((double) PLAYER_SPEED / (double) TEXTURE_WIDTH);
	return (new_pos);
}

static enum e_player_variation	get_variation(int last_var, int direction)
{
	if (direction == LEFT)
		return (MOVING_LEFT);
	else if (direction == RIGHT)
		return (MOVING_RIGHT);
	else if (direction == UP || direction == DOWN)
	{
		if (last_var == MOVING_LEFT || last_var == STANDING_LEFT)
			return (MOVING_LEFT);
		if (last_var == MOVING_RIGHT || last_var == STANDING_RIGHT)
			return (MOVING_RIGHT);
	}
	else
	{
		if (last_var == MOVING_LEFT)
			return (STANDING_LEFT);
		else if (last_var == MOVING_RIGHT)
			return (STANDING_RIGHT);
	}
	return (last_var);
}

static void	update_variation(t_entity *player, int direction, enum e_player_variation last_var, int current_frame)
{
	enum e_player_variation	new_var;


	new_var = get_variation(last_var, direction);

	if (last_var != new_var)
	{
		player->sprites[last_var][current_frame]->enabled = false;
		player->sprites[new_var][current_frame]->enabled = true;
		player->current_variation = new_var;
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

void	move_player(mlx_t *mlx, t_entity *player, t_map *map)
{
	int			direction;
	t_vector	new_pos;

	direction = get_steering_key(mlx);
	update_variation(player, direction, player->current_variation, player->current_frame);
	new_pos = get_new_pos(direction, map->player_pos);
	if (!is_valid_pos(map->map_2d, &new_pos))
		return ;
	if (round(new_pos.y) != round(map->player_pos.y) || round(new_pos.x) != round(map->player_pos.x))
		map->steps += 1;
	map->player_pos = new_pos;
	move_sprites(player, direction);
}
