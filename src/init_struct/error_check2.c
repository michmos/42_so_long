
#include "../so_long.h"

static bool	is_valid_space(char c)
{
	return (c == SPACE || c == ITEM || c == EXIT);
}

static void	cross_reachable_space(char **map, size_t y, size_t x)
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

bool	has_valid_path(t_map *map)
{
	bool	is_valid;

	cross_reachable_space(map->map_2d, map->player_pos.y, map->player_pos.x);
	is_valid = !has_entity(map->map_2d, EXIT) && !has_entity(map->map_2d, ITEM);
	return (is_valid);
}
