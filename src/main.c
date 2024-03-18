
#include "so_long.h"

// TODO: DOWNLOAD MLX FROM GITHUB INSTEAD OF PUSHING IT
// TODO: EMPTY LINES IN THE MIDDLE ARE UNVALID
// TODO: Check other settings
//
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
		free_2d_array((void **) game.map.map_2d);
		exit(EXIT_FAILURE);
	}
	// game.mlx = mlx_init(TEXTURE_WIDTH * game.map.width, TEXTURE_WIDTH * game.map.height, "so_long", true);
	// if (!game.mlx)
	// {
	// 	free_2d_array((void **) game.map.map_2d);
	// 	exit(EXIT_FAILURE);
	// }
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	// if (load_images(game.mlx, &imgs) == -1)
	// {
	// 	free_2d_array((void **) game.map.map_2d);
	// 	exit(EXIT_FAILURE);
	// }
	// if (init_entities(game.mlx, &game.entities, &imgs) == -1)
	// {
	// 	free_entities(game.mlx, &game.entities);
	// 	free_2d_array((void **) game.map.map_2d);
	// 	exit(EXIT_FAILURE);
	// }
	// mlx_loop_hook(game.mlx, my_loop_hook, (void *) &game);
	// mlx_loop(game.mlx);
	// mlx_terminate(game.mlx);
	return (0);
}
