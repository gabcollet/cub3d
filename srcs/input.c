/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:41:15 by fousse            #+#    #+#             */
/*   Updated: 2021/12/22 19:42:45 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int key_press(int key, t_mlx *mlx)
{
	mlx = NULL;
	//printf("%d\n", key);
	if(key == A_KEY)
		rotate_player(&g_game.player, -TURN_SPEED);
	if(key == D_KEY)
		rotate_player(&g_game.player, TURN_SPEED);
	if(key == W_KEY)
		g_game.player.vel = SPEED;
	if(key == S_KEY)
		g_game.player.vel = -SPEED;
	return (key);
}

int key_release(int key, t_mlx *mlx)
{
	mlx = NULL;
	if(key == W_KEY)
		g_game.player.vel = 0;
	if(key == S_KEY)
		g_game.player.vel = 0;
	if (key == ESC)
		exit(0);
	return (key);
}
