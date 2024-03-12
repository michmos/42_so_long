
#include "so_long.h"
#define	BUFFER_SIZE 128

void	err_exit(const char *err_message)
{
	if (err_message)
		print_err(err_message);
	exit(EXIT_FAILURE);
}

void	print_err(const char *err_message)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	write(STDERR_FILENO, "\n", 1);
}

void	find_item_pos(char **map, char item, int *y_pos, int *x_pos)
{
	int y;
	int	x;

	if (!map || !*map)
		return ;
	y = 0;
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] == item)
			{
				*x_pos = x;
				*y_pos = y;
				return ;
			}
			x++;
		}
		y++;
	}
	*x_pos = -1;
	*y_pos = -1;
}

void	free_2d_array(char **arr)
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

char	**copy_map(char **map, size_t	size)
{
	int 	y;
	char	**dup_map;

	y = 0;
	if (!map || !*map)
		return (NULL);
	dup_map = malloc((size + 1) * sizeof(char *));
	if (!dup_map)
		return (NULL);
	while (map[y])
	{
		dup_map[y] = ft_strdup(map[y]);
		if (!dup_map[y])
		{
			free_2d_array(dup_map);
			return (NULL);
		}
		y++;
	}
	dup_map[size] = NULL;
	return (dup_map);
}
