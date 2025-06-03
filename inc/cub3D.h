/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:03:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 15:41:37 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdbool.h>

#include "structures.h"
#include "../lib/libft/libft.h"
#include "../minilibx-linux/mlx.h"

#define EPSILON 1e-10 //define "close enough to 0" for floating point comparison
#define SAFE_LARGE_VALUE 1e30
#define RED 0xff0000
#define ROT_SPEED 0.1

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 64
#define HORIZONTAL 0
#define VERTICAL 1

#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define YELLOW 0xffff00

/*_______INIT______________*/
t_mlx_data	init_data(void);
t_player	init_player(t_mlx_data *data);
void		init_texture(t_mlx_data *data);

/*_______EVENT_____________*/
int		close_cub3D(t_mlx_data *data);
int		key_press(int keysym, t_mlx_data *data);
int		key_release(int keysym, t_mlx_data *data);

/*_______IMAGE RENDERING */ 
void	my_pixel_put(t_img *img, int x, int y, int color);
void	ft_clear_image(t_mlx_data *data);
int		render_frame(t_mlx_data *data);
//void	draw_wall_column(t_mlx_data *data, int screen_x, int wall_start, int wall_end);

void	draw_wall_column(t_mlx_data *data, t_line wall, int color);

/*_______MINIMAP___________*/
void	init_minimap(t_mlx_data *data);
void	draw_map(t_mlx_data *data);
bool	is_inside_image(t_mlx_data *data, int x, int y);
void	draw_player(t_mlx_data *data);

/*______MOVEMENT__________*/
void	update_position(t_mlx_data *data, t_player *player);
t_vector	get_perpendicular_plane(t_vector dir, double plane_len);

/*______RAYCASTING_______*/
t_vector calculate_ray_dir(t_mlx_data *data, t_player *player, int screen_x, int screen_width);
void	initialize_dda(t_player *player, t_ray *ray);
void	cast_ray(t_mlx_data *data);
void	perform_dda(t_mlx_data *data, t_ray *ray);

/*_______ERROR_____________*/
void	put_error(char *error_msg, t_mlx_data *data);

/*_______UTILS_____________*/
t_vector	vec(double x, double y);
t_vector	get_plane(t_vector dir, double plane_len);
void		draw_line(t_mlx_data *data, t_line line, int color);

#endif 
