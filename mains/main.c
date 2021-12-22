/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/22 17:45:37 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

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

int	change_player_pos(void)
{
	t_pos pos;
	t_pos new_pos;

	pos.x = g_game.player.pos.x;
	pos.y = g_game.player.pos.y;
	new_pos = move_pos(pos, g_game.player.rot, g_game.player.vel);
	printf("old : %d  new : %d", pos.x, new_pos.x);
	//if (!check_collision_x(new_pos.x, new_pos.y))
		g_game.player.pos.x = new_pos.x;
	//if (!check_collision_y(new_pos.x, new_pos.y))
		g_game.player.pos.y = new_pos.y;
	return (0);
}

void drawPlayer(t_mlx *mlx)
{
	int x;
	int y;
	
	if (g_game.player.vel)
		change_player_pos();
	x = g_game.player.pos.x;
	y = g_game.player.pos.y;
	while (y++ < (g_game.player.pos.y + 10))
	{
		x = g_game.player.pos.x;
		while (x++ < (g_game.player.pos.x + 10))
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
	while (index_y < (y + TILE_SIZE))
	{
		index_x = x;
		while (index_x < (x + TILE_SIZE))
		{
			my_mlx_pixel_put(mlx, index_x, index_y, WHITE);
			index_x++;
		}
		index_y++;
	}
}

void drawMap2D(t_mlx *mlx, t_map map)
{
	int x, y;
	for (y=0; y<map.height; y++)
	{
		for (x=0; x<map.width; x++)
		{
			if (map.map[y*map.width+x]==1)
			{
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
}

int display(void *ptr)
{
	static int	frame_timer;
	t_mlx mlx;

	if (frame_timer <= 0)
		frame_timer = 10000 / FPS;
	ptr = NULL;
	mlx = getmlx();
	mlx_clear_img(&mlx);
	drawMap2D(&mlx, g_game.map);
	drawPlayer(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	return (0);
}

int buttons_press(int key, t_mlx *mlx)
{
	mlx = NULL;
	printf("%d\n", key);
	if(key == A_KEY)
		g_game.player.rot -= TURN_SPEED;
	if(key == D_KEY)
		g_game.player.rot += TURN_SPEED;
	if(key == W_KEY)
		g_game.player.vel = SPEED;
	if(key == S_KEY)
		g_game.player.vel = -SPEED;
	return (0);
}

int buttons_release(int key, t_mlx *mlx)
{
	mlx = NULL;
	if(key == W_KEY)
		g_game.player.vel = 0;
	if(key == S_KEY)
		g_game.player.vel = 0;
	if (key == ESC)
		exit(0);
	return (0);
}

int	*copy_map(int *src, int size)
{
	int	*map;
	int	i;

	map = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		map[i] = src[i];
		i++;
	}
	return (map);
}

void init()
{
	int map[64] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	g_game.player.pos.x = 51;
	g_game.player.pos.y = 51;
	g_game.player.rot = 90;
	g_game.player.hp = 100;
	g_game.map.width = 8;
	g_game.map.height = 8;
	g_game.map.map = copy_map(map, 64);
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