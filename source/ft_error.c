#include "../includes/cub3d.h"

void	ft_error(const char *message)
{
	ft_putstr_fd("Error: ", 2);//printf de olabilir
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}
