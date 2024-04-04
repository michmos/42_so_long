
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../external_libs/42_libs/src/libft/libft.h"
# include "../external_libs/42_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/42_libs/src/ft_printf/ft_printf.h"
# include "../external_libs/MLX42/include/MLX42/MLX42.h"

# include "utils/utils.h"
# include "settings.h"
# include <fcntl.h>
# include <math.h>

# define CHAR_PIXEL_SIZE 10

enum e_entity
{
	SPACE = '0',
	WALL = '1',
	PLAYER = 'P',
	EXIT = 'E',
	ITEM = 'C',
	ENEMY = 'M'
};

enum e_direction
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_2d;
	char		*map_1d;
	int			steps_min;
	t_vector	player_pos;
	t_vector	exit_pos;
	size_t		num_items;
	size_t		num_enemies;

	mlx_image_t		*step_count;
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
	enum e_entity	type;
	mlx_image_t		***sprites;
	int				num_variations;
	int				current_variation;
	int				num_frames;
	int				current_frame;
	int				fps;
	double			delta_time;
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

typedef struct	s_game
{
	t_map 			map;
	mlx_t			*mlx;
	t_entity_list	entities;
} t_game;

// main.c ---------------------------------------------------------------------//
int	main(int argc, char **argv);

// free.c --------------------------------------------------------------------//
void	end_game(t_game *game, int exit_code);

// map_ops.c -----------------------------------------------------------------//
int		copy_t_map(t_map *map_dest, t_map *map_src);
void	restore_map(t_map *map, t_map *backup);
char	get_entity(char **map, t_vector *position);



// ------------------------- INIT_STRUCT/ ------------------------------------//
// init_struct.c -------------------------------------------------------------//
void	init_struct(t_game *game, char *map_path);

// map_init.c ----------------------------------------------------------------//
void	init_map(t_map *map, const char *map_path);

// error_check.c -------------------------------------------------------------//
int	error_check(t_map *map);

// error_check2.c ------------------------------------------------------------//
int	has_valid_path(t_map *map);

// load_images.c -------------------------------------------------------------//
int load_images(mlx_t *mlx, t_img_list *imgs);

// sprites.c -----------------------------------------------------------------//
mlx_image_t ***split_sprite_sheet(mlx_t *mlx, mlx_image_t *sprite_sheet, int num_variations, int num_frames);

// init_entities.c -----------------------------------------------------------//
int	init_entities(mlx_t *mlx, t_entity_list *entities, t_img_list* imgs);



// ---------------------------- HOOK/ ----------------------------------------//
// hooks.c -------------------------------------------------------------------//
void	my_loop_hook(void *param);

// display_map.c -------------------------------------------------------------//
int	display_map(t_game *game);

// move_player.c -------------------------------------------------------------//
void	move_player(mlx_t *mlx, t_entity *player, t_map *map);

// disable_item.c ------------------------------------------------------------//
void	disable_item(t_entity *item, t_map *map);

// update_animations.c -------------------------------------------------------//
void	update_animations(t_game *game);

// move_enemies.c ------------------------------------------------------------//
void	move_enemies(mlx_t *mlx, t_entity *enemy, t_map *map);

// end_screens.c -------------------------------------------------------------//
void	display_screen(t_game *game, int color, char *message);

#endif
