
#include "so_long.h"
#include "utils.h"
#include <stdint.h>

mlx_image_t	*dup_frame(mlx_t *mlx, mlx_image_t *src, int start_x, int start_y)
{
	int 	 	y;
	int 	 	x;
	int  		rgba;
	mlx_image_t *frame;

	frame = mlx_new_image(mlx, TEXTURE_WIDTH, TEXTURE_WIDTH);
	if (!frame)
		return (NULL);
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

mlx_image_t **split_into_frames(mlx_t *mlx, mlx_image_t *sprite_sheet, int row)
{
	int			i;
	int			num_frames;
	mlx_image_t	**frames;

	i = 0;
	num_frames = sprite_sheet->width / TEXTURE_WIDTH; // TODO: protext if unexact?
	frames = (mlx_image_t **) malloc((num_frames + 1) * sizeof(mlx_image_t *));
	if (!frames)
		; // TODO: protect
	while (i < num_frames)
	{
		frames[i] = dup_frame(mlx, sprite_sheet, i * TEXTURE_WIDTH, row * TEXTURE_WIDTH);
		if (!frames[i])
			; // TODO: protect
		i++;
	}
	frames[i] = NULL;
	return (frames);
}

mlx_image_t ***split_sprite_sheet(mlx_t *mlx, mlx_image_t *sprite_sheet)
{
	mlx_image_t	***frames;
	int			num_variations;
	int			i;


	num_variations = sprite_sheet->height / TEXTURE_WIDTH; // TODO: what if not exact
	frames = (mlx_image_t ***) malloc((num_variations + 1) * sizeof(mlx_image_t **));
	if (!frames)
		return (NULL);
	i = 0;
	while (i < num_variations)
	{
		frames[i] = split_into_frames(mlx, sprite_sheet, i);
		i++;
	}
	frames[i] = NULL;
	return (frames);
}

