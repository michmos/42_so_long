
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external_libs/42_libs/src/libft/libft.h"
# include "../external_libs/42_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/42_libs/src/ft_printf/ft_printf.h"
# include <fcntl.h>

typedef struct s_map
{
	size_t	height;
	size_t	width;
	char	**map;

} t_map;

// utils.c
void	err_exit(const char *str);
char	*read_file(int fd);

// parsing.c
char **parsing(char *map_path);

#endif
