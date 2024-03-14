
#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_map	map;
	mlx_t   *mlx;
	t_imgs imgs;

	if (argc != 2)
	{
		err_exit("unvalid arguments");
	}
	init_map(&map, argv[1]);
	if (error_check(&map))
	{
		free_2d_array(map.map);
		exit(EXIT_FAILURE);
	}
	mlx = mlx_init(TEXTURE_WIDTH * map.width, TEXTURE_WIDTH * map.height, "so_long", true);
	if (!mlx)
	{
		free_2d_array(map.map);
		exit(EXIT_FAILURE);
	}
	if (load_images(mlx, &imgs) == -1)
	{
		free_2d_array(map.map);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(mlx, imgs.space, 100, 100);
	mlx_loop(mlx);
	return (0);
}
