
#include "../so_long.h"
#include <stdlib.h>

static int	display_all_frames(mlx_t *mlx, mlx_image_t **sprite, int x, int y)
{
	int frame;

	frame = 0;
	while (sprite[frame])
	{
		if (mlx_image_to_window(mlx, sprite[frame], TEXTURE_WIDTH * x, TEXTURE_WIDTH * y) == -1)
			return (-1);
		sprite[frame]->enabled = false;
		frame++;
	}
	return (0);
}

static int	display_sprite(mlx_t *mlx, t_entity *entity, int x, int y)
{
	entity->current_variation = circular_increment(entity->current_variation, entity->num_variations - 1);
	if (entity->type == PLAYER)
	{
		while (entity->sprites[entity->current_variation])
		{
			if (display_all_frames(mlx, entity->sprites[entity->current_variation], x, y) == -1)
				return (-1);
			entity->current_variation++;
		}
		entity->sprites[0][0]->enabled = true;
		entity->current_variation = 0;
	}
	else
	{
		if (display_all_frames(mlx, entity->sprites[entity->current_variation], x, y) == -1)
			return (-1);
		entity->sprites[entity->current_variation][0]->enabled = true;
	}
	return (0);
}

static int	display_background(t_game *game) // TODO: delete this
{
	int	y;
	int	x;
	int	width;
	int	height;
	mlx_image_t *background;


	width = TEXTURE_WIDTH * game->map.width;
	height = TEXTURE_WIDTH * game->map.height;
	background = mlx_new_image(game->mlx, width, height);
	if (!background)
		return (-1);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(background, x, y, get_rgba(50, 75, 190, 0xFF));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, background, 0, 0);
	return (0);
}

static int	display_all_instances(mlx_t *mlx, t_entity *entity, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == entity->type)
			{
				if (display_sprite(mlx, entity, x, y) == -1)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	display_entities(mlx_t *mlx, t_entity_list *entities, char **map)
{
	if (display_all_instances(mlx, &entities->space, map) == -1)
		return (-1);
	if (display_all_instances(mlx, &entities->wall, map) == -1)
		return (-1);
	if (display_all_instances(mlx, &entities->exit, map) == -1)
		return (-1);
	if (display_all_instances(mlx, &entities->item, map) == -1)
		return (-1);
	if (display_all_instances(mlx, &entities->enemy, map) == -1)
		return (-1);
	if (display_all_instances(mlx, &entities->player, map) == -1)
		return (-1);
	return (0);
}

int	display_map(t_game *game)
{
	display_background(game);
	if (display_entities(game->mlx, &game->entities, game->map.map_2d) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	if (display_menus(game->mlx, &game->menus, &game->map) == -1)
	{
		end_game(game, EXIT_FAILURE);
	}
	return (0);
}

