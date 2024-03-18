
#include "so_long.h"

static int init_entity(mlx_t *mlx, t_entity *entity, mlx_image_t *sprite_sheet, int fps)
{
	entity->num_variations = sprite_sheet->height / TEXTURE_WIDTH;
	if (entity->num_variations == 0)
	{
		print_err("Height of pngs needs to be >= TEXTURE_WIDTH");
		return (-1);
	}
	entity->num_frames = sprite_sheet->width / TEXTURE_WIDTH;
	if (entity->num_frames == 0)
	{
		print_err("Width of pngs needs to be >= TEXTURE_WIDTH");
		return (-1);
	}
	entity->current_frame = -1;
	entity->fps = fps;
	entity->delta_time = 0;
	entity->sprites = split_sprite_sheet(mlx, sprite_sheet, entity->num_variations, entity->num_frames);
	if (!entity->sprites)
		return (-1);
	return (0);
}

int	init_entities(mlx_t *mlx, t_entity_list *entities, t_img_list* imgs)
{
	if (init_entity(mlx, &entities->space, imgs->space, SPACE_FPS) == -1)
		return (-1);
	// if (init_entity(mlx, &entities->wall, imgs->wall, WALL_FPS) == -1)
	// 	return (-1);
	// if (init_entity(mlx, &entities->player, imgs->player, PLAYER_FPS) == -1)
	// 	return (-1);
	// if (init_entity(mlx, &entities->exit, imgs->exit, EXIT_FPS) == -1)
	// 	return (-1);
	// if (init_entity(mlx, &entities->item, imgs->items, ITEM_FPS) == -1)
	// 	return (-1);
	// if (init_entity(mlx, &entities->enemy, imgs->enemies, ENEMY_FPS) == -1)
	// 	return (-1);
	return (0);
}

