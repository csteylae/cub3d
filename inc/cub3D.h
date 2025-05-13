/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:03:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 16:18:08 by csteylae         ###   ########.fr       */
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

#define PI 3.14159265358979323846
#define RED 0xff0000
#define ROT_SPEED 0.1

#define TILE_SIZE 64

/*_______INIT______________*/
t_mlx_data	init_data(void);
t_player	init_player(t_mlx_data *data);

/*_______EVENT_____________*/
int		close_cub3D(t_mlx_data *data);
int		key_press(int keysym, t_mlx_data *data);
int		key_release(int keysym, t_mlx_data *data);

/*_______IMAGE RENDERING */ 
void	my_pixel_put(t_img *img, int x, int y, int color);
void	ft_clear_image(t_mlx_data *data);
int		render_frame(t_mlx_data *data);

/*_______MINIMAP___________*/
void	init_minimap(t_mlx_data *data);
void	draw_map(t_mlx_data *data);
bool	is_inside_image(t_mlx_data *data, int x, int y);
void	draw_player(t_mlx_data *data);

/*______MOVEMENT__________*/
void	update_position(t_mlx_data *data, t_player *player);

/*_______ERROR_____________*/
void	put_error(char *error_msg, t_mlx_data *data);


t_vector	vec(double x, double y);
t_vector	get_plane(t_vector dir, double plane_len);

#endif 
