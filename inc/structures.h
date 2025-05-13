/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:00 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 17:47:57 by csteylae         ###   ########.fr       */
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

/*
typedef struct s_pos
{
	double		x;
	double	 	y;
	double		rot_angle;
}	t_pos;
*/

typedef struct	s_minimap_square
{
	t_vector	pos; // player position
	t_vector	dir; // (0,1) = S; (0,-1) = N ; (1,0) = E ; (0,-1) = E  
	t_vector	plane; //should be perpendicular to dir. Its length dependt on fov 
	double		fov_rad;
	double		plane_len; // defini l'étendue de ce que voit le joueur. Utilisé pour calculer les rayons
	int			color;
	int			size;
}	t_minimap_square;

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
	t_img		img;
}	t_player;

typedef struct s_mlx_data
{
	void				*mlx;
	void				*win;
	char				**map;
	int					map_width;
	int					map_height;
	t_minimap_square	square;
	t_player			player;
	t_img				wall;
	t_img				floor;
	t_img				framebuffer;
	t_key				key;

}	t_mlx_data;

#endif
