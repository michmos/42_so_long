
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external_libs/42_libs/src/libft/libft.h"
# include "../external_libs/42_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/42_libs/src/ft_printf/ft_printf.h"
# include "../external_libs/MLX42/include/MLX42/MLX42.h"

# include "utils/utils.h"
# include <fcntl.h>

# define TEXTURE_WIDTH 256

# define SPACE_TEXTURE "textures/ocean_cleanup/textures/water_sprite_sheet.png"
# define WALL_TEXTURE "textures/rock.png"
# define PLAYER_TEXTURE "textures/ocean_cleanup/textures/boat_with_waves256_2.png"
# define EXIT_TEXTURE "textures/exit.png"
# define ITEM_TEXTURE "textures/trash.png"
# define ENEMY_TEXTURE "textures/fish.png"

enum e_entity
{
	SPACE = '0',
	WALL = '1',
	PLAYER = 'P',
	EXIT = 'E',
	ITEM = 'C'
};

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
	int		steps_min;
	int		player_pos[2];
	int		exit_pos[2];

} t_map;

typedef struct s_img_list
{
	mlx_image_t *space;
	mlx_image_t *wall;
	mlx_image_t *player;
	mlx_image_t *exit;
	mlx_image_t *items;
	mlx_image_t *enemies;
} t_img_list;

typedef struct s_entity
{
	mlx_image_t	***sprites;
	int			num_variations;
	int			num_frames;
	int			current_frame;
} t_entity;


typedef struct s_entity_list
{
	t_entity space;
	t_entity wall;
	t_entity player;
	t_entity exit;
	t_entity item;
	t_entity enemy;
} t_entity_list;


// map_init.c ----------------------------------------------------------------//
void	init_map(t_map *map, const char *map_path);

// error_check.c -------------------------------------------------------------//
int	error_check(t_map *map);

// error_check2.c ------------------------------------------------------------//
int	has_valid_path(t_map *map);
int	all_items_collected(char **map);

// load_images.c -------------------------------------------------------------//
int load_images(mlx_t *mlx, t_img_list *imgs);

// sprites.c -----------------------------------------------------------------//
mlx_image_t ***split_sprite_sheet(mlx_t *mlx, mlx_image_t *sprite_sheet);

// init_entities.c -----------------------------------------------------------//
int	init_entities(mlx_t *mlx, t_entity_list *entities, t_img_list* imgs);

// free.c --------------------------------------------------------------------//
void	free_entities(mlx_t *mlx, t_entity_list *entities);

#endif
