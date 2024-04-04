
#include "../so_long.h"
#include <stdio.h>

static char	get_entity(char **map, t_vector *position)
{
	int	y;
	int	x;

	y = (int) round(position->y);
	x = (int) round(position->x);
	return (map[y][x]);
}

void	my_loop_hook(void *param)
{
	t_game *game;

	game = (t_game *) param;
	move_player(game->mlx, &game->entities.player, &game->map);
	if (get_entity(game->map.map_2d, &game->map.player_pos) == ITEM)
		disable_item(&game->entities.item, &game->map);
	else if (get_entity(game->map.map_2d, &game->map.player_pos) == ENEMY)
		;
	update_animations(game);
}

