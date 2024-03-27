
#include "../so_long.h"
#include <stdio.h>

static void	update_animation(t_entity *entity, double mlx_delta_time)
{
	int	var;
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

static void	update_animations(t_game *game)
{
	update_animation(&game->entities.space,  game->mlx->delta_time);
	update_animation(&game->entities.wall,  game->mlx->delta_time);
	update_animation(&game->entities.player,  game->mlx->delta_time);
	update_animation(&game->entities.exit,  game->mlx->delta_time);
	update_animation(&game->entities.item,  game->mlx->delta_time);
	update_animation(&game->entities.enemy,  game->mlx->delta_time);
}

static void	move_sprites(t_entity *entity, enum e_direction direction, int distance)
{
	int	vars;
	int	frames;


	vars = 0;
	while(vars < entity->num_variations)
	{
		frames = 0;
		while(frames < entity->num_frames)
		{
			if (direction == UP)
				entity->sprites[vars][frames]->instances[0].y -= distance;
			else if (direction == LEFT)
				entity->sprites[vars][frames]->instances[0].x -= distance;
			else if (direction == DOWN)
				entity->sprites[vars][frames]->instances[0].y += distance;
			else if (direction == RIGHT)
				entity->sprites[vars][frames]->instances[0].x += distance;
			frames++;
		}
		vars++;
	}
}

static void	move_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_sprites(&game->entities.player, UP, 10);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_sprites(&game->entities.player, LEFT, 10);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_sprites(&game->entities.player, DOWN, 10);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_sprites(&game->entities.player, RIGHT, 10);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		; // TERMINATION
	}
}

void	my_loop_hook(void *param)
{
	t_game *game;

	game = (t_game *) param;
	move_player(game);
	update_animations(game);
}

