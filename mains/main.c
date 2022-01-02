/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/01 20:34:58 by fousse           ###   ########.fr       */
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
	
	if (g_game.player.vel_u + g_game.player.vel_d)
		change_player_pos(&g_game.player, g_game.player.vel_u + g_game.player.vel_d, 0);
	if (g_game.player.vel_r + g_game.player.vel_l)
		change_player_pos(&g_game.player, g_game.player.vel_r + g_game.player.vel_l, 1);
	if (g_game.player.turn_l + g_game.player.turn_r)
		rotate_player(&g_game.player, g_game.player.turn_l + g_game.player.turn_r);
	x = g_game.player.pos.x;
	y = g_game.player.pos.y;
	while (y++ < (g_game.player.pos.y + 10))
	{
		x = g_game.player.pos.x;
		while (x++ < (g_game.player.pos.x + 10))
		{
			my_mlx_pixel_put(mlx->img, x, y, YELLOW);
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
				my_mlx_pixel_put(mlx->img, index_x, index_y, RED);
			else if (type == WALL)
				my_mlx_pixel_put(mlx->img, index_x, index_y, WHITE);
			else if (type == PLAYER)
				my_mlx_pixel_put(mlx->img, index_x, index_y, 0x000040);
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
			if (map.tiles[y*map.width+x]==1)
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
	float	dist;

	mlx = (t_mlx *)ptr;
	if (frame_timer <= 0)
	{
		//frame_timer = MLX_CD / FPS;
		//mouse_handler(0, 0);
		mlx_clear_img(mlx->img);
		draw_background(mlx->img);
		//drawMap2D(mlx, g_game.map);
		drawPlayer(mlx); //on pogne dans les coins parce que la colision du player est trop large
		
		raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	}
	else
		frame_timer--;
	return (0);
}

int main(void)
{
	t_mlx *mlx;

	mlx = get_mlx();
	init_game(&g_game);
	//h.sheet.img = mlx_xpm_file_to_image(h.mlx.mlx, "sheetmegaman.xpm", &h.sheet.x_len, &h.sheet.y_len);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook(mlx->mlx, display, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}