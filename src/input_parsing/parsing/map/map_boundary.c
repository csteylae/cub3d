#include "../../../../inc/cub3D.h"

void	free_padded_map(char **padded_map, int len)
{
	int	i;

	i = 0;
	while (i != len)
	{
		if (padded_map[i])
		{
			free(padded_map[i]);
			padded_map[i] = NULL;
		}
		i++;
	}
	free(padded_map);
	padded_map = NULL;
}

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	exterior_flood_fill(char **map, int x, int y, bool *is_valid)
{
	if (y < 0 || x < 0  || x >= get_max_width(map) || y >= get_map_height(map))
		return ;
	if (*is_valid == false)
		return ;
	if (map[y][x] == '0' || is_player(map[y][x]))
	{
		*is_valid = false;
		return ;
	}
	if (map[y][x] == '.' || map[y][x] == '1')
		return ;
	map[y][x] = '.';
	exterior_flood_fill(map, x + 1, y, is_valid);
	exterior_flood_fill(map, x - 1, y, is_valid);
	exterior_flood_fill(map, x, y + 1, is_valid);
	exterior_flood_fill(map, x, y - 1, is_valid);
}

static void print_padded_map(char **map)
{
	int	i;

	i = 0;
	printf("MAP COPY->\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	check_map_boundary(t_data *game)
{
	char	**copy;
	bool	is_valid;

	is_valid = true;
	copy = create_padded_map(game);
	print_padded_map(copy);
	if (!copy)
		free_all_error("Error\nCannot malloc map copy!\n", game);
	exterior_flood_fill(copy, 0, 0, &is_valid);
	free_padded_map(copy, get_map_height(copy));
	if (!is_valid)
		free_all_error("Error\nMap isnt closed :o\n", game);
	return ;
}
