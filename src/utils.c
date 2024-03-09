
#include "so_long.h"
#define	BUFFER_SIZE 128

void	err_exit(const char *str)
{
	if (str)
		print_err(str);
	exit(EXIT_FAILURE);
}

void	print_err(const char *str)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}
