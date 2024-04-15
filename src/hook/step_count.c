
#include "../so_long.h"

int	print_step_count(mlx_t *mlx, mlx_image_t **step_count, int steps)
{
	char *temp;

	temp = ft_itoa(steps);
	if (!temp)
		return (-1);
	if (!step_count || !*step_count)
	{
		if(!mlx_put_string(mlx, "steps: ", STEP_COUNT_POS_X, STEP_COUNT_POS_Y))
		{
			free(temp);
			return (-1);
		}
	}
	else
	{
		mlx_delete_image(mlx, *step_count);
	}
	*step_count = mlx_put_string(mlx, temp, STEP_COUNT_POS_X + 80, STEP_COUNT_POS_Y);
	if (!step_count)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (0);
}
