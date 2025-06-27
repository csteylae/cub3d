#include "../../../inc/cub3D.h"

void    init_game_struct(t_data *game)
{
    game->texture[0] = NULL;
    game->texture[1] = NULL;
    game->texture[2] = NULL;
    game->texture[3] = NULL;
    game->check_floor_color = 0;
    game->check_ceiling_color = 0;
    game->map = NULL;
}
