
#include "../so_long.h"

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

	map_dup = dup_map(map->map_2d, map->height);
	if (!map_dup)
	{
		free_2d_array((void **)map->map_2d); // TODO: check whether this is everything that needs to be freed?
		exit(EXIT_FAILURE);
	}
	cross_reachable_space(map_dup, map->player_pos.y, map->player_pos.x);
	if (!has_entity(map_dup, EXIT) && !has_entity(map_dup, ITEM))
	{
		free_2d_array((void **) map_dup);
		return (true);
	}
	free_2d_array((void **) map_dup);
	return (false);
}
