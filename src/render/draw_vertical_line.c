#include "../../inc/cub3D.h"

t_line	new_line(t_vector start, t_vector end)
{
	t_line line;

	line.start = start;
	line.end = end;
	return (line);
}

void	draw_wall(t_mlx_data data, int screen_x, t_wall wall)
{
	t_line	line;

	line = new_line(vec(screen_x, 0), vec(screen_x, wall.top);
	draw_ceiling(data, line, data.ceiling);
	line = new_line(vec(screen_x, wall.top), vec(screen_x, wall.bottom));
	draw_textured_wall();
	line = new_line(vec(screen_x, wall_bottom), vec(screen_x, SCREEN_HEIGHT - 1));
	draw_floor(data, line, data.floor);
}
