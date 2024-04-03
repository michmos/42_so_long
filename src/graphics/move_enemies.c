
#include "../so_long.h"

static void	update_map(t_vector old_pos, t_vector new_pos, char **map)
{
	map[(int) old_pos.y][(int) old_pos.x] = SPACE;
	map[(int) old_pos.y][(int) old_pos.x] = SPACE;

	map[(int) new_pos.y][(int) new_pos.x] = ENEMY;
	map[(int) new_pos.y][(int) new_pos.x] = ENEMY;
}

static void	move_sprites(int i, t_entity *enemy, t_vector *new_pos)
{
	int	variation;
	int	instance;
	int	frame;

	instance = i / enemy->num_variations;
	variation = i % enemy->num_variations;
	frame = 0;
	while(frame < enemy->num_frames)
	{
		enemy->sprites[variation][frame]->instances[instance].y = new_pos->y * TEXTURE_WIDTH;
		enemy->sprites[variation][frame]->instances[instance].x = new_pos->x * TEXTURE_WIDTH;
		frame++;
	}
}

static bool	is_valid_pos(t_vector *pos, char **map)
{
	return (map[(int) pos->y][(int) pos->x] != WALL
	&& map[(int) pos->y][(int) pos->x] != ITEM
	&& map[(int) pos->y][(int) pos->x] != ENEMY
	&& map[(int) pos->y][(int) pos->x] != EXIT);
}

static t_vector	update_pos(t_vector *pos, char **map)
{
	int			change;
	t_vector	new_pos;
	int			tries;


	tries = 0;
	while(tries < 5)
	{
		new_pos.x = pos->x;
		new_pos.y = pos->y;
		change = random_value(-1, 1);
		if (random_value(0, 1))
			new_pos.y += change;
		else
			new_pos.x += change;
		if (is_valid_pos(&new_pos, map))
		{
			return (new_pos);
		}
		tries++;
	}
	return (*pos);
}

static t_vector	get_enemy_i_pos(char **map, int index)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ENEMY)
			{
				if (count == index)
					return ((t_vector){x, y});
				count++;
			}
			x++;
		}
		y++;
	}
	return ((t_vector){x, y});
}

void	move_enemies(mlx_t *mlx, t_entity *enemy, t_map *map)
{
	t_vector	pos;
	t_vector	new_pos;
	size_t		i;
	char		**new_map;
	static double  time;

	time += mlx->delta_time;
	if (time <= ENEMY_SPEED)
		return ;
	time = 0;
	new_map = dup_map(map->map_2d, map->height);
	if (!new_map)
		; // TODO: protect
	i = 0;
	while (i < map->num_enemies)
	{
		pos = get_enemy_i_pos(map->map_2d, i);
		new_pos = update_pos(&pos, map->map_2d);
		update_map(pos, new_pos, new_map);
		move_sprites(i, enemy, &new_pos);
		i++;
	}
	free_2d_array((void **)map->map_2d); // TODO: double check
	map->map_2d = new_map;
}
