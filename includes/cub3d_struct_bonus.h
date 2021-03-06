/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/30 18:05:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_BONUS_H
# define CUB3D_STRUCT_BONUS_H

# define UI_ELEMS	2
# define MAX_ENEMY	300
# define MAX_DOOR	200

/* Typedefs */
typedef struct s_mlx		t_mlx;
typedef struct s_img		t_img;

typedef struct s_game		t_game;
typedef struct s_map		t_map;

typedef struct s_obj		t_obj;
typedef struct s_obj_draw	t_obj_d;
typedef struct s_wall		t_wall;
typedef struct s_door		t_door;
typedef struct s_player		t_plyr;
typedef struct s_sprite		t_sprite;

typedef struct s_vect		t_vect;

typedef struct s_coll		t_coll;

typedef struct s_pos		t_pos;
typedef struct s_size		t_size;

typedef struct s_rgb		t_rgb;

/* Enums definition*/
enum e_obj_type
{
	WALL = 0,
	PLAYER,
	FLOOR,
	CEILING,
	UI,
	ENEMY,
	DOOR
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

enum e_ui_elem
{
	UI_GUN = 0,
	UI_FACE,
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
	t_obj	*obj;
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

struct s_sprite
{
	int		active;
	t_img	frames[20];
	int		frames_n;
	double	anim_countdown;
	double	anim_time;
	int		playing;
	int		loop;
	double	scaling;
	double	scaled_width;
	double	i_x;
	double	x_step;
	int		drawing;
	int		rewind;
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

struct s_obj
{
	int			type;
	t_pos		pos;
	t_sprite	sprite;
	float		dist;
	float		dist_side;
	double		rot;
	double		rot_side;
	int			visible;
	int			alive;
	void		(*update)(t_obj *obj);
};

struct s_obj_draw
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
};

struct s_door
{
	t_pos		pos;
	t_sprite	sprite;
	float		dist;
	float		dist_side;
	double		face_rot;
	double		rot;
	double		rot_side;
	int			visible;
	int			tile_i;
	int			opened;
};

struct s_player
{
	t_pos	pos;
	int		hp;
	double	rot;
	double	vel_r;
	double	vel_l;
	double	vel_u;
	double	vel_d;
	double	vel_z;
	double	gravity;
	double	turn_l;
	double	turn_r;
};

struct s_game
{
	t_map		map;
	t_plyr		player;
	t_mlx		*mlx;
	t_img		game_img;
	t_door		doors[MAX_DOOR];
	int			door_count;
	t_img		minimap;
	t_img		texture[4];
	t_obj		ui_elems[UI_ELEMS];
	t_obj		enemies[MAX_ENEMY];
	int			enemy_count;
	int			res_w;
	int			res_h;
	int			toggle_map;
	int			mouse_x;
	int			mouse_y;
};

#endif