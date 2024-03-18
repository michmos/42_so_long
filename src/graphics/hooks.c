
#include "../so_long.h"

static void	update_animation(t_entity *entity, double mlx_delta_time)
{
	int	i;

	entity->delta_time += mlx_delta_time;
	if (entity->delta_time * entity->fps < 1)
	{
		return;
	}
	entity->delta_time = 0;
	i = 0;
	while (i < entity->num_variations)
	{
		entity->sprites[i][entity->current_frame]->enabled = false;
		if (entity->current_frame == entity->num_frames - 1)
		{
			entity->current_frame = 0;
		}
		else
		{
			entity->current_frame++;
		}
		entity->sprites[i][entity->current_frame]->enabled = true;
		i++;
	}
}

void	my_loop_hook(void *param)
{
	t_game *game;

	game = (t_game *) param;
	update_animation(&game->entities.space,  game->mlx->delta_time);
}

