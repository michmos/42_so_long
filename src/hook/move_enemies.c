
#include "../so_long.h"

static void	update_map(t_vector old_pos, t_vector new_pos, char **map)
{
	map[(int) old_pos.y][(int) old_pos.x] = SPACE;
	map[(int) new_pos.y][(int) new_pos.x] = ENEMY;
}

void	move_enemy_i_sprites(int i, t_entity *enemy, t_vector *new_pos)
{
	size_t	variation;
	size_t	instance;
	size_t	frame;

	variation = i % enemy->num_variations;
	instance = i / enemy->num_variations;
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

static t_vector	get_new_pos(t_vector pos, char **map)
{
	int			change;
	t_vector	new_pos;
	int			tries;


	tries = 0;
	while(tries < 5)
	{
		new_pos = pos;
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
	return (pos);
}

t_vector	get_next_enemy(char **map, t_vector starting_pos)
{
	size_t y;
	size_t x;

	y = starting_pos.y;
	x = starting_pos.x + 1;
	while(map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == ENEMY)
				return ((t_vector) {x, y});
			x++;
		}
		x = 0;
		y++;
	}
	return ((t_vector) {-1, -1});
}

static t_vector *get_enemy_positions(char **map, size_t	num_enemies)
{
	t_vector	*positions;
	size_t		i;

	positions = malloc(num_enemies * sizeof(t_vector));
	if (!positions)
		return (NULL);
	i = 0;
	while (i < num_enemies)
	{
		if (i == 0)
			positions[i] = get_next_enemy(map, (t_vector) {0, 0});
		else
			positions[i] = get_next_enemy(map, positions[i - 1]);
		i++;
	}
	return (positions);
}

int	move_enemies(double delta_time, t_entity *enemy, t_map *map)
{
	t_vector	*all_pos;
	t_vector	new_pos;
	size_t		i;
	static double  time;

	time += delta_time;
	if (time <= ENEMY_SPEED)
		return (0);
	time = 0;

	all_pos = get_enemy_positions(map->map_2d, map->num_enemies);
	if (!all_pos)
		return (-1);
	i = 0;
	while (i < map->num_enemies)
	{
		new_pos = get_new_pos(all_pos[i], map->map_2d);
		update_map(all_pos[i], new_pos, map->map_2d);
		move_enemy_i_sprites(i, enemy, &new_pos);
		i++;
	}
	free(all_pos);
	return (0);
}

