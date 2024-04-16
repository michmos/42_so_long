
#include "../so_long.h"
#include <stdlib.h>

static bool	is_new_count(mlx_image_t *img, size_t new_count)
{
	static size_t	last_count;

	if (!img)
	{
		return (true);
	}
	else if (last_count != new_count)
	{
		last_count = new_count;
		return (true);
	}
	else
	{
		return (false);
	}
}

void	my_loop_hook(void *param)
{
	t_game 		*game;
	static bool	freeze;

	game = (t_game *) param;
	if ((freeze && mlx_is_key_down(game->mlx, MLX_KEY_SPACE)))
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
		if (is_new_count(game->map.steps_img, game->map.steps))
		{
			print_step_count(game->mlx, &game->map.steps_img, game->map.steps);
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
		if (move_enemies(game->mlx->delta_time, &game->entities.enemy, &game->map) == -1)
		{
			end_game(game, EXIT_FAILURE);
		}
	}
	update_animations(&game->entities, game->mlx->delta_time);
}

