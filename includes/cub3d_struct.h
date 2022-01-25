/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/24 18:32:27 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# define UI_ELEMS	2
# define MAX_ENEMY	300
# define MAX_DOOR	200

/* Typedefs */
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_game	t_game;
typedef struct s_map	t_map;

typedef struct s_obj_draw	t_obj_draw;
typedef struct s_wall	t_wall;
typedef struct s_player	t_plyr;

typedef struct s_coll	t_coll;

typedef struct s_pos	t_pos;
typedef struct s_size	t_size;

typedef struct s_rgb	t_rgb;

/* Enums definition*/
enum e_obj_type
{
	WALL = 0,
	PLAYER,
	FLOOR,
	CEILING
};

enum e_dir
{
	NORTH = 1,
	SOUTH = 2,
	WEST = 4,
	EAST = 8
};

enum e_sprite
{
	NO = 0,
	SO,
	WE,
	EA,
	NW,
	NE,
	SW,
	SE
};

/* Structures definition */
struct s_pos
{
	double	x;
	double	y;
	double	z;
};

struct s_size
{
	double	x;
	double	y;
	double	z;
};

struct s_rgb
{
	int		r;
	int		g;
	int		b;
};

struct s_coll
{
	t_pos	pos;
	int		type;
	int		dir;
};

struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		width;
	int		endian;
	int		height;
};

struct s_vect
{
	double	x;
	double	y;
	double	z;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		init;
};

struct s_map
{
	t_img	back;
	int		width;
	int		height;
	char	*tiles;
	int		*tiles_coll;
	int		size;
	int		floor_c;
	int		ceiling_c;
};

struct s_obj_draw
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
};

struct s_player
{
	t_pos	pos;
	double	rot;
	double	vel_r;
	double	vel_l;
	double	vel_u;
	double	vel_d;
	double	turn_l;
	double	turn_r;
};

struct s_game
{
	t_map		map;
	t_plyr		player;
	t_mlx		*mlx;
	t_img		game_img;
	t_img		minimap;
	t_img		texture[4];
	int			res_w;
	int			res_h;
};

t_game					g_game;

#endif