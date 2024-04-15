
#include "../so_long.h"
#include <stddef.h>


static bool	is_closed(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map->map_2d[0][x])
	{
		if (map->map_2d[0][x] != WALL)
			return (false);
		x++;
	}
	y = 1;
	while (y < map->height - 1)
	{
		if (map->map_2d[y][0] != WALL || map->map_2d[y][map->width -1] != WALL)
			return (false);
		y++;
	}
	x = 0;
	while (map->map_2d[map->height - 1][x])
	{
		if (map->map_2d[map->height -1][x] != WALL)
			return (false);
		x++;
	}
	return (true);
}

static bool	is_rectangular(t_map *map)
{
	size_t	i;

	i = 0;
	while (map->map_2d[i])
	{
		if (ft_strlen(map->map_2d[i]) != map->width)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	has_duplicates(t_map *map)
{
	bool	player;
	bool	exit;
	size_t	i;

	i = 0;
	player = false;
	exit = false;
	while (map->map_1d[i])
	{
		if (map->map_1d[i] == PLAYER && player == true)
			return (true);
		else if (map->map_1d[i] == EXIT && exit == true)
			return (true);
		else if (map->map_1d[i] == PLAYER)
			player = true;
		else if (map->map_1d[i] == EXIT)
			player = true;
		i++;
	}
	return (false);
}

static bool	has_e_c_p(t_map *map)
{
	if (map->player_pos.y == -1 || map->exit_pos.y == -1)
	{
		return (false);
	}
	if (!has_entity(map->map_2d, ITEM))
	{
		return (false);
	}
	return (true);
}

static bool	has_inner_empty_lines(char *map)
{
	size_t	i;
	char	*temp;

	if (!map)
		return (-1);
	i = 0;
	while(map[i] && map[i] == '\n')
	{
		i++;
	}
	temp = ft_strnstr(&map[i], "\n\n", ft_strlen(&map[i]));
	if (!temp)
	{
		return (false);
	}
	i = 0;
	while (temp[i] && temp[i] == '\n')
	{
		i++;
	}
	if (temp[i] == '\0')
	{
		return (false);
	}
	return (true);
}

static bool	has_unvalid_chars(char *map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (!ft_strchr("01PECM\n", map[i]))
			return (true);
		i++;
	}
	return (false);
}

int	error_check(t_map *map)
{
	if (has_unvalid_chars(map->map_1d))
		print_err("Map contains unvalid characters");
	else if (has_inner_empty_lines(map->map_1d))
		print_err("Map should not contain inner empty lines");
	else if (!has_e_c_p(map))
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
