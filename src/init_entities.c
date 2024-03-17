
#include "so_long.h"

static int init_entity(mlx_t *mlx, t_entity *entity, mlx_image_t *img)
{
	entity->sprites = split_sprite_sheet(mlx, img);
	if (!entity->sprites)
		return (-1);
	entity->num_variations = img->height / TEXTURE_WIDTH;
	entity->num_frames = img->width / TEXTURE_WIDTH;
	return (0);
}

int	init_entities(mlx_t *mlx, t_entity_list *entities, t_img_list* imgs)
{
	if (init_entity(mlx, &entities->space, imgs->space) == -1)
		return (-1);
	if (init_entity(mlx, &entities->wall, imgs->wall) == -1)
		return (-1);
	if (init_entity(mlx, &entities->player, imgs->player) == -1)
		return (-1);
	if (init_entity(mlx, &entities->exit, imgs->exit) == -1)
		return (-1);
	if (init_entity(mlx, &entities->item, imgs->items) == -1)
		return (-1);
	if (init_entity(mlx, &entities->enemy, imgs->enemies) == -1)
		return (-1);
	return (0);
}

