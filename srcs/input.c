/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:41:15 by fousse            #+#    #+#             */
/*   Updated: 2022/01/28 17:36:40 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	key_press(int key)
{
	double	modifier;

	modifier = ((double)WIN_H * (double)WIN_W) / 1000000.0;
	if (key == LEFT_KEY)
		g_game.player.turn_l = TURN_SPEED * modifier;
	if (key == RIGHT_KEY)
		g_game.player.turn_r = -TURN_SPEED * modifier;
	if (key == W_KEY)
		g_game.player.vel_u = SPEED * modifier;
	if (key == S_KEY)
		g_game.player.vel_d = -SPEED * modifier;
	if (key == A_KEY)
		g_game.player.vel_l = SPEED * modifier;
	if (key == D_KEY)
		g_game.player.vel_r = -SPEED * modifier;
	return (key);
}

int	key_release(int key)
{
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
		exit_game(0);
	return (key);
}

int	quit_handler(void)
{
	exit_game(0);
	return (0);
}
