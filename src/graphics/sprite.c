
#include "../so_long.h"

mlx_image_t	*dup_frame(mlx_t *mlx, mlx_image_t *src, int start_x, int start_y)
{
	int 	 	y;
	int 	 	x;
	int  		rgba;
	mlx_image_t *frame;

	frame = mlx_new_image(mlx, TEXTURE_WIDTH, TEXTURE_WIDTH);
	if (!frame)
	{
		return (NULL);
	}
	y = 0;
	while (y < TEXTURE_WIDTH)
	{
		x = 0;
		while (x < TEXTURE_WIDTH)
		{
			rgba = get_pixel(src, start_y + y, start_x + x);
			mlx_put_pixel(frame, x, y, rgba);
			x++;
		}
		y++;
	}
	return (frame);
}

mlx_image_t **split_into_frames(mlx_t *mlx, mlx_image_t *sprite_sheet, int row, int num_frames)
{
	int			i;
	mlx_image_t	**frames;

	i = 0;
	frames = (mlx_image_t **) malloc((num_frames + 1) * sizeof(mlx_image_t *));
	if (!frames)
	{
		return (NULL);
	}
	while (i < num_frames)
	{
		frames[i] = dup_frame(mlx, sprite_sheet, i * TEXTURE_WIDTH, row * TEXTURE_WIDTH);
		if (!frames[i])
		{
			delete_frames(mlx, frames);
			return (NULL);
		}
		i++;
	}
	frames[i] = NULL;
	return (frames);
}

mlx_image_t ***split_sprite_sheet(mlx_t *mlx, mlx_image_t *sprite_sheet, int num_variations, int num_frames)
{
	mlx_image_t	***sprites;
	int			i;


	num_variations = sprite_sheet->height / TEXTURE_WIDTH;
	sprites = (mlx_image_t ***) malloc((num_variations + 1) * sizeof(mlx_image_t **));
	if (!sprites)
	{
		return (NULL);
	}
	i = 0;
	while (i < num_variations)
	{
		sprites[i] = split_into_frames(mlx, sprite_sheet, i, num_frames);
		if (!sprites[i])
		{
			delete_sprites(mlx, sprites);
			return (NULL);
		}
		i++;
	}
	sprites[i] = NULL;
	return (sprites);
}

