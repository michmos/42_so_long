
#include "../so_long.h"

static void	reset_player(t_entity *player, t_vector pos)
{
	size_t	frame;
	size_t	variation;
	size_t	y;
	size_t	x;

	y = pos.y * TEXTURE_WIDTH;
	x = pos.x * TEXTURE_WIDTH;
	variation = 0;
	while (variation < player->num_variations)
	{
		frame = 0;
		while (frame < player->num_frames)
		{
			player->sprites[variation][frame]->instances[0].y = y;
			player->sprites[variation][frame]->instances[0].x = x;
			frame++;
		}
		variation++;
	}
}

static void	reset_items(t_entity *item)
{
	size_t	variation;
	size_t	frame;
	size_t	instance;
	
	variation = 0;
	while(variation < item->num_variations)
	{
		frame = 0;
		while (frame < item->num_frames)
		{
			instance = 0;
			while (instance < item->sprites[variation][frame]->count)
			{
				item->sprites[variation][frame]->instances[instance].enabled = true;
				instance++;
			}
			frame++;
		}
		variation++;
	}
}

static void	reset_enemies(t_entity *enemy, t_map *map)
{
	size_t		i;
	t_vector	pos;

	i = 0;
	while (i < map->num_enemies)
	{
		pos = get_enemy_i_pos(map->map_2d, i);
		move_enemy_i_sprites(i, enemy, &pos);
		i++;
	}
}

void	reset_map(t_map *map, t_map *backup)
{
	free(map->map_1d);
	free_2d_array((void **) map->map_2d);
	copy_t_map(map, backup);
}

void	reset_game(t_game *game)
{
	mlx_delete_image(game->mlx, game->map.steps_img);
	reset_map(&game->map, &game->backup_map);
	reset_enemies(&game->entities.enemy, &game->map);
	reset_items(&game->entities.item);
	reset_player(&game->entities.player, game->map.player_pos);
	disable_menu(&game->menus.success);
	disable_menu(&game->menus.failure);
}
