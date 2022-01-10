/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:35:03 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 16:49:14 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

t_pos	new_pos(double x, double y, double z)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_pos	move_pos(t_pos pos, double rot, double dist, int dir)
{
	t_pos	new_pos;

	if (dir)
		rot += 90;
	new_pos.x = pos.x + dist * cos(deg_to_rad(rot));
	new_pos.y = pos.y + dist * -sin(deg_to_rad(rot));
	new_pos.z = pos.z + 0;
	return (new_pos);
}

int	change_player_pos(t_player *player, double vel, int dir)
{
	t_pos	pos;
	t_pos	new_pos;

	pos.x = player->pos.x;
	pos.y = player->pos.y;
	new_pos = move_pos(pos, player->rot, vel, dir);
	if (check_collision(new_pos.x, new_pos.y, 5, g_game.map.width))
	{
		if (check_collision(new_pos.x, pos.y, 5, g_game.map.width))
			new_pos.x = player->pos.x;
	}
	if (check_collision(new_pos.x, new_pos.y, 5, g_game.map.width))
		new_pos.y = player->pos.y;
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
	return (0);
}

void	move_Player(void)
{
	if (g_game.player.vel_u + g_game.player.vel_d)
		change_player_pos(&g_game.player, g_game.player.vel_u + g_game.player.vel_d, 0);
	if (g_game.player.vel_r + g_game.player.vel_l)
		change_player_pos(&g_game.player, g_game.player.vel_r + g_game.player.vel_l, 1);
	if (g_game.player.turn_l + g_game.player.turn_r)
		rotate_player(&g_game.player, g_game.player.turn_l + g_game.player.turn_r);
}
