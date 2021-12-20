/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/20 15:54:36 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pour compiler : gcc -lmlx -framework OpenGL -framework AppKit main.c
#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

# define ESC 			53
# define SPACE_KEY 		49
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define SPEED			3.0
# define TILESET		50

# define WHITE			0xffffff
# define BLACK			0
# define YELLOW			0xf0de18

int mapX = 8, mapY = 8, mapS = 64;
int map[] = 
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

float px, py; //player position
float vx_a, vx_d, vy_w, vy_s; //velocity

t_mlx	getmlx()
{
	static t_mlx mlx;
	
	if (mlx.init != 1)
	{
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
		mlx.img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
		mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp,
					&mlx.img.line_length, &mlx.img.endian);
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
		dst = mlx->img.addr + (i * (mlx->img.bpp / 8));
		*(unsigned int*)dst = 0;
		i++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT)
		return ;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bpp / 8));
	*(unsigned int*)dst = color;
}

int	check_collision_x(int plyr_x, int plyr_y)
{
	if (plyr_x / TILESET > mapX || map[plyr_x / TILESET + plyr_y / TILESET * mapX] == 1)
		return (1);
	if ((plyr_x + 10) / TILESET > mapX || map[(plyr_x + 10) / TILESET + plyr_y / TILESET * mapX] == 1)
		return (1);
	if ((plyr_x) / TILESET > mapX || map[(plyr_x) / TILESET + (plyr_y + 10) / TILESET * mapX] == 1)
		return (1);
	if ((plyr_x + 10) / TILESET > mapX || map[(plyr_x + 10) / TILESET + (plyr_y + 10) / TILESET * mapX] == 1)
		return (1);
	return (0);
}
int	check_collision_y(int plyr_x, int plyr_y)
{
	if (plyr_y / TILESET > mapY || map[plyr_x / TILESET + plyr_y / TILESET * mapY] == 1)
		return (1);
	if ((plyr_y + 10) / TILESET > mapY || map[plyr_x / TILESET + (plyr_y + 10) / TILESET * mapY] == 1)
		return (1);
	if ((plyr_y) / TILESET > mapY || map[(plyr_x + 10) / TILESET + (plyr_y) / TILESET * mapY] == 1)
		return (1);
	if ((plyr_y + 10) / TILESET > mapY || map[(plyr_x + 10) / TILESET + (plyr_y + 10) / TILESET * mapY] == 1)
		return (1);
	return (0);
}

int	change_player_pos(void)
{
	if (!check_collision_x(px + vx_a + vx_d, py))
		px += vx_a + vx_d;
	if (!check_collision_y(px, py + vy_w + vy_s))
		py += vy_w + vy_s;
	return (1);
}

void drawPlayer(t_mlx *mlx)
{
	int x;
	int y;
	
	change_player_pos();
	x = px;
	y = py;
	while (y++ < (py + 10))
	{
		x = px;
		while (x++ < (px + 10))
		{
			my_mlx_pixel_put(mlx, x, y, YELLOW);
		}
	}
}

void drawTile(t_mlx *mlx, int x, int y)
{
	int	index_x;
	int index_y;

	index_x = x;
	index_y = y;
	while (index_y < (y + TILESET))
	{
		index_x = x;
		while (index_x < (x + TILESET))
		{
			my_mlx_pixel_put(mlx, index_x, index_y, WHITE);
			index_x++;
		}
		index_y++;
	}
}

void drawMap2D(t_mlx *mlx)
{
	int x, y;
	for (y=0; y<mapY; y++)
	{
		for (x=0; x<mapX; x++)
		{
			if (map[y*mapX+x]==1)
			{
				drawTile(mlx, x * TILESET, y * TILESET);
			}
		}
	}
}

int display(void *ptr)
{
	t_mlx mlx;

	ptr = NULL;
	mlx = getmlx();
	mlx_clear_img(&mlx);
	drawMap2D(&mlx);
	drawPlayer(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	return (0);
}

int buttons_press(int key, t_mlx *mlx)
{
	mlx = NULL;
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
	mlx = NULL;
	if(key == A_KEY)
		vx_a = 0;
	if(key == D_KEY)
		vx_d = 0;
	if(key == W_KEY)
		vy_w = 0;
	if(key == S_KEY)
		vy_s = 0;
	if (key == ESC)
		exit(0);
	return (0);
}

void init()
{
	px = 51; py = 51;
}

int main(void)
{
	t_mlx mlx;

	mlx = getmlx();
	init();
	mlx_hook(mlx.win, 2, 1L<<0, buttons_press, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, buttons_release, &mlx);
	mlx_loop_hook(mlx.mlx, display, &mlx);
	//mlx_key_hook(mlx.win, buttons, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}