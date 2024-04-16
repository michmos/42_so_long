
#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		err_exit("you need to provide the map path as an argument");
	}
	init_struct(&game, argv[1]);
	display_game(&game);
	if (mlx_loop_hook(game.mlx, my_loop_hook, (void *) &game) == false)
	{
		end_game(&game, EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	end_game(&game, EXIT_FAILURE);
}
