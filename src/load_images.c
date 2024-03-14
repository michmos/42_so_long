
#include "so_long.h"

typedef struct s_textures
{
	mlx_texture_t *space;
	mlx_texture_t *wall;
	mlx_texture_t *player;
	mlx_texture_t *exit;
	mlx_texture_t *items;
	mlx_texture_t *enemies;
} t_textures;


static int	load_textures(t_textures *textures)
{
	textures->space = mlx_load_png(SPACE_TEXTURE);
	if (!textures->space)
		return (-1);
	// textures->wall = mlx_load_png(WALL_TEXTURE);
	// if (!textures->wall)
	// 	return (-1);
	// textures->player = mlx_load_png(PLAYER_TEXTURE);
	// if (!textures->player)
	// 	return (-1);
	// textures->exit = mlx_load_png(EXIT_TEXTURE);
	// if (!textures->exit)
	// 	return (-1);
	// textures->items = mlx_load_png(ITEM_TEXTURE);
	// if (!textures->items)
	// 	return (-1);
	// textures->enemies = mlx_load_png(ENEMY_TEXTURE);
	// if (!textures->enemies)
	// 	return (-1);
	return (0);
}

static int	textures_to_img(mlx_t *mlx, t_textures *textures, t_imgs *imgs)
{
	imgs->space = mlx_texture_to_image(mlx, textures->space);
	if (!imgs->space)
		return (-1);
	// imgs->wall = mlx_texture_to_image(mlx, textures->wall);
	// if (!imgs->wall)
	// 	return (-1);
	// imgs->player = mlx_texture_to_image(mlx, textures->player);
	// if (!imgs->player)
	// 	return (-1);
	// imgs->exit = mlx_texture_to_image(mlx, textures->exit);
	// if (!imgs->exit)
	// 	return (-1);
	// imgs->items = mlx_texture_to_image(mlx, textures->items);
	// if (!imgs->items)
	// 	return (-1);
	// imgs->enemies = mlx_texture_to_image(mlx, textures->enemies);
	// if (!imgs->enemies)
	// 	return (-1);
	return (0);
}

int load_images(mlx_t *mlx, t_imgs *imgs)
{
	t_textures textures;
	
	if (load_textures(&textures) == -1)
	{
		return (-1);
	}
	if (textures_to_img(mlx, &textures, imgs) == -1)
	{
		return (-1);
	}
	return (0);
}

