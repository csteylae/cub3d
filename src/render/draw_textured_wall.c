#include "../../inc/cub3D.h"

int get_pixel_color(t_img img, int x, int y)
{
	char *pixel;

	pixel = img.pixel_addr + (y * img.line_len) + (x * (img.bpp / 8));
	return *(int *)pixel;
}

double	get_exact_wall_hit(t_mlx_data *data, t_ray ray)
{
	double wall_x;

	if (ray.side == VERTICAL)
		wall_x = data->player.pos.y + ray.perp_wall_dist * ray.dir.y;
	else
		wall_x = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_column(double wall_x, t_ray ray)
{
	int	tex_column;

	(void)ray;
	tex_column = (int)(wall_x * TILE_SIZE);
	if (tex_column < 0)
		tex_column = 0;
	if (tex_column >= TILE_SIZE)
		tex_column = TILE_SIZE - 1;
	if (ray.side == VERTICAL && ray.dir.x > 0)
		tex_column = TILE_SIZE - tex_column - 1;
	if (ray.side == HORIZONTAL && ray.dir.y < 0)
		tex_column = TILE_SIZE - tex_column - 1;
	return (tex_column);
}


int	get_wall_side(t_ray ray)
{
	if (ray.side == VERTICAL) 
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

t_wall	init_wall(t_mlx_data *data, t_ray ray)
{
	t_wall wall;

	wall.height = (int)SCREEN_HEIGHT / ray.perp_wall_dist;
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

void	draw_textured_wall(t_mlx_data *data, t_ray ray, int screen_x)
{
	t_wall	wall;
	int		screen_y;
	int		tex_step; //increase tex_pos
	double	tex_pos; //the 
	int		tex_y; //cast tex_pos into int to get the current row of the texture to render
	int		color;

	wall = init_wall(data, ray);
	screen_y = wall.begin;
	
	tex_step = 1.0 * TILE_SIZE / wall.height;
	tex_pos = (wall.begin - SCREEN_HEIGHT / 2 + wall.height / 2) * tex_step;

	draw_vertical_line(data, screen_x, 0, wall.begin, SKY_BLUE);
	while (screen_y < wall.end)
	{
		tex_y = (int)(tex_pos);
		if (tex_y < 0)
		   	tex_y = 0;
		if (tex_y >= TILE_SIZE) 
			tex_y = TILE_SIZE - 1;
		tex_pos += tex_step;
		color = get_pixel_color(data->texture[NORTH].img, wall.tex_col, tex_y);
		my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
		screen_y++;
	}
	draw_vertical_line(data, screen_x, wall.end, SCREEN_HEIGHT, FOREST_GREEN);
}
/*
void draw_textured_wall(t_mlx_data *data, t_ray ray, int screen_x)
{
	t_wall	wall;
	int		screen_y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	wall = init_wall(data, ray); // remplit .hit, .tex_col, .height, .begin, .end, .side

	// Calcule combien de pixels de texture on saute à chaque pixel à l'écran
	step = 1.0 * TILE_SIZE / wall.height;

	// Point de départ dans la texture (position verticale)
	tex_pos = (wall.begin - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;

	// Ciel
	draw_vertical_line(data, screen_x, 0, wall.begin, SKY_BLUE);

	// Texture du mur
	for (screen_y = wall.begin; screen_y < wall.end; screen_y++)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= TILE_SIZE)
			tex_y = TILE_SIZE - 1;

		tex_pos += step;

		color = get_pixel_color(data->texture[wall.side].img, wall.tex_col, tex_y);
		my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
	}

	// Sol
	draw_vertical_line(data, screen_x, wall.end, SCREEN_HEIGHT, FOREST_GREEN);
}


void	draw_textured_wall(t_mlx_data *data, t_ray ray, int screen_x)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;

	if (ray.perp_wall_dist < 0.001)
		ray.perp_wall_dist = 0.001;

	wall_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);

	draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;

	draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;

	// Point d’impact précis sur le mur (coordonnée entre 0 et 1)
	if (ray.side == VERTICAL)
		wall_x = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
	else // HORIZONTAL
		wall_x = data->player.pos.y + ray.perp_wall_dist * ray.dir.y;
	wall_x -= floor(wall_x);

	// Coordonnée de la colonne de texture
	tex_x = (int)(wall_x * TILE_SIZE);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= TILE_SIZE) tex_x = TILE_SIZE - 1;

	// Flip horizontal si nécessaire (corrigé selon tes defines)
	if (ray.side == HORIZONTAL && ray.dir.x > 0)
		tex_x = TILE_SIZE - tex_x - 1;
	if (ray.side == VERTICAL && ray.dir.y < 0)
		tex_x = TILE_SIZE - tex_x - 1;

	// Texture mapping
	double	step = 1.0 * TILE_SIZE / wall_height;
	double	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;

	// CIEL
	for (int y = 0; y < draw_start; y++)
		my_pixel_put(&data->framebuffer, screen_x, y, 0x87CEEB); // sky blue

	// MUR TEXTURÉ
	for (int y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)(tex_pos);
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= TILE_SIZE) tex_y = TILE_SIZE - 1;

		tex_pos += step;

		int color = get_pixel_color(data->texture[EAST].img, tex_x, tex_y); // ← remplace par la bonne direction
		my_pixel_put(&data->framebuffer, screen_x, y, color);
	}

	// SOL
	for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
		my_pixel_put(&data->framebuffer, screen_x, y, 0x228B22); // forest green
}

*/
