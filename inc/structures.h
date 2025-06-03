/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:00 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 15:42:49 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	STRUCTURES_H

# define STRUCTURES_H

typedef struct	s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef	struct	s_int_vec
{
	int	x;
	int	y;
}	t_int_vec;

typedef struct	s_ray
{
	t_vector	dir;
	t_int_vec	map;
	t_vector	side_dist; // how far the ray need to travel right now to reach the next grid boundary ? Will be updated each time we move from one grid cell to another
	t_vector	delta_dist; //dist the ray travel to move from one grid line to the next parallel grid line in each direction, how for it must travel to cross one complete grid cell in each direction with this ray angle
	t_int_vec	step;
	double		perp_wall_dist; //to calculate how the perpendicular distance from the player to the wall that the ray hits
	bool		hit; //was there a wall ?
	int			side; //is it a NS or EW wall hit? Help to draw shadow
}	t_ray;

typedef struct	s_img
{
	void	*ptr;
	char	*pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_texture
{
	int		width;
	int		height;
	t_img	img;
}	t_texture;

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
	t_texture			texture[4];
	t_img				framebuffer;
	t_key				key;

}	t_mlx_data;

typedef struct	s_line
{
	t_int_vec	start;
	t_int_vec	end;
}	t_line;


#endif
