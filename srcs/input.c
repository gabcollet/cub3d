/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:41:15 by fousse            #+#    #+#             */
/*   Updated: 2021/12/31 18:51:33 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	mouse_handler(int x, int y)
{
	static int	mouse_x;
	static int	mouse_y;

	mlx_mouse_get_pos(get_mlx()->mlx, get_mlx()->win, &x, &y);
	if (mouse_x != x)
		rotate_player(&g_game.player, (mouse_x - x) * MOUSE_TURN);
	/*if (x >= WIN_W)
	{
		x = (x % WIN_W);
		mlx_mouse_move(get_mlx()->mlx, get_mlx()->win, x, mouse_y);
		
	}*/
	mouse_x = x;
	mouse_y = y;
	return (0);
}

int	key_press(int key, t_mlx *mlx)
{
	mlx = NULL;
	if (key == LEFT_KEY)
		g_game.player.turn_l = TURN_SPEED;
	if (key == RIGHT_KEY)
		g_game.player.turn_r = -TURN_SPEED;
	if (key == W_KEY)
		g_game.player.vel_u = SPEED;
	if (key == S_KEY)
		g_game.player.vel_d = -SPEED;
	if (key == A_KEY)
		g_game.player.vel_l = SPEED;
	if (key == D_KEY)
		g_game.player.vel_r = -SPEED;
	return (key);
}

int	key_release(int key, t_mlx *mlx)
{
	mlx = NULL;
	if (key == W_KEY)
		g_game.player.vel_u = 0;
	if (key == A_KEY)
		g_game.player.vel_l = 0;
	if (key == S_KEY)
		g_game.player.vel_d = 0;
	if (key == D_KEY)
		g_game.player.vel_r = 0;
	if (key == LEFT_KEY)
		g_game.player.turn_l = 0;
	if (key == RIGHT_KEY)
		g_game.player.turn_r = 0;
	if (key == ESC)
		exit_game(&g_game, 0);
	return (key);
}

int	quit_handler(void)
{
	exit_game(&g_game, 0);
	return (0);
}
