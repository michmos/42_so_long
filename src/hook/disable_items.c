
#include "../so_long.h"
#include <stdio.h>

static int	get_item_index(char **map, int pos_y, int pos_x)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = -1;
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] == ITEM)
			{
				count++;
				if (y == pos_y && x == pos_x)
					return (count);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

void	collect_item(t_entity *item, t_map *map, char **og_map)
{
	int	i;
	int	variation;
	int	instance;
	int	frame;

	i = get_item_index(og_map, round(map->player_pos.y), round(map->player_pos.x));
	instance = i / item->num_variations;
	variation = i % item->num_variations;
	frame = 0;
	while(frame < item->num_frames)
	{
		item->sprites[variation][frame]->instances[instance].enabled = false;
		frame++;
	}
	map->map_2d[(int) round(map->player_pos.y)][(int) round(map->player_pos.x)] = SPACE;
	map->num_items--;
}
