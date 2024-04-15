
#include "../so_long.h"

static void	update_animation(t_entity *entity, double mlx_delta_time)
{
	size_t	var;
	size_t	old_frame;
	size_t	new_frame;

	entity->delta_time += mlx_delta_time;
	if (entity->delta_time * entity->fps < 1)
	{
		return;
	}
	entity->delta_time = 0;

	old_frame = entity->current_frame;
	new_frame = circular_increment(entity->current_frame, entity->num_frames - 1);
	var = 0;
	if (entity->type == PLAYER)
		var = entity->current_variation;
	while (var < entity->num_variations)
	{
		entity->sprites[var][old_frame]->enabled = false;
		entity->sprites[var][new_frame]->enabled = true;
		if (entity->type == PLAYER)
			break ;
		var++;
	}
	entity->current_frame = new_frame;
}

void	update_animations(t_entity_list *entities, double mlx_delta_time)
{
	update_animation(&entities->space,  mlx_delta_time);
	update_animation(&entities->wall,  mlx_delta_time);
	update_animation(&entities->player,  mlx_delta_time);
	update_animation(&entities->exit,  mlx_delta_time);
	update_animation(&entities->item,  mlx_delta_time);
	update_animation(&entities->enemy,  mlx_delta_time);
}
