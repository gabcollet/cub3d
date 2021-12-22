/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/22 17:46:23 by gcollet          ###   ########.fr       */
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

# define ESC 			65307
# define SPACE_KEY 		49
# define W_KEY			119
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100
# define SPEED			3.0
# define TURN_SPEED		 1
# define TILE_SIZE		50

# define WHITE			0xffffff
# define BLACK			0
# define YELLOW			0xf0de18



typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_game	t_game;
typedef struct s_map	t_map;

typedef struct s_wall	t_wall;
typedef struct s_player	t_player;
typedef struct s_obj	t_obj;

typedef struct s_vect	t_vect;

typedef struct s_pos	t_pos;
typedef struct s_size	t_size;

typedef struct s_rgb	t_rgb;

struct s_pos
{
	float	x;
	float	y;
	float	z;
};

struct s_size
{
	float	x;
	float	y;
	float	z;
};

struct s_rgb
{
	int	r;
	int	g;
	int	b;
};

struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
};

struct s_vect
{
	float	x;
	float	y;
	float	z;
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
	int *map;
};

struct s_obj
{

};

struct s_player
{
	t_pos	pos;
	int		hp;
	int		rot;
	int		vel;
};

struct s_game
{
	t_map		map;
	t_player	player;
	t_mlx		*mlx;
};

t_game	g_game;

/* Generic structure creator */
t_pos		new_pos(int x, int y, int z);
t_size		new_size(int x, int y, int z);
t_vect		new_vect(int x, int y, int z);

/* Image and draw functions */
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	mlx_clear_img(t_mlx *mlx);
int 	raycast_draw(t_pos pos, float rot, int dist);

/* Position and movement */
t_pos	move_pos(t_pos pos, float rot, float dist);

/* Collision */
int	check_collision_y(int plyr_x, int plyr_y);
int	check_collision_x(int plyr_x, int plyr_y);

#endif