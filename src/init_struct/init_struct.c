
#include "../so_long.h"

static void	init_pointers(t_game *game, int value)
{
	ft_memset(&game->map, value, sizeof(t_map));
	ft_memset(&game->backup_map, value, sizeof(t_map));
	ft_memset(&game->entities.space, value, sizeof(t_entity));
	ft_memset(&game->entities.wall, value, sizeof(t_entity));
	ft_memset(&game->entities.player, value, sizeof(t_entity));
	ft_memset(&game->entities.exit, value, sizeof(t_entity));
	ft_memset(&game->entities.item, value, sizeof(t_entity));
	ft_memset(&game->entities.enemy, value, sizeof(t_entity));
}

void	init_struct(t_game *game, char *map_path)
{
	t_img_list	imgs;

	init_pointers(game, 0);
	init_map(&game->map, map_path);
	if (copy_t_map(&game->backup_map, &game->map) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (error_check(&game->map))
	{
		end_game(game, EXIT_FAILURE);
	}
	game->mlx = mlx_init(game->map.width * TEXTURE_WIDTH, game->map.height * TEXTURE_WIDTH, "so_long", true);
	if (!game->mlx)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (load_images(game->mlx, &imgs) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (init_entities(game->mlx, &game->entities, &imgs) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (load_menus(game->mlx, &game->menus, &game->map) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
}
