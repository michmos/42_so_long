
#include "../so_long.h"

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
			display_all_frames(mlx, entity->sprites[entity->current_variation], x, y);
			entity->current_variation++;
		}
		entity->sprites[0][0]->enabled = true;
		entity->current_variation = 0;
	}
	else
	{
		display_all_frames(mlx, entity->sprites[entity->current_variation], x, y);
		entity->sprites[entity->current_variation][0]->enabled = true;
	}
	return (0);
}

static int	display_background(t_game *game)
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

int	display_map(t_game *game)
{
	int	y;
	int	x;

	display_background(game);
	y = 0;
	while (game->map.map_2d[y])
	{
		x = 0;
		while (game->map.map_2d[y][x])
		{
			if (game->map.map_2d[y][x] == SPACE)
				display_sprite(game->mlx, &game->entities.space, x, y);
			if (game->map.map_2d[y][x] == WALL)
				display_sprite(game->mlx, &game->entities.wall, x, y);
			else if (game->map.map_2d[y][x] == PLAYER)
				display_sprite(game->mlx, &game->entities.player, x, y);
			else if (game->map.map_2d[y][x] == EXIT)
				display_sprite(game->mlx, &game->entities.exit, x, y);
			else if (game->map.map_2d[y][x] == ITEM)
				display_sprite(game->mlx, &game->entities.item, x, y);
			else if (game->map.map_2d[y][x] == ENEMY)
				display_sprite(game->mlx, &game->entities.enemy, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

