#include "../../inc/cub3D.h"

static int	get_width_map(char **map)
{
	int	width;

	width = ft_strlen(map[0]);
	return (width);
}

static int	get_height_map(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

static char	**get_map(void)
{
	static char *map[] = {
		"111111111",
		"100000001",
		"1001N0001",
		"100010001",
		"111111111",
		NULL
	};
	return (map);
}

t_vector	vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

void	init_minimap(t_mlx_data *data)
{
	data->map = get_map();
	data->map_height = get_height_map(data->map);
	data->map_width = get_width_map(data->map);
}
