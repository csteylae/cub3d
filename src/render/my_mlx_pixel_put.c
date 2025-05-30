/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:15:11 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 18:26:46 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static bool	is_inside_window(int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return (false);
	return (true);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (!is_inside_window(x, y))
		return ;
	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_addr)) = color;
}
