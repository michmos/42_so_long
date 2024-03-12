
#include "so_long.h"
#define	BUFFER_SIZE 128

void	err_exit(const char *str)
{
	if (str)
		print_err(str);
	exit(EXIT_FAILURE);
}

void	print_err(const char *str)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, str, ft_strlen(str));
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
