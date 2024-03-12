
#include "so_long.h"
#include <stdbool.h>

static int	has_e_c_p(t_map *map)
{
	int	y_pos;
	int	x_pos;

	if (map->player_pos[0] == -1 || map->exit_pos[0] == -1)
	{
		return (false);
	}
	find_item_pos(map->map, ITEM, &y_pos, &x_pos);
	if (y_pos == -1)
	{
		return (false);
	}
	return (true);
}

static int	is_rectangular(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if ((int) ft_strlen(map->map[i]) != map->width)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static int	is_closed(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[0][i])
	{
		if (map->map[0][i] != WALL)
			return (false);
		i++;
	}
	j = 1;
	while (j < map->height - 1)
	{
		if (map->map[j][0] != WALL || map->map[j][map->width -1] != WALL)
			return (false);
		j++;
	}
	i = 0;
	while (map->map[map->height - 1][i])
	{
		if (map->map[map->height -1][i] != WALL)
			return (false);
		i++;
	}
	return (true);
}

static void	cross_reachable_space(int x, int y, t_map *map)
{
	if (x == 0 || x == map->width || y == 0 || y == map->height)
		return ;
	map->map[y][x] = 'x';
	if (map->map[y][x - 1] != WALL && map->map[y][x - 1] != 'x')
		cross_reachable_space(x - 1, y, map);
	if (map->map[y][x + 1] != WALL && map->map[y][x + 1] != 'x')
		cross_reachable_space(x + 1, y, map);
	if (map->map[y - 1][x] != WALL && map->map[y - 1][x] != 'x')
		cross_reachable_space(x, y - 1, map);
	if (map->map[y + 1][x] != WALL && map->map[y + 1][x] != 'x')
		cross_reachable_space(x, y + 1, map);
	return ;
}

static int	has_valid_path(t_map *map)
{
	// cross_reachable_space(map->player_pos[1], map->player_pos[0], map);
	cross_reachable_space(1, 3, map);
	// if (map->map[map->exit_pos[1]][map->exit_pos[0]] == 'x')
	// 	return (true);
	return (false);
}

int	error_check(t_map *map)
{
	if (!has_e_c_p(map))
		print_err("Map must contain the characters E, C and P");
	// else if (has_duplicates(map))
	// 	print_err("Map: There can only be one start and one exit");
	else if (!is_rectangular(map))
		print_err("Map must be rectangular");
	else if (!is_closed(map))
		print_err("Map must be closed");
	else if (!has_valid_path(map))
		print_err("Map: There must be a valid path from start to exit");
	else
		return (0);
	return (1);
}
