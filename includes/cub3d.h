/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 15:47:55 by sfournie         ###   ########.fr       */
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
# include	"mlx.h"
# include	"../libft/libft.h"

# define	WIN_W 1000
# define	WIN_H 500

typedef struct s_game	t_game;
typedef struct s_lvl	t_lvl;

typedef struct s_wall	t_wall;
typedef struct s_player	t_player;
typedef struct s_obj	t_obj;

typedef struct s_img	t_img;
typedef struct s_mlx	t_mlx;

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

struct t_player
{
	int	x;
	int	y;
	int	z;
};

struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		init;
};
#endif