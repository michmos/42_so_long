
#include "so_long.h"

void	end_game(t_game *game, int exit_code) // TODO: anything else missing
{
	free(game->map.map_1d);
	free_2d_array((void **) game->map.map_2d);
	free_2d_array((void **) game->entities.space.sprites);
	free_2d_array((void **) game->entities.wall.sprites);
	free_2d_array((void **) game->entities.player.sprites);
	free_2d_array((void **) game->entities.exit.sprites);
	free_2d_array((void **) game->entities.item.sprites);
	free_2d_array((void **) game->entities.enemy.sprites);
	mlx_terminate(game->mlx);
	exit(exit_code);
}
