
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
void	print_err(const char *str);

// map_init.c
void	init_map(t_map *map, const char *map_path);

// error_check.c
int	error_check(t_map *map);

#endif
