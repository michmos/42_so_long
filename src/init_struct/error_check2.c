
#include "../so_long.h"

static int	is_valid_space(char c)
{
	return (c != WALL && c != 'x' && c != ENEMY);  // TODO: update for mandatory part
}

static void	cross_reachable_space(char **map, int y, int x)
{
	if (x == 0 || map[y][x] == '\0' || y == 0 || map[y] == NULL)
	{
		return ;
	}
	map[y][x] = 'x';
	if (is_valid_space(map[y][x - 1]))
		cross_reachable_space(map, y, x - 1);
	if (is_valid_space(map[y][x + 1]))
		cross_reachable_space(map, y, x + 1);
	if (is_valid_space(map[y - 1][x]))
		cross_reachable_space(map, y - 1, x);
	if (is_valid_space(map[y + 1][x]))
		cross_reachable_space(map, y + 1, x);
	return ;
}

int	has_valid_path(t_map *map)
{
	char **map_dup;

	map_dup = dup_map(map->map_2d, map->height);
	if (!map_dup)
	{
		free_2d_array((void **)map->map_2d); // TODO: wrongly protected
		
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
