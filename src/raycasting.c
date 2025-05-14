#include "../inc/cub3D.h"

t_vector	calculate_ray_dir(t_player *player, int screen_x, int screen_width)
{
	double	camera_x;
	
	camera = ((2.0 * screen_x) / screen_width) - 1.0;

}

void	cast_ray(t_mlx_data *data)
{
	int		screen_x;
	int		screen_width;
	t_ray	ray;

	screen_x = 0;
	screen_width = data->map_width * TILE_SIZE;
	while (screen_x < screen_width)
	{
		ray.dir = calculate_ray_dir(data->player, screen_x, screen_width);
		perform_dda();
		calculate_wall_dist();
		draw_ray();
		x++;
	}
}
