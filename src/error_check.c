
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

static int	has_valid_path(t_map *map)
{
	char **map_dup;

	map_dup = dup_map(map->map, map->height);
	cross_reachable_space(map_dup, map->player_pos[0], map->player_pos[1]);
	if (map_dup[map->exit_pos[0]][map->exit_pos[1]] == 'x')
	{
		free_2d_array(map_dup);
		return (true);
	}
	free_2d_array(map_dup);
	return (false);
}

static int	has_duplicates(t_map *map)
{
	int		exit_pos[2];
	int		player_pos[2];
	int		temp[2];

	exit_pos[0] = map->exit_pos[0];
	exit_pos[1] = map->exit_pos[1];
	player_pos[0] = map->player_pos[0];
	player_pos[1] = map->player_pos[1];
	map->map[player_pos[0]][player_pos[1]] = 'x';
	find_item_pos(map->map, PLAYER, &temp[0], &temp[1]);
	if (temp[0] != -1)
		return (true);
	map->map[exit_pos[0]][exit_pos[1]] = 'x';
	find_item_pos(map->map, EXIT, &temp[0], &temp[1]);
	if (temp[0] != -1)
		return (true);
	map->map[exit_pos[0]][exit_pos[1]] = EXIT;
	map->map[player_pos[0]][player_pos[1]] = PLAYER;
	return (false);
}

int	error_check(t_map *map)
{
	if (!has_e_c_p(map))
		print_err("Map must contain the characters E, C and P");
	else if (has_duplicates(map))
		print_err("Map: There can only be one start and one exit");
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
