
#include "so_long.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		err_exit("unvalid arguments");
	}
	map.map = parsing(argv[1]);
	if (error_check(&map) == true)
	{
		free(map.map);
		exit(EXIT_FAILURE);
	}
	return (0);
}
