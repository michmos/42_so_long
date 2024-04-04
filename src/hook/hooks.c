
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
	t_game 		*game;
	static bool	freeze;

	game = (t_game *) param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		end_game(game, EXIT_SUCCESS);
	}
	if (!freeze)
	{
		move_player(game->mlx, &game->entities.player, &game->map);
		move_enemies(game->mlx, &game->entities.enemy, &game->map);
		if (get_entity(game->map.map_2d, &game->map.player_pos) == ITEM)
		{
			disable_item(&game->entities.item, &game->map);
			game->map.num_items--;
		}
		else if (get_entity(game->map.map_2d, &game->map.player_pos) == ENEMY)
		{
			display_screen(game, get_rgba(0xFF, 0, 0, 70), FAILURE_MESSAGE);
			freeze = true;
		}
		else if (get_entity(game->map.map_2d, &game->map.player_pos) == EXIT
			&& game->map.num_items == 0)
		{
			display_screen(game, get_rgba(0, 0xFF, 0, 70), SUCCESS_MESSAGE);
			freeze = true;
		}
	}
	update_animations(game);
}

