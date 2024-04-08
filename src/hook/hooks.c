
#include "../so_long.h"
#include <stdio.h>

void	my_loop_hook(void *param)
{
	t_game 		*game;
	static bool	freeze;
	static int	last_count;

	game = (t_game *) param;
	if ((freeze && mlx_is_key_down(game->mlx, MLX_KEY_SPACE))) // TODO: restart functionality
	{
		reset_game(game);
		freeze = false;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		end_game(game, EXIT_SUCCESS);
	}
	if (!freeze)
	{
		if (!game->map.steps_img || last_count != game->map.steps)
		{
			print_step_count(game->mlx, &game->map.steps_img, game->map.steps);
			last_count = game->map.steps;
		}
		move_player(game->mlx, &game->entities.player, &game->map);
		if (get_entity(game->map.map_2d, &game->map.player_pos) == ITEM)
		{
			collect_item(&game->entities.item, &game->map, game->backup_map.map_2d);
		}
		else if (get_entity(game->map.map_2d, &game->map.player_pos) == ENEMY)
		{
			enable_menu(&game->menus.failure);
			freeze = true;
		}
		else if (get_entity(game->map.map_2d, &game->map.player_pos) == EXIT
			&& game->map.num_items == 0)
		{
			enable_menu(&game->menus.success);
			freeze = true;
		}
	}
	update_animations(game);
}

