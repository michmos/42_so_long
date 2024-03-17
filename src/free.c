
#include "so_long.h"

void	free_entities(mlx_t *mlx, t_entity_list *entities)
{
	delete_sprites(mlx, entities->space.sprites);
	delete_sprites(mlx, entities->wall.sprites);
	delete_sprites(mlx, entities->player.sprites);
	delete_sprites(mlx, entities->exit.sprites);
	delete_sprites(mlx, entities->item.sprites);
	delete_sprites(mlx, entities->enemy.sprites);
}

