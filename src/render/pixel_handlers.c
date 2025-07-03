/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:09:02 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/03 11:09:08 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	get_pixel_color(t_img img, int x, int y)
{
	char	*pixel;

	pixel = img.pixel_addr + (y * img.line_len) + (x * (img.bpp / 8));
	return (*(int *)pixel);
}

void	ft_clear_image(t_mlx_data *data)
{
	int	total_bytes;

	total_bytes = SCREEN_HEIGHT * data->framebuffer.line_len;
	ft_memset(data->framebuffer.pixel_addr, 0, total_bytes);
}

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
