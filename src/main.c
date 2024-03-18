
#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game			game;
	t_img_list		imgs;

	if (argc != 2)
	{
		err_exit("unvalid arguments");
	}
	init_map(&game.map, argv[1]);
	if (error_check(&game.map))
	{
		free_2d_array((void **) game.map.map_data);
		exit(EXIT_FAILURE);
	}
	game.mlx = mlx_init(TEXTURE_WIDTH * game.map.width, TEXTURE_WIDTH * game.map.height, "so_long", true);
	if (!game.mlx)
	{
		free_2d_array((void **) game.map.map_data);
		exit(EXIT_FAILURE);
	}
	if (load_images(game.mlx, &imgs) == -1)
	{
		free_2d_array((void **) game.map.map_data);
		exit(EXIT_FAILURE);
	}
	if (init_entities(game.mlx, &game.entities, &imgs) == -1)
	{
		free_entities(game.mlx, &game.entities);
		free_2d_array((void **) game.map.map_data);
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(game.mlx, my_loop_hook, (void *) &game);
	mlx_loop(game.mlx);
	return (0);
}
