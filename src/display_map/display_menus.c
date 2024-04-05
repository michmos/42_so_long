
#include "../so_long.h"

void	disable_menu(t_menu *menu)
{
	menu->background->enabled = false;
	menu->message->enabled = false;
}

void	enable_menu(t_menu *menu)
{
	menu->background->enabled = true;
	menu->message->enabled = true;
}

static mlx_image_t	*display_central_message(mlx_t *mlx, t_map *map, char *message)
{
	size_t		message_width;
	int			start_x;
	int			start_y;
	mlx_image_t *img;

	message_width = ft_strlen(message) * CHAR_PIXEL_SIZE;
	start_y = map->height * TEXTURE_WIDTH / 2;
	start_x = map->width * TEXTURE_WIDTH / 2 - message_width / 2;
	if (start_x < 0)
	{
		start_x = 0;
	}
	img = mlx_put_string(mlx, message, start_x, start_y);
	return (img);
}

int	display_menus(mlx_t *mlx, t_menu_list *menus, t_map *map)
{
	if (mlx_image_to_window(mlx, menus->success.background, 0, 0) == -1)
		return (-1);
	if (mlx_image_to_window(mlx, menus->failure.background, 0, 0) == -1)
		return (-1);
	menus->success.message = display_central_message(mlx, map, SUCCESS_MESSAGE);
	if (!menus->success.message)
		return (-1);
	menus->failure.message = display_central_message(mlx, map, FAILURE_MESSAGE);
	if (!menus->failure.message)
		return (-1);
	disable_menu(&menus->success);
	disable_menu(&menus->failure);
	return (0);
}
