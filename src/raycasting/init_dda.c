#include"../../inc/cub3D.h"

t_vector	calculate_ray_dir(t_player *player, int screen_x, int screen_width)
{
	//the camera_x maps the entire screen of the player view defined by plane vector on a value comprised between -1 and 1
	//a way to map the horizontal position on the screen yo a direction within the fov
	double		camera_x; // rpz a position inside the camera_plane (plane vector),so its like a horizontal coord on that camera/screen
	t_vector	ray_dir;
	
	camera_x = 2.0 * screen_x / (double)screen_width - 1.0; //its val is comprised between -1 (left corner of the camera plane vect) and 1 (right side) 0 is the center of the camera plane
	ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray_dir.y = player->dir.y + player->plane.y *camera_x;
	return (ray_dir);
}

static t_vector	get_delta_dist(t_vector raydir)
{
	//delta_dist = the distance for the angle of the ray to traverse one grid cell
	t_vector	delta_dist;

	if (raydir.x == 0) // if the ray is perfectly vertical we need to handle div by 0 by setting a very high value
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1.0 / raydir.x);
	if (raydir.y == 0) //same check if the ray is perfectly horizontal
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1.0 / raydir.y);
	return (delta_dist);
}

static t_vector get_side_dist(t_ray *ray, t_vector player_pos)
{
	//the distance between the actual player_position from the next grid cell
	//we need to know in wich direction the ray is going (left of right? up or down?)
	//side dist will be incremented each iteration by delta_dist until a wall cell is found. 
	t_vector	side_dist;

	if (ray->dir.x < 0) //move to the previous left grid
		side_dist.x = (player_pos.x - ray->map.x) * ray->delta_dist.x;
	else
		side_dist.x = ((ray->map.x + 1.0) - player_pos.x) * ray->delta_dist.x;
	if (ray->dir.y < 0) //if raydir is going up
		side_dist.y = (player_pos.y - ray->map.y) * ray->delta_dist.y;
	else
		side_dist.y = ((ray->map.y + 1.0) - player_pos.y) * ray->delta_dist.y;
	return (side_dist);
}

static t_int_vec	get_step_dir(t_vector raydir)
{
	t_int_vec	step;

	if (raydir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (raydir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

void	initialize_dda(t_player *player, t_ray *ray)
{
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->step = get_step_dir(ray->dir);
	ray->delta_dist = get_delta_dist(ray->dir);
	ray->side_dist = get_side_dist(ray, player->pos);
	ray->hit = false;

}
