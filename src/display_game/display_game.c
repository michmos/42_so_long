
#include "../so_long.h"

int	display_game(t_game *game)
{
	if (display_entities(game->mlx, &game->entities, game->map.map_2d) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (display_menus(game->mlx, &game->menus, &game->map) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	return (0);
}

