
#include "../so_long.h"

static void clean_up_frames(mlx_t *mlx, mlx_image_t **frames)
{
	size_t	i;

	i = 0;
	while (frames[i])
	{
		mlx_delete_image(mlx, frames[i]);
		i++;
	}
	free(frames);
}

static void clean_up_sprites(mlx_t *mlx, mlx_image_t ***sprites)
{
	size_t	i;

	i = 0;
	while (sprites[i])
	{
		clean_up_frames(mlx, sprites[i]);
		i++;
	}
	free(sprites);
}

static mlx_image_t	*dup_frame(mlx_t *mlx, mlx_image_t *src, size_t start_x, size_t start_y)
{
	size_t 	 	y;
	size_t 	 	x;
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

static mlx_image_t **split_into_frames(mlx_t *mlx, mlx_image_t *sprite_sheet, size_t row, size_t num_frames)
{
	size_t		i;
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
			clean_up_frames(mlx, frames);
			return (NULL);
		}
		i++;
	}
	frames[i] = NULL;
	return (frames);
}

mlx_image_t ***split_sprite_sheet(mlx_t *mlx, mlx_image_t *sprite_sheet, size_t num_vars, size_t num_frames)
{
	mlx_image_t	***sprites;
	size_t		i;

	sprites = (mlx_image_t ***) malloc((num_vars + 1) * sizeof(mlx_image_t **));
	if (!sprites)
	{
		return (NULL);
	}
	i = 0;
	while (i < num_vars)
	{
		sprites[i] = split_into_frames(mlx, sprite_sheet, i, num_frames);
		if (!sprites[i])
		{
			clean_up_sprites(mlx, sprites);
			return (NULL);
		}
		i++;
	}
	sprites[i] = NULL;
	return (sprites);
}

