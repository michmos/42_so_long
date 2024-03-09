
#include "so_long.h"
#define	BUFFER_SIZE 128

void	err_exit(const char *str)
{
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

