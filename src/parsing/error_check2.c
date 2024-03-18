
#include "../so_long.h"

int	all_items_collected(char **map)
{
	int	y;
	int	x;

	y = 0;
	if (!map || !*map)
		return (-1);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ITEM)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static void	cross_reachable_space(char **map, int y, int x)
{
	if (x == 0 || map[y][x] == '\0' || y == 0 || map[y] == NULL)
	{
		return ;
	}
	map[y][x] = 'x';
	if (map[y][x - 1] != WALL && map[y][x - 1] != 'x')
		cross_reachable_space(map, y, x - 1);
	if (map[y][x + 1] != WALL && map[y][x + 1] != 'x')
		cross_reachable_space(map, y, x + 1);
	if (map[y - 1][x] != WALL && map[y - 1][x] != 'x')
		cross_reachable_space(map, y - 1, x);
	if (map[y + 1][x] != WALL && map[y + 1][x] != 'x')
		cross_reachable_space(map, y + 1, x);
	return ;
}

int	has_valid_path(t_map *map)
{
	char **map_dup;

	map_dup = dup_map(map->map_data, map->height);
	if (!map_dup)
	{
		free_2d_array((void **)map->map_data); // TODO: check whether this is everything that needs to be freed?
		exit(EXIT_FAILURE);
	}
	cross_reachable_space(map_dup, map->player_pos[0], map->player_pos[1]);
	if (map_dup[map->exit_pos[0]][map->exit_pos[1]] == 'x' && all_items_collected(map_dup))
	{
		free_2d_array((void **) map_dup);
		return (true);
	}
	free_2d_array((void **) map_dup);
	return (false);
}