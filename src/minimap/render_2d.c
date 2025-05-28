#include "../../inc/cub3D.h"

void draw_ray_2d(t_mlx_data *data, t_ray *ray)
{
    t_line line;
    t_vector wall_hit;
   
    // Starting point is player position
    line.start.x = (int)(data->player.pos.x * TILE_SIZE);
    line.start.y = (int)(data->player.pos.y * TILE_SIZE);
    
    // Calculate exact hit point
    wall_hit.x = data->player.pos.x + ray->dir.x * ray->perp_wall_dist;
    wall_hit.y = data->player.pos.y + ray->dir.y * ray->perp_wall_dist;
    
    // Set end point of line
    line.end.x = (int)(wall_hit.x * TILE_SIZE);
    line.end.y = (int)(wall_hit.y * TILE_SIZE);
    
    // Draw the ray
    draw_line(data, line, 0xff0000);
}

/*
void	cast_ray_2d(t_mlx_data *data)
{
	//2D RENDER
	int		screen_x;
	int		screen_width;
	t_ray	ray;

	screen_x = 0;
	screen_width = data->map_width * TILE_SIZE;
	while (screen_x < screen_width)
	{
		ray.dir = calculate_ray_dir(&data->player, screen_x, screen_width);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
		draw_ray_2d(data, &ray);
		screen_x++;
	}
}
*/
