
#include "so_long.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_map	map;

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
	return (0);
}
