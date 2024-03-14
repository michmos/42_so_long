
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external_libs/42_libs/src/libft/libft.h"
# include "../external_libs/42_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/42_libs/src/ft_printf/ft_printf.h"
# include "../external_libs/MLX42/include/MLX42/MLX42.h"

# include "utils.h"

# include <fcntl.h>

# define TEXTURE_WIDTH 64
# define SPACE_TEXTURE "textures/ocean_cleanup/textures/water.png"
# define WALL_TEXTURE "textures/rock.png"
# define PLAYER_TEXTURE "textures/boat.png"
# define EXIT_TEXTURE "textures/exit.png"
# define ITEM_TEXTURE "textures/trash.png"
# define ENEMY_TEXTURE "textures/fish.png"

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

enum e_entity
{
	SPACE = '0',
	WALL = '1',
	PLAYER = 'P',
	EXIT = 'E',
	ITEM = 'C'
};

// map_init.c ----------------------------------------------------------------//
void	init_map(t_map *map, const char *map_path);

// error_check.c -------------------------------------------------------------//
int	error_check(t_map *map);

// error_check2.c ------------------------------------------------------------//
int	has_valid_path(t_map *map);

// load_images.c -------------------------------------------------------------//
int load_images(mlx_t *mlx, t_imgs *imgs);

#endif
