#include "../inc/cub3D.h"

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
		"1011P0001",
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

t_vector	get_plane(t_vector dir, double plane_len)
{
	t_vector	plane;

	plane.x = -dir.y * plane_len;
	plane.y = dir.x * plane_len;
	return (plane);
}

static t_minimap_square	init_square(void)
{
	t_minimap_square	minimap_square;

	minimap_square.color = RED;
	minimap_square.size = 10;
	minimap_square.pos = vec(64, 64);
	minimap_square.dir = vec(0, 1);
	minimap_square.fov_rad = 66 * (M_PI / 180);
	minimap_square.plane_len = tan(minimap_square.fov_rad / 2);
	minimap_square.plane = get_plane(minimap_square.dir, minimap_square.plane_len);

//	minimap_square.x = 64;
//	minimap_square.y = 64;
//	minimap_square.rot_angle = 0;

	
	return (minimap_square);
}

void	init_minimap(t_mlx_data *data)
{
	data->map = get_map();
	data->map_height = get_height_map(data->map);
	data->map_width = get_width_map(data->map);
	data->square = init_square();
}
