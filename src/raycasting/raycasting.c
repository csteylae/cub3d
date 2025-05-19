#include "../../inc/cub3D.h"

void	perform_dda(t_mlx_data *data, t_ray *ray)
{
	while (ray->hit == false)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = VERTICAL;
		}
		if (ray->map.x < 0 || ray->map.x >= data->map_width
			|| ray->map.y < 0 || ray->map.y >= data->map_height)
		{
			ray->hit = true;
			break;
		}
		if (data->map[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
}

void	calculate_wall_dist(t_player player, t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		ray->perp_wall_dist = (ray->map.x - player.pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
	    ray->perp_wall_dist = (ray->map.y - player.pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	printf("check : %f\n\n",ray->perp_wall_dist);
}

/*
void	draw_ray_2d(t_mlx_data *data, t_ray *ray)
{
	t_line		line;
	t_vector	wall;
   
	line.start.x = (int)(data->player.pos.x * TILE_SIZE);
	line.start.y =(int)(data->player.pos.y * TILE_SIZE);
	if (ray->side == HORIZONTAL)
	{
		line.end.x = ray->map.x * TILE_SIZE;
		if (ray->step.x > 0) //next right grid cell
			line.end.x = line.end.x + TILE_SIZE;
		wall.y = data->player.pos.y + (ray->perp_wall_dist * ray->dir.y);
		line.end.y = (int)(wall.y * TILE_SIZE);
	}
	else
	{
		line.end.y = ray->map.y * TILE_SIZE;
		if (ray->step.y > 0) // bottom side
			line.end.y = line.end.y + TILE_SIZE;
		wall.x = data->player.pos.x + (ray->perp_wall_dist * ray->dir.x);
		line.end.x = (int)(wall.x * TILE_SIZE);
	}
	draw_line(data, line, 0xff0000);
}
*/

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

void	cast_ray(t_mlx_data *data)
{
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
		calculate_wall_dist(data->player, &ray);
		draw_ray_2d(data, &ray);
		screen_x++;
	}
}
