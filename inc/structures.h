/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:00 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 14:57:26 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	STRUCTURES_H

# define STRUCTURES_H

#define PRESSED 0
#define RELEASED 1

typedef struct	s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct	s_img
{
	void	*ptr;
	char	*pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_key;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		fov;
	double		plane_len;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_mlx_data
{
	void				*mlx;
	void				*win;
	char				**map;
	int					map_width;
	int					map_height;
	t_player			player;
	t_img				wall; //maybe need 4 type of wall + ceiling ? myabe make a texture struct ?
	t_img				floor;
	t_img				framebuffer;
	t_key				key;

}	t_mlx_data;

#endif
