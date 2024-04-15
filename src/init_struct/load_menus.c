
#include "../so_long.h"
#include <stddef.h>

static mlx_image_t	*create_colored_img(mlx_t *mlx, size_t width, size_t height, int color)
{
	size_t		y;
	size_t		x;
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, height);
	if (!img)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel((img), x, y, color);
			x++;
		}
		y++;
	}
	return (img);
}

int	load_menus(mlx_t *mlx, t_menu_list *menus, t_map *map)
{
	size_t		width;
	size_t		height;

	width = TEXTURE_WIDTH * map->width;
	height = TEXTURE_WIDTH * map->height;
	menus->success.background = create_colored_img(mlx, width, height, get_rgba(0, 0xFF, 0, 70));
	if (!menus->success.background)
		return (-1);
	menus->failure.background = create_colored_img(mlx, width, height, get_rgba(0xFF, 0, 0, 70));
	if (!menus->failure.background)
		return (-1);
	return (0);
}
