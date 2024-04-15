
#include "so_long.h"

void	end_game(t_game *game, int exit_code) // TODO: anything else missing
{
	free(game->map.map_1d);
	free_2d_array((void **) game->map.map_2d);
	free(game->backup_map.map_1d);
	free_2d_array((void **) game->backup_map.map_2d);

	if (game->mlx)
		mlx_terminate(game->mlx);
	free_2d_array((void **) game->entities.space.sprites);
	free_2d_array((void **) game->entities.wall.sprites);
	free_2d_array((void **) game->entities.player.sprites);
	free_2d_array((void **) game->entities.exit.sprites);
	free_2d_array((void **) game->entities.item.sprites);
	free_2d_array((void **) game->entities.enemy.sprites);
	exit(exit_code);
}
