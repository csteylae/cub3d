/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:00 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/09 15:55:43 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_int_vec
{
	int	x;
	int	y;
}	t_int_vec;

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

typedef struct s_ray
{
	t_vector	dir;
	t_int_vec	map;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_int_vec	step;
	double		perp_wall_dist;
	bool		hit;
	int			side;
}	t_ray;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_key;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		plane_len;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_wall
{
	int		height;
	int		top;
	int		bottom;
	int		side;
	double	hit;
	int		tex_col;
}	t_wall;

typedef struct s_img
{
	void	*ptr;
	char	*pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	char	*path;
	int		width;
	int		height;
	t_img	img;
}	t_texture;

typedef struct s_line
{
	t_int_vec	start;
	t_int_vec	end;
}	t_line;

/*______________RACHEL______________*/
typedef struct s_data
{
	int		fd;
	int		cnt;
	char	**entire_fd;
	char	*trimmed;
	char	*texture[4];
	char	*txt_path;
	int		check_floor_color;
	int		check_ceiling_color;
	int		floor_color;
	int		ceiling_color;
	int		comma_cnt;
	char	**rgb;
	char	**cleaned;
	int		r;
	int		g;
	int		b;
	int		cnt_map_lines;
	char	**map;
	char	**map_copy;
}	t_data;

typedef struct s_mlx_data
{
	void				*mlx;
	void				*win;
	char				**map;
	t_player			player;
	t_texture			texture[4];
	t_img				framebuffer;
	t_key				key;
	int					ceiling;
	int					floor;
	t_data				*game;
}	t_mlx_data;

#endif
