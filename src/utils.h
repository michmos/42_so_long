
#ifndef UTILS_H
# define UTILS_H

# include "../external_libs/42_libs/src/libft/libft.h"

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

/*
* This function checks whether all items have been collected. Returns true or
* false
*
* @param map The map to be checked for items
*/
int	all_items_collected(char **map);


#endif
