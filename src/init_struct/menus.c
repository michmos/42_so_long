
#include "../so_long.h"

static mlx_image_t	*get_img(mlx_t *mlx, int width, int height, int color)
{
	int			y;
	int			x;
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

static mlx_image_t	*print_central_message(t_game *game, char *message)
{
	size_t		message_width;
	int			start_x;
	int			start_y;
	mlx_image_t *img;

	start_y = game->map.height * TEXTURE_WIDTH / 2;
	message_width = ft_strlen(message) * CHAR_PIXEL_SIZE;
	start_x = game->map.width * TEXTURE_WIDTH / 2 - message_width / 2;
	if (start_x < 0)
		start_x = 0;
	img = mlx_put_string(game->mlx, message, start_x, start_y);
	return (img);
}


void	display_screen(t_game *game, int color, char *message)
{
	int	width;
	int	height;

	width = TEXTURE_WIDTH * game->map.width;
	height = TEXTURE_WIDTH * game->map.height;
	game->end_imgs.background = get_img(game->mlx, width, height, color);
	if (!game->end_imgs.background)
		;// TODO: protect
	mlx_image_to_window(game->mlx, game->end_imgs.background, 0, 0);
	if (message)
	{
		game->end_imgs.message = print_central_message(game, message);
		if (!game->end_imgs.message)
			;// TODO: protect
	}
}
