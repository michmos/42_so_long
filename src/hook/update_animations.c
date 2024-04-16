
#include "../so_long.h"

static bool	update_required(double *accumulated_time, double mlx_delta_time, int fps)
{
	*accumulated_time += mlx_delta_time;
	if (*accumulated_time * fps < 1)
	{
		return (false);
	}
	*accumulated_time = 0;
	return (true);

}

static void	update_animation(t_entity *entity, double mlx_delta_time)
{
	size_t	var;
	size_t	old_frame;
	size_t	new_frame;

	if (!update_required(&entity->delta_time, mlx_delta_time, entity->fps))
		return ;
	old_frame = entity->current_frame;
	new_frame = circular_increment(entity->current_frame, entity->num_frames - 1);
	if (entity->type == PLAYER)
	{
		var = entity->current_variation;
		entity->sprites[var][old_frame]->enabled = false;
		entity->sprites[var][new_frame]->enabled = true;
	}
	else
	{
		var = 0;
		while (var < entity->num_variations)
		{
			entity->sprites[var][old_frame]->enabled = false;
			entity->sprites[var][new_frame]->enabled = true;
			var++;
		}
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
