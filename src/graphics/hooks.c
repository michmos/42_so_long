
#include "../so_long.h"

static void	update_animation(t_entity *entity, double mlx_delta_time)
{
	int	i;
	int	old_frame;
	int	new_frame;

	entity->delta_time += mlx_delta_time;
	if (entity->delta_time * entity->fps < 1)
	{
		return;
	}
	entity->delta_time = 0;

	old_frame = entity->current_frame;
	new_frame = circular_increment(entity->current_frame, entity->num_frames - 1);
	i = 0;
	while (i < entity->num_variations)
	{
		entity->sprites[i][old_frame]->enabled = false;
		entity->sprites[i][new_frame]->enabled = true;
		i++;
	}
	entity->current_frame = new_frame;
}

static void	update_animations(t_game *game)
{
	update_animation(&game->entities.space,  game->mlx->delta_time);
	update_animation(&game->entities.wall,  game->mlx->delta_time);
	update_animation(&game->entities.player,  game->mlx->delta_time);
	update_animation(&game->entities.exit,  game->mlx->delta_time);
	update_animation(&game->entities.item,  game->mlx->delta_time);
	update_animation(&game->entities.enemy,  game->mlx->delta_time);
}

void	my_loop_hook(void *param)
{
	t_game *game;

	game = (t_game *) param;
	update_animations(game);
}

