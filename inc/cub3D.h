/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:03:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 18:26:24 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

#include "structures.h"
#include "../lib/libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 1000

#define RED 0xff0000

/*_______INIT______________*/
t_mlx_data	init_data(void);

/*_______EVENT_____________*/

int		close_cub3D(t_mlx_data *data);
int		key_press(int keysym, t_mlx_data *data);
int		key_release(int keysym, t_mlx_data *data);

/*_______IMAGE HANDLING______*/
void	my_pixel_put(t_img *img, int x, int y, int color);
void	ft_clear_image(t_mlx_data *data);
void	draw_square(t_mlx_data *data, t_square square);
int		render_frame(t_mlx_data *data);
#endif 
