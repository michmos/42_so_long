
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
		free(map.map); // TODO: free 2d array instead
		exit(EXIT_FAILURE);
	}
	map.map += 1;
	// if (error_check(&map) == true)
	// {
	// 	free(map.map);
	// 	exit(EXIT_FAILURE);
	// }
	return (0);
}
