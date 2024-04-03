
#include "../so_long.h"

static int	fill_window(t_game *game, int color)
{
	int	y;
	int	x;
	int	width;
	int	height;
	mlx_image_t *background;


	width = TEXTURE_WIDTH * game->map.width;
	height = TEXTURE_WIDTH * game->map.height;
	background = mlx_new_image(game->mlx, width, height);
	if (!background)
		return (-1);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(background, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, background, 0, 0);
	return (0);
}

static int	print_central_message(t_game *game, char *message)
{
	size_t	message_width;
	int		start_x;
	int		start_y;

	start_y = game->map.height * TEXTURE_WIDTH / 2;
	message_width = ft_strlen(message) * CHAR_PIXEL_SIZE;
	start_x = game->map.width * TEXTURE_WIDTH / 2 - message_width / 2;
	if (start_x < 0)
		start_x = 0;
	if (!mlx_put_string(game->mlx, message, start_x, start_y))
		return (-1);
	return (0);
}


void	display_screen(t_game *game, int color, char *message)
{
	if (fill_window(game, color) == -1)
		;// TODO: protect
	if (message)
	{
		if (print_central_message(game, message) == -1)
			;// TODO: protect
	}
}
