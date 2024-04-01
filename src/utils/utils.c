
#include "utils.h"

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

void	find_item_pos(char **map, char item, double *y_pos, double *x_pos)
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
				*x_pos = x + 0.5;
				*y_pos = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
	*x_pos = -1;
	*y_pos = -1;
}

char	**dup_map(char **map, size_t	size)
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
			free_2d_array((void **) dup_map);
			return (NULL);
		}
		y++;
	}
	dup_map[size] = NULL;
	return (dup_map);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel(mlx_image_t *img, int y, int x)
{
	int		pixel_index;
	uint8_t	*pixel_data;
	int		rgba;

	pixel_index = img->width * y + x;
	pixel_data = &img->pixels[pixel_index * 4];
	rgba = get_rgba(pixel_data[0], pixel_data[1], pixel_data[2], pixel_data[3]);
	return (rgba);
}

