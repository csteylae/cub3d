#include "../../inc/cub3D.h"

static void	apply_2d_rotation_matrix(t_vector *vector, double angle)
{
	t_vector	prev;

	prev = *vector;
	vector->x = prev.x * cos(angle) - prev.y * sin(angle);
	vector->y = prev.x * sin(angle) + prev.y * cos(angle);
}

void	rotate(t_player *player, double angle)
{
	apply_2d_rotation_matrix(&player->dir, angle);
	apply_2d_rotation_matrix(&player->plane, angle);
}
