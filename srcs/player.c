/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:15:21 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 01:01:07 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_plyr	get_plyr(void)
{
	return (g_game.player);
}

/*
* Used mainly in parse_valid_map when a player code if found.
*/
void	player_set_pos(int x, int y, int z)
{
	g_game.player.pos.x = x;
	g_game.player.pos.y = y;
	g_game.player.pos.z = z;
}

/*
* Return the cardinal point where the player is facing.
* It uses the (e_dir enum) in the header.
*/
int	player_get_facing(t_plyr player)
{
	int	rot;

	rot = player.rot;
	if (rot >= 45 && rot <= 135)
		return (NORTH);
	if (rot >= 225 && rot <= 315)
		return (SOUTH);
	if (rot >= 135 && rot <= 225)
		return (WEST);
	if (rot >= 315 || rot <= 45)
		return (EAST);
	return (NORTH);
}
