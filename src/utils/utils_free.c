
#include "utils.h"

void	delete_frames(mlx_t *mlx, mlx_image_t **frames)
{
	int	i;

	i = 0;
	if (!frames)
		return ;
	while (frames[i])
	{
		mlx_delete_image(mlx, frames[i]);
		i++;
	}
	free(frames);
}

void	delete_sprites(mlx_t *mlx, mlx_image_t ***sprites)
{
	int	i;

	if (!sprites | !*sprites)
		return ;
	while (sprites[i])
	{
		delete_frames(mlx, sprites[i]);
		i++;
	}
	free(sprites);
}

