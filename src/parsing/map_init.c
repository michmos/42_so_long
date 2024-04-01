
#include "../so_long.h"

static char	*read_file(int fd)
{
	char	*content;
	char	*buffer;
	char	*temp;

	content = NULL;
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE - 1) != 0)
	{
		if (!*buffer)
			return (free(buffer), free(content), NULL);
		else
		{
			temp = ft_strjoin(content, buffer);
			free(content);
			if (!temp)
				return (free(buffer), NULL);
			content = temp;
			ft_memset(buffer, 0, ft_strlen(buffer));
		}
	}
	free(buffer);
	return (content);
}

static char *get_map(const char *map_path)
{
	int 	fd;
	char	*map;
	int		strlen;

	strlen = ft_strlen(map_path);
	if (strlen < 4 || ft_strncmp(&map_path[strlen - 4], ".ber", 4) != 0)
		err_exit("file must end with .ber extension");
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		err_exit("opening file failed");
	}
	map = read_file(fd);
	if (!map)
	{
		err_exit("reading file failed");
	}
	return (map);
}

static size_t	get_height(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	init_map(t_map *map, const char *map_path)
{
	map->map_1d = get_map(map_path);
	map->map_2d = ft_split(map->map_1d, '\n');
	if (!map->map_2d)
	{
		free(map->map_1d);
		exit(EXIT_FAILURE);
	}
	map->height = get_height(map->map_2d);
	map->width = ft_strlen(map->map_2d[0]);
	find_item_pos(map->map_2d, 'E', &map->exit_pos.y, &map->exit_pos.x);
	find_item_pos(map->map_2d, 'P', &map->player_pos.y, &map->player_pos.x);
}
