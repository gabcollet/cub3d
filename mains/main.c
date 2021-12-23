/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/23 13:30:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

void drawPlayer(t_mlx *mlx)
{
	int x;
	int y;
	
	if (g_game.player.vel)
		change_player_pos(&g_game.player);
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

void drawTile(t_mlx *mlx, int x, int y, int type)
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
			if (index_y % 50 == 0 || index_x % 50 == 0)
				my_mlx_pixel_put(mlx, index_x, index_y, RED);
			else if (type == WALL)
				my_mlx_pixel_put(mlx, index_x, index_y, WHITE);
			else if (type == PLAYER)
				my_mlx_pixel_put(mlx, index_x, index_y, 0x000040);
			index_x++;
		}
		index_y++;
	}
}

void drawMap2D(t_mlx *mlx, t_map map)
{
	int 	x, y;
	t_pos	p_pos;

	p_pos = g_game.player.pos;
	for (y=0; y<map.height; y++)
	{
		for (x=0; x<map.width; x++)
		{
			if (map.map[y*map.width+x]==1)
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, WALL);
			else if (x==(int)p_pos.x / TILE_SIZE && y==(int)p_pos.y / TILE_SIZE)
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, PLAYER);
			else
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, FLOOR);
		}
	}
}

int display(void *ptr)
{
	static int	frame_timer;
	t_mlx *mlx;

	if (frame_timer <= 0)
	{
		//frame_timer = MLX_CD / FPS;
		//mouse_handler(0, 0);
		ptr = NULL;
		mlx = get_mlx();
		mlx_clear_img(mlx);
		drawMap2D(mlx, g_game.map);
		drawPlayer(mlx);
		raycast_draw_all(g_game.player.pos, g_game.player.rot, 800, VIEW);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	}
	else
		frame_timer--;
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
	g_game.player.pos.x = 221;
	g_game.player.pos.y = 221;
	g_game.player.rot = 0;
	g_game.player.hp = 100;
	g_game.map.width = 8;
	g_game.map.height = 8;
	g_game.map.map = copy_map(map, 64);
	g_game.mlx = get_mlx();
	mlx_get_screen_size(g_game.mlx->mlx, &g_game.screen_x, &g_game.screen_y);
	mlx_mouse_hide(g_game.mlx->mlx, g_game.mlx->win);
}

int main(void)
{
	t_mlx *mlx;

	mlx = get_mlx();
	init();
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	//mlx_hook(mlx->win, 6, 1L<<6, mouse_move, mlx);
	//mlx_mouse_hook(mlx->win, mouse_handler, NULL);
	mlx_loop_hook(mlx->mlx, display, mlx);
	//mlx_key_hook(mlx.win, buttons, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}