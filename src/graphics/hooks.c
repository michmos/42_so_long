
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

static void	move_sprites(t_entity *entity, enum e_direction direction)
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
				entity->sprites[vars][frames]->instances[0].y -= PLAYER_SPEED;
			else if (direction == LEFT)
				entity->sprites[vars][frames]->instances[0].x -= PLAYER_SPEED;
			else if (direction == DOWN)
				entity->sprites[vars][frames]->instances[0].y += PLAYER_SPEED;
			else if (direction == RIGHT)
				entity->sprites[vars][frames]->instances[0].x += PLAYER_SPEED;
			frames++;
		}
		vars++;
	}
}

static void	update_variation(t_entity *player, enum e_player_motion motion)
{
	int	current_var;
	int	current_frame;

	current_var = player->current_variation;
	current_frame = player->current_frame;

	player->sprites[current_var][current_frame]->enabled = false;
	player->sprites[motion][current_frame]->enabled = true;
	player->current_variation = motion;
}

static void	move_player(mlx_t *mlx, t_entity *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		move_sprites(player, UP);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		update_variation(player, MOVING_LEFT);
		move_sprites(player, LEFT);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		move_sprites(player, DOWN);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		update_variation(player, MOVING_RIGHT);
		move_sprites(player, RIGHT);
	}
	else
	{
		if (player->current_variation == MOVING_LEFT)
		{
			update_variation(player, STANDING_LEFT);
		}
		else if (player->current_variation == MOVING_RIGHT)
		{
			update_variation(player, STANDING_RIGHT);
		}

	}
}

void	my_loop_hook(void *param)
{
	t_game *game;

	game = (t_game *) param;
	move_player(game->mlx, &game->entities.player);
	update_animations(game);
}

