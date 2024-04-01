
#ifndef UTILS_H
# define UTILS_H

# include "../../external_libs/42_libs/src/libft/libft.h"
# include "../../external_libs/MLX42/include/MLX42/MLX42.h"

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
* @param y_pos A pointer to a double that will be initialized with the
* y-location in case the item is found - otherwise -1
* @param x_pos A pointer to a double that will be initialized with the
* x-location in case the item is found - otherwise -1
*/
void	find_item_pos(char **map, char item, double *y_pos, double *x_pos);

/*
* This functions frees an array of pointers. Therefore the array needs to be
* terminated with a pointer to NULL
*
* @param arr The array to be freed
*/
void	free_2d_array(void **arr);

/*
* This function creates a copy of a 2d map and returns it on success. NULL is
* returned on failure
*
* @param map The map to copy
* @param size The size of the map (excluding the terminating NULL pointer)
*/
char	**dup_map(char **map, size_t	size);

/*
* This function returns the rgba value given values for the 4 color channels
*
* @param r The value for the red channel
* @param g The value for the green channel
* @param b The value for the blue channel
* @param a The value for the alpha channel
*/
int get_rgba(int r, int g, int b, int a);

/*
* This function returns the pixel rgba value given an image and the pixel
* location
*
* @param img The image to retrieve the information from
* @param y The y location of the pixel
* @param x The x location of the pixel
*/
int	get_pixel(mlx_image_t *img, int y, int x);


// utils_free.c --------------------------------------------------------------//
/*
* This function deletes each image of a sprite, before it frees the memory 
* holding the pointers to the images
*
* @param mlx The mlx window the imgs refer to
* @param frames The array holding the pointers to the imgs
*/
void	delete_frames(mlx_t *mlx, mlx_image_t **frames);

/*
* This function deletes each image of each sprite, held by sprites and frees the
* related memory.
*
* @param mlx The mlx window the imgs refer to
* @param sprites The array holding several sprites, consisting of several imgs
*/
void	delete_sprites(mlx_t	*mlx, mlx_image_t ***sprites);


/*
* This function returns true if the map contains a specific entity, false
* otherwise.
*
* @param map The map to search the character in
* @param entity The character the look for
*/
int has_entity(char **map, int entity);

/*
* This function increments an index in a circular manner, i.e. it starts
* from the beginning after reaching the max value
*
* @param index The current index
* @param max The max value for the index
*/

int	circular_increment(int index, int max);

#endif
