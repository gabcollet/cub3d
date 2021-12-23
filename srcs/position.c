/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:35:03 by fousse            #+#    #+#             */
/*   Updated: 2021/12/23 02:43:07 by fousse           ###   ########.fr       */
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

t_pos	move_pos(t_pos pos, double rot, double dist)
{
	t_pos	new_pos;
	
	new_pos.x = pos.x + dist * cos(deg_to_rad(rot));
	new_pos.y = pos.y + dist * sin(deg_to_rad(rot));
	new_pos.z = pos.z + 0;
	//printf("| dist = %f rot = %f cos = %f sin = %f\n", dist, rot, cos(deg_to_rad(rot)),  cos(deg_to_rad(rot)));

	return (new_pos);
}

int	change_player_pos(t_player *player)
{
	t_pos pos;
	t_pos new_pos;

	pos.x = player->pos.x;
	pos.y = player->pos.y;
	new_pos = move_pos(pos, player->rot, player->vel);
	if (check_collision_x(new_pos.x, new_pos.y, 10))
	{
		if (check_collision_x(new_pos.x, pos.y, 10))
			new_pos.x = player->pos.x;
	}
	if (check_collision_y(new_pos.x, new_pos.y, 10))
		new_pos.y = player->pos.y;
	/*if (!check_collision_x(new_pos.x, new_pos.y, 10))
		player->pos.x = new_pos.x;
	if (!check_collision_y(new_pos.x, new_pos.y, 10))
		player->pos.y = new_pos.y;*/
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
	return (0);
}