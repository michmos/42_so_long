
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external_libs/42_libs/src/libft/libft.h"
# include "../external_libs/42_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/42_libs/src/ft_printf/ft_printf.h"
# include "../external_libs/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define TEXTURE_WIDTH 64
# define PATH_TEXTURE_SPACE "../textures/water"
# define PATH_TEXTURE_WALL "../textures/rock"
# define PATH_TEXTURE_PLAYER "../textures/boat"
# define PATH_TEXTURE_EXIT "../textures/exit"
# define PATH_TEXTURE_ITEMS "../textures/trash"
# define PATH_TEXTURE_ENEMIES "../textures/fish"

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
	int		steps_min;
	int		player_pos[2];
	int		exit_pos[2];

} t_map;

typedef struct s_imgs
{
	mlx_image_t *space;
	mlx_image_t *wall;
	mlx_image_t *player;
	mlx_image_t *exit;
	mlx_image_t *items;
	mlx_image_t *enemies;
} t_imgs;

enum e_change_name
{
	WALL = '1',
	PLAYER = 'P',
	ITEM = 'C',
	EXIT = 'E'
};

// utils.c -------------------------------------------------------------------//

/*
* This function calls print_err with err_message and then exits with -1
*
* @param err_message The error message to print
*/
void	err_exit(const char *str);

/* This function prints a message to stderr in the format "Error\n<message>\n"
*
* @param err_message The error message to print
*/
void	print_err(const char *err_message);

/*
* This functions searches for a character inside a 2D map
* 
* @param map The map to search for the item
* @param item The item to look for
* @param y_pos A pointer to an integer that will be initialized with the
* y-location in case the item is found - otherwise -1
* @param x_pos A pointer to an integer that will be initialized with the
* x-location in case the item is found - otherwise -1
*/
void	find_item_pos(char **map, char item, int *y_pos, int *x_pos);

/*
* This functions frees an array of strings. Therefore the array needs to be
* terminated with a pointer to NULL
*
* @param arr The array to be freed
*/
void	free_2d_array(char **arr);

/*
* This function creates a copy of a 2d map and returns it on success. NULL is
* returned on failure
*
* @param map The map to copy
* @param size The size of the map (excluding the terminating NULL pointer)
*/
char	**dup_map(char **map, size_t	size);

// map_init.c ----------------------------------------------------------------//
void	init_map(t_map *map, const char *map_path);

// error_check.c -------------------------------------------------------------//
int	error_check(t_map *map);

// load_images.c -------------------------------------------------------------//
int load_images(mlx_t *mlx, t_imgs *imgs);

#endif
