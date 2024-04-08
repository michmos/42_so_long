
#include "so_long.h"
#include "utils/utils.h"

// TODO: DOWNLOAD CORRECT MLX VERSION FROM GITHUB INSTEAD OF PUSHING IT
// TODO: check freeing procedure
// TODO: protect all mlx calls
// TODO: change flag texture a bit

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		err_exit("you need to provide the map path as an argument");
	}
	init_struct(&game, argv[1]);
	display_game(&game);
	mlx_loop_hook(game.mlx, my_loop_hook, (void *) &game);
	mlx_loop(game.mlx);
	end_game(&game, EXIT_FAILURE);
}
