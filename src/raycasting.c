#include "../inc/cub3D.h"

t_vector	calculate_ray_dir(t_player *player, int screen_x, int screen_width)
{
	//the camera_x is the maps the entire screen of the player view defined by plane vector on a value comprised between -1 and 1
	//a way to map the horizontal position on the screen yo a direction within the fov
	double		camera_x; // rpz a position inside the camera_plane (plane vector),so its like a horizontal coord on that camera/screen
	t_vector	ray_dir;
	
	camera_x = 2.0 * screen_x / (double)screen_width - 1.0; //its val is comprised between -1 (left corner of the camera plane vect) and 1 (right side) 0 is the center of the camera plane
	ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray_dir.y = player->dir.y + player->plane.y *camera_x;
	return (ray_dir);
}

t_vector	get_side_dist(char **map, t_vector pos)
{
}



void	initialize_dda(t_mlx_data *data, t_player *player, t_ray *ray)
{
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist = get_delta_dist(data, player->pos, ray->dir);
	ray->side_dist = get_side_dist(data->map, player.pos);

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
		initilize_dda(data, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist();
		draw_ray();
		screen_x++;
	}
}
