
#include "so_long.h"

int	copy_t_map(t_map *map_dest, t_map *map_src)
{
	if (!map_dest | !map_src)
	{
		return (-1);
	}
	*map_dest = *map_src;
	map_dest->map_1d = ft_strdup(map_src->map_1d);
	if (!map_dest->map_1d)
	{
		return (-1);
	}
	map_dest->map_2d = dup_map(map_src->map_2d, map_src->height);
	if (!map_dest->map_2d)
	{
		return (-1);
	}
	return (0);
}

char	get_entity(char **map, t_vector *position)
{
	size_t	y;
	size_t	x;

	y = (int) round(position->y);
	x = (int) round(position->x);
	return (map[y][x]);
}
