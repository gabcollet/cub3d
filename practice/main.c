/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/20 14:18:11 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pour compiler : gcc -lmlx -framework OpenGL -framework AppKit main.c
#define WIDTH 1000
#define HEIGHT 500

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		init;
	void	*win;
}				t_mlx;

# define ESC 			53
# define SPACE_KEY 		49
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define SPEED			3.0

float px, py; //player position
float vx_a, vx_d, vy_w, vy_s; //velocity

t_mlx	getmlx()
{
	static t_mlx mlx;
	
	if (mlx.init != 1)
	{
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
		mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
		mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
					&mlx.line_length, &mlx.endian);
		mlx.init = 1;
	}
	return(mlx);
}

void	mlx_clear_img(t_mlx *mlx)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		dst = mlx->addr + (i * (mlx->bits_per_pixel / 8));
		*(unsigned int*)dst = 0;
		i++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void drawPlayer(t_mlx *mlx)
{
	int x;
	int y;
	
	px += vx_a + vx_d;
	py += vy_w + vy_s;
	x = px;
	y = py;
	while (y++ < (py + 10))
	{
		x = px;
		while (x++ < (px + 10))
		{
			my_mlx_pixel_put(mlx, x, y, 0xf0de18);	
		}
	}
}

void display()
{
	t_mlx mlx;

	mlx = getmlx();
	mlx_clear_img(&mlx);
	drawPlayer(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}

int buttons_press(int key, t_mlx *mlx)
{
	if(key == A_KEY)
		vx_a = -SPEED;
	if(key == D_KEY)
		vx_d = SPEED;
	if(key == W_KEY)
		vy_w = -SPEED;
	if(key == S_KEY)
		vy_s = SPEED;
	return (0);
}

int buttons_release(int key, t_mlx *mlx)
{
	if(key == A_KEY)
		vx_a = 0;
	if(key == D_KEY)
		vx_d = 0;
	if(key == W_KEY)
		vy_w = 0;
	if(key == S_KEY)
		vy_s = 0;
	return (0);
}

void init()
{
	px = 0; py = 0;
}


int main(int ac, char **av)
{
	t_mlx mlx;

	mlx = getmlx();
	init();
	mlx_hook(mlx.win, 2, 1L<<0, buttons_press, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, buttons_release, &mlx);
	mlx_loop_hook(mlx.mlx, display, &mlx);
	//mlx_key_hook(mlx.win, buttons, &mlx);
	mlx_loop(mlx.mlx);
}