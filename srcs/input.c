/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:41:15 by fousse            #+#    #+#             */
/*   Updated: 2021/12/31 13:24:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	mouse_handler(int x, int y)
{
	static int	mouse_x;
	static int	mouse_y;

	mlx_mouse_get_pos(get_mlx()->mlx, get_mlx()->win, &x, &y);
	if (mouse_x != x)
		rotate_player(&g_game.player, -(mouse_x - x) * MOUSE_TURN);
	/*if (x >= WIN_W)
	{
		x = (x % WIN_W);
		mlx_mouse_move(get_mlx()->mlx, get_mlx()->win, x, mouse_y);
		
	}*/
	mouse_x = x;
	mouse_y = y;
	return (0);
}

/*int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	mouse_x;
	static int	mouse_y;

	mlx = NULL;
	if (x != 0)
	{
		mlx_mouse_get_pos(get_mlx()->mlx, get_mlx()->win, &x, &y);
		if (mouse_x != x)
			rotate_player(&g_game.player, -(mouse_x - x) * MOUSE_TURN);
		mouse_x = x;
		mouse_y = y;
	}
	printf("x = %d\n", x);
	if (x > 500)
		mlx_mouse_move(get_mlx()->mlx, get_mlx()->win, 0, 0);
	return (0);
}*/

int key_press(int key, t_mlx *mlx)
{
	mlx = NULL;
	if(key == LEFT_KEY)
		rotate_player(&g_game.player, TURN_SPEED);
	if(key == RIGHT_KEY)
		rotate_player(&g_game.player, -TURN_SPEED);
	if(key == W_KEY)
		g_game.player.vel_u_d = SPEED;
	if(key == S_KEY)
		g_game.player.vel_u_d = -SPEED;
	if(key == A_KEY)
		g_game.player.vel_r_l = SPEED;
	if(key == D_KEY)
		g_game.player.vel_r_l = -SPEED;
	return (key);
}

int key_release(int key, t_mlx *mlx)
{
	mlx = NULL;
	if(key == W_KEY || key == S_KEY)
		g_game.player.vel_u_d = 0;
	if(key == A_KEY || key == D_KEY)
		g_game.player.vel_r_l = 0;
	if (key == ESC)
		exit(0);
	return (key);
}
