/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/21 14:57:42 by fousse           ###   ########.fr       */
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

# define	WIN_W 1000
# define	WIN_H 500

typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_game	t_game;
typedef struct s_lvl	t_lvl;

typedef struct s_wall	t_wall;
typedef struct s_player	t_player;
typedef struct s_obj	t_obj;

typedef struct s_vect3d	t_vect3d;

typedef struct s_pos	t_pos;
typedef struct s_size	t_size;

typedef struct s_rgb	t_rgb;

struct s_pos
{
	int	x;
	int	y;
	int	z;
};

struct s_size
{
	int	x;
	int	y;
	int	z;
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

struct s_vect3d
{
	int	x;
	int	y;
	int	z;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		init;
};

struct s_game
{
	t_lvl	*cur_lvl;
};

struct s_lvl
{
	int	*map;
	int	width;
	int	height;
};

struct s_obj
{

};

struct s_player
{
	t_pos	pos;
	int		hp;

};

/* Generic structure creator */
t_pos		new_pos(int x, int y, int z);
t_size		new_size(int x, int y, int z);
t_vect3d	new_vect3d(int x, int y, int z);


#endif