#include "../../inc/cub3D.h"

int get_pixel_color(t_img img, int x, int y)
{
	char *pixel;

	pixel = img.pixel_addr + (y * img.line_len) + (x * (img.bpp / 8));
	return *(int *)pixel;
}

double get_exact_wall_hit(t_mlx_data *data, t_ray ray)
{
    double wall_x;

    if (ray.side == 0)
        wall_x = data->player.pos.y + ray.perp_wall_dist * ray.dir.y; 
    else 
        wall_x = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
    
    wall_x -= floor(wall_x); 
    return (wall_x);
}

int get_texture_column(double wall_x, t_ray ray)
{
    int tex_column;
    tex_column = (int)(wall_x * TILE_SIZE);
    if (tex_column < 0)
        tex_column = 0;
    if (tex_column >= TILE_SIZE)
        tex_column = TILE_SIZE - 1;
    if (ray.side == 0 && ray.dir.x > 0)
        tex_column = TILE_SIZE - tex_column - 1;
    if (ray.side == 1 && ray.dir.y < 0)
        tex_column = TILE_SIZE - tex_column - 1;
    return (tex_column);
}

int	get_wall_side(t_ray ray)
{
	if (ray.side == 0) 
	{
		if (ray.step.x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else 
	{
		if (ray.step.y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}
void	draw_vertical_line(t_mlx_data *data, int x, int y_begin, int y_end, int color)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, x, y, color);
		y++;
	}
}

t_wall	init_wall(t_mlx_data *data, t_ray ray)
{
	t_wall wall;

	wall.height = (int)SCREEN_HEIGHT / ray.perp_wall_dist;
	if (wall.height < 0)
		wall.height = 0;
	if (wall.height > SCREEN_HEIGHT * 3)
		wall.height = SCREEN_HEIGHT *3;
	wall.begin = -wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.begin < 0)
		wall.begin = 0;
	wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.end >= SCREEN_HEIGHT)
		wall.end = SCREEN_HEIGHT - 1;
	wall.hit = get_exact_wall_hit(data, ray);
	wall.tex_col = get_texture_column(wall.hit, ray);
	wall.side = get_wall_side(ray);
	return (wall);
}


void draw_textured_wall(t_mlx_data *data, t_ray ray, int screen_x)
{
    t_wall wall;
    int screen_y;
    double step;
    double tex_pos;
    int tex_y;
    int color;

    wall = init_wall(data, ray);
    step = 1.0 * TILE_SIZE / wall.height;
    tex_pos = (wall.begin - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;
	screen_y = wall.begin;
	if (ray.perp_wall_dist < 0.05)  // Very close walls
{
    printf("Close wall: perp_dist=%.4f, height=%d, step=%.6f\n",
           ray.perp_wall_dist, wall.height, step);
}
    draw_vertical_line(data, screen_x, 0, wall.begin, SKY_BLUE);
	while (screen_y < wall.end)
	{
       tex_y = (int)tex_pos;
       if (tex_y < 0)
           tex_y = 0;
       if (tex_y >= TILE_SIZE)
           tex_y = TILE_SIZE - 1;
       tex_pos += step;
       color = get_pixel_color(data->texture[wall.side].img, wall.tex_col, tex_y);
       my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
	   screen_y++;
    }
    draw_vertical_line(data, screen_x, wall.end, SCREEN_HEIGHT, FOREST_GREEN);
}
