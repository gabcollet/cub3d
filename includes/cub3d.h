/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/01 20:27:13 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include	<stdarg.h>
# include	<stdio.h>
# include	<limits.h>
# include	<stddef.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<math.h>
# include	<complex.h>
# include	<mlx.h>
# include	"../libft/libft.h"

# define WIN_W 		1000
# define WIN_H		500
# define FPS		30
# define MLX_CD		10000

/* Key for linux */
# define ESC 			65307
# define SPACE_KEY 		49
# define W_KEY			119
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100
# define RIGHT_KEY		65363
# define LEFT_KEY		65361

/* Game parameter */
# define SPEED			2
# define TURN_SPEED		2.5
# define MOUSE_TURN		0.1
# define VIEW_ANGLE		60
# define VIEW_DIST		1000
# define TILE_SIZE		50
# define MINI_TILE_S	10

/* Sprites */
# define SPRITE_AMNT	4

/* Colors */
# define WHITE			0xffffff
# define BLACK			0x000000
# define RED			0xFF0000
# define FLOOR_C		0x303030
# define CEILING_C		0x909090
# define NORTH_C		0x00aa50
# define SOUTH_C		0x005090
# define WEST_C			0x0020bb
# define EAST_C			0x0000ff
# define YELLOW			0xf0de18

/* Parse errors */
# define ERR_FILE		1
# define ERR_MAPC		2
# define ERR_WALL		3
# define ERR_SPACE		4
# define ERR_PLAYER		5

typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_game	t_game;
typedef struct s_map	t_map;

typedef struct s_wall	t_wall;
typedef struct s_player	t_player;
typedef struct s_cam	t_cam;
typedef struct s_obj	t_obj;

typedef struct s_vect	t_vect;

typedef struct s_coll	t_coll;

typedef struct s_pos	t_pos;
typedef struct s_size	t_size;

typedef struct s_rgb	t_rgb;

enum e_obj_type
{
	WALL,
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
};

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
	int	r;
	int	g;
	int	b;
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
	int	width;
	int	height;
	int *tiles;
	int *tiles_coll;
	int size;
};

struct s_obj
{

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
	double	turn_l;
	double	turn_r;
};

struct s_game
{
	t_map		map;
	t_player	player;
	t_mlx		*mlx;
	t_img		minimap;
	int			screen_x;
	int			screen_y;
};

t_game	g_game;

/* Generic structure creator */
t_pos	new_pos(double x, double y, double z);
t_size	new_size(double x, double y, double z);
t_vect	new_vect(double x, double y, double z);
t_coll	new_collider(t_pos pos, int type, int dir);

/* MLX */
t_mlx	*get_mlx(void);

/* Game management */
void	init_game(t_game *game);
void	exit_game(t_game *game, int exit_code);

/* Map management */
int		*copy_map(int *src, int size);

/* Image and draw */
void	my_mlx_pixel_put(t_img img, int x, int y, int color);
void	mlx_clear_img(t_img img);
int 	raycast_draw(t_pos pos, double rot, double dist);
int 	raycast_draw_all(t_pos pos, double rot, double view);
void	drawMap3D(t_mlx *mlx, t_map map);
void	draw_background(t_img img);

/* Color */
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
t_rgb	color_int_to_rgb(int color);
int		color_rgb_to_int(t_rgb rgb);
t_rgb	color_shift_rgb(t_rgb base, t_rgb shift, double force);
int		color_shift_int(int base, int shift, double force);

/* Inputs */
int		key_press(int key, t_mlx *mlx);
int		key_release(int key, t_mlx *mlx);
int		mouse_handler(int x, int y);
int		mouse_move(int x, int y, t_mlx *mlx);
int 	quit_handler(void);

/* Position and movement */
t_pos	move_pos(t_pos pos, double rot, double dist, int dir);
int		rotate_player(t_player *player, double rot);
int		change_player_pos(t_player *player, double vel, int dir);

/* Collision and intersection */
int		check_collision(int x, int y, int size, int map);
t_coll	check_intersections(int x, int y, double rot);
t_coll	check_dir(t_pos inter_y, t_pos inter_x, int side, double rot);

/* Math */
double	deg_to_rad(double angle);
double	get_draw_distance(t_pos pos, double rot, t_pos pixel);

#endif