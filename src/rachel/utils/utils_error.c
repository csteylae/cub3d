#include "../../../inc/cub3D.h"

void    ft_error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(EXIT_FAILURE);
}

static void	ft_free_map(t_data *game)
{
	int	y;

	y = 0;
	if (game->map != NULL)
	{
		while (game->map[y] != NULL)
		{
			free(game->map[y]);
			y++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	ft_free_error(char *str, t_data *game)
{
	ft_free_map(game);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}