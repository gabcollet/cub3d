/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/06 17:52:45 by fousse           ###   ########.fr       */
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
	
	int	i;
	
	if (g_game.player.vel_u + g_game.player.vel_d)
		change_player_pos(&g_game.player, g_game.player.vel_u + g_game.player.vel_d, 0);
	if (g_game.player.vel_r + g_game.player.vel_l)
		change_player_pos(&g_game.player, g_game.player.vel_r + g_game.player.vel_l, 1);
	if (g_game.player.turn_l + g_game.player.turn_r)
		rotate_player(&g_game.player, g_game.player.turn_l + g_game.player.turn_r);
	x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) - 1;
	y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S) - 1;
	/*while (y++ < g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S) + 1)
	{
		x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) - 1;
		while (x++ < g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) + 1)
		{
			my_mlx_pixel_put(mlx->img, x , y, RED);
		}
	}*/

	// Ça ça doit pas rester là
	t_pos	facing;
	facing.x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S);
	facing.y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S);
	i = -(VIEW_ANGLE / 2);
	while(i <= VIEW_ANGLE / 2)
	{
		raycast_draw(facing, g_game.player.rot - i, 10, RED);
		i += 3;
	}
	
}

void drawTile(t_mlx *mlx, int x, int y, int type)
{
	int	index_x;
	int index_y;

	index_x = x;
	index_y = y;
	while (index_y < (y + MINI_TILE_S))
	{
		index_x = x;
		while (index_x < (x + MINI_TILE_S))
		{
			/*if (index_y % MINI_TILE_S == 0 || index_x % MINI_TILE_S == 0)
				my_mlx_pixel_put(mlx->img, index_x, index_y, RED);*/
			if (type == WALL)
				my_mlx_pixel_put(mlx->img, index_x, index_y, 0);
			else if (type == FLOOR)
				my_mlx_pixel_put(mlx->img, index_x, index_y, WHITE);
			else if (type == PLAYER)
				my_mlx_pixel_put(mlx->img, index_x, index_y, RED);
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
	for (y = 0; y<map.height; y++)
	{
		for (x = 0; x<map.width; x++)
		{
			if (map.tiles[y * map.width + x] == M_WALL || map.tiles[y * map.width + x] == M_EMPTY)
				drawTile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else
				drawTile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, FLOOR);
			//else if (x==(int)p_pos.x / TILE_SIZE && y==(int)p_pos.y / TILE_SIZE)
				//drawTile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, PLAYER);
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
		mouse_handler(0, 0);
		mlx_clear_img(mlx->img);
		draw_background(mlx->img);
		
		raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
		drawMap2D(mlx, g_game.map);
		drawPlayer(mlx); //on pogne dans les coins parce que la colision du player est trop large
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	}
	else
		frame_timer--;
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx *mlx;

	if (argc != 2)
		return (parse_error(ERR_ARGC));
	mlx = get_mlx();
	g_game.mlx = mlx;
	init_game(&g_game);
	if (!parse_cub(argv[1]))
		return (0);
	mlx_get_screen_size(mlx->mlx, &g_game.screen_x, &g_game.screen_y);
	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook(mlx->mlx, display, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}