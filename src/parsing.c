
#include "so_long.h"
#include <stdlib.h>

char **parsing(char *map_path)
{
	int 	fd;
	char	*content;
	char	**map;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		err_exit("error when opening file");
	}
	content = read_file(fd);
	if (!content)
	{
		err_exit("error when reading file");
	}
	map = ft_split(content, '\n');
	free(content);
	if (!map)
	{
		exit(EXIT_FAILURE);
	}
	return (map);
}
