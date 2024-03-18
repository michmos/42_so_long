
#include "../so_long.h"

static int	has_e_c_p(t_map *map)
{
	int	y_pos;
	int	x_pos;

	if (map->player_pos[0] == -1 || map->exit_pos[0] == -1)
	{
		return (false);
	}
	find_item_pos(map->map_2d, ITEM, &y_pos, &x_pos);
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
	while (map->map_2d[i])
	{
		if ((int) ft_strlen(map->map_2d[i]) != map->width)
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
	while (map->map_2d[0][i])
	{
		if (map->map_2d[0][i] != WALL)
			return (false);
		i++;
	}
	j = 1;
	while (j < map->height - 1)
	{
		if (map->map_2d[j][0] != WALL || map->map_2d[j][map->width -1] != WALL)
			return (false);
		j++;
	}
	i = 0;
	while (map->map_2d[map->height - 1][i])
	{
		if (map->map_2d[map->height -1][i] != WALL)
			return (false);
		i++;
	}
	return (true);
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
	map->map_2d[player_pos[0]][player_pos[1]] = 'x';
	find_item_pos(map->map_2d, PLAYER, &temp[0], &temp[1]);
	if (temp[0] != -1)
		return (true);
	map->map_2d[exit_pos[0]][exit_pos[1]] = 'x';
	find_item_pos(map->map_2d, EXIT, &temp[0], &temp[1]);
	if (temp[0] != -1)
		return (true);
	map->map_2d[exit_pos[0]][exit_pos[1]] = EXIT;
	map->map_2d[player_pos[0]][player_pos[1]] = PLAYER;
	return (false);
}

static int	has_empty_lines(char *map)
{
	int		i;
	char	*temp;

	if (!map)
		return (-1);
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

int	error_check(t_map *map)
{
	if (has_empty_lines(map->map_1d))
		print_err("Map should not contain empty lines");
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
