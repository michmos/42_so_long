
#include "utils.h"

int has_entity(char **map, int entity)
{
	double	location[2];

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

int	count(char *src, char value)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == value)
			count++;
		i++;
	}
	return (count);
}

int random_value(int min, int max)
{
	int	value;
	int	range;

	range = max - min;
	value = rand() % (range + 1);
	return (value + min);
}

void	free_2d_array(void **arr)
{
	int y;

	y = 0;
	if (!arr)
		return ;
	if (!arr[0])
	{
		free(arr);
		return ;
	}
	while (arr[y])
	{
		free(arr[y]);
		y++;
	}
	free(arr);
}
