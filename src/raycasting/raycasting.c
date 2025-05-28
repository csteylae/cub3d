#include "../../inc/cub3D.h"

t_vector	calculate_ray_dir(t_mlx_data *data, t_player *player, int screen_x, int screen_width)
{
	//the camera_x maps the entire screen of the player view defined by plane vector on a value comprised between -1 and 1
	//a way to map the horizontal position on the screen yo a direction within the fov
	double		camera_x; // rpz a position inside the camera_plane (plane vector),so its like a horizontal coord on that camera/screen
	t_vector	ray_dir;
	
	if (screen_width <= 0)
	{
		// if screen corruption occured (reducing size or idk)
		printf("Error: invalid screen width\n");
		close_cub3D(data);
	}
	camera_x = 2.0 * screen_x / (double)screen_width - 1.0; //its val is comprised between -1 (left corner of the camera plane vect) and 1 (right side) 0 is the center of the camera plane
	ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray_dir.y = player->dir.y + player->plane.y *camera_x;
	return (ray_dir);
}

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	cast_ray(t_mlx_data *data)
{
	int		screen_x;
	t_ray	ray;
	int		wall_height;
	int		draw_start;
	int		draw_end;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		ray.dir = calculate_ray_dir(data, &data->player, screen_x, SCREEN_WIDTH);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
		if (!isfinite(ray.perp_wall_dist) || ray.perp_wall_dist <= 0.001) // check because we will cast it into int
		{
			screen_x++;
			continue;
		}
		wall_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		draw_wall_column(data, screen_x, draw_start, draw_end);
		screen_x++;
	}
}
