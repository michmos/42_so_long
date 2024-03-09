
#include "so_long.h"
#define	BUFFER_SIZE 128

void	err_exit(const char *str)
{
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

char	*read_file(int fd)
{
	char	*content;
	char	*buffer;
	char	*temp;

	content = NULL;
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE - 1) != 0)
	{
		if (!*buffer)
			return (free(buffer), free(content), NULL);
		else
		{
			temp = ft_strjoin(content, buffer);
			free(content);
			if (!temp)
				return (free(buffer), NULL);
			content = temp;
			ft_memset(buffer, 0, ft_strlen(buffer));
		}
	}
	free(buffer);
	return (content);
}

