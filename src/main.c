
#include "so_long.h"
#include "utils/utils.h"

// TODO: DOWNLOAD CORRECT MLX VERSION FROM GITHUB INSTEAD OF PUSHING IT
// TODO: UPDATE FREEING PROCEDURE
// TODO: Randomize loading of variations
// TODO: Check other settings
// TODO: Check for unvalid chars
// TODO: Valid map check with enemies
// TODO: Enemy should disappear when boat goes there
// TODO: protect all mlx calls
// TODO: when item is collected, map should be updated so that enemy can actually go there

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
