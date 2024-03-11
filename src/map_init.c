
#include "so_long.h"

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

static char **get_map(const char *map_path)
{
	int 	fd;
	char	*content;
	char	**map;
	int		strlen;

	strlen = ft_strlen(map_path);
	if (strlen < 4 || ft_strncmp(&map_path[strlen - 4], ".ber", 4) != 0)
		err_exit("file must end with .ber extension");
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		err_exit("opening file failed");
	}
	content = read_file(fd);
	if (!content)
	{
		err_exit("reading file failed");
	}
	map = ft_split(content, '\n');
	free(content);
	if (!map)
	{
		exit(EXIT_FAILURE);
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
	map->map = get_map(map_path);
	map->height = get_height(map->map);
	map->width = ft_strlen(map->map[0]);
	// TODO: continue here with initialization (-1 if not found), maybe get_map should retun single string and split afterwards (would also be beneicial for finding duplicates)
	// further trimm new lines at beginning and end before splitting
	map->exit_pos = 
	map->player_pos = 
}
