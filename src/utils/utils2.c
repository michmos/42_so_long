
#include "utils.h"

int has_entity(char **map, int entity)
{
	int	location[2];

	find_item_pos(map, entity, &location[0], &location[1]);
	if (location[0] == -1)
	{
		return (false);
	}
	return (true);
}

int	circular_increment(int index, int max)
{
	if (index < max)
	{
		return (index + 1);
	}
	else
	{
		return (0);
	}
}
