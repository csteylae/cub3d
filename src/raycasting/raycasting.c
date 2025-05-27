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

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	draw_wall_column(t_mlx_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	color;

	y = 0;
	color = 0x808080;
	while (y < draw_start)
	{
		//draw the ceiling
		my_pixel_put(&data->framebuffer, x, y, 0x87ceeb);
		y++;
	}
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(&data->framebuffer,x, y, color);
		y++;
	}
	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_pixel_put(&data->framebuffer,x, y, 0x228b22);
		y++;
	}
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
		ray.dir = calculate_ray_dir(&data->player, screen_x, SCREEN_WIDTH);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
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

