
#include "so_long.h"
#include <unistd.h>

void	err_exit(const char *str)
{
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
