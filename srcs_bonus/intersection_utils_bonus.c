/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 11:00:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

t_pos	increment_pos(t_pos inter, int xy, int side, double rot)
{
	int	sign;

	sign = 0;
	if (side == NORTH || side == EAST)
		sign = 1;
	else if (side == SOUTH || side == WEST)
		sign = -1;
	if (xy == 'y')
	{
		inter.x += (TILE_SIZE / tan(deg_to_rad(rot))) * sign;
		inter.y += -TILE_SIZE * sign;
	}
	else
	{
		inter.x += TILE_SIZE * sign;
		inter.y += (-TILE_SIZE * tan(deg_to_rad(rot))) * sign;
	}
	return (inter);
}

int	parse_s(int side, int xy)
{
	if (xy == 'y')
	{
		if (side == NE || side == NW)
			return (NORTH);
		else
			return (SOUTH);
	}
	else if (xy == 'x')
	{
		if (side == NE || side == SE)
			return (EAST);
		else
			return (WEST);
	}
	return (0);
}

t_coll	check_dir(t_pos inter_y, t_pos inter_x, int side, double rot)
{
	int	x;
	int	y;

	x = g_game.player.pos.x;
	y = g_game.player.pos.y;
	while (1)
	{	
		if ((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2))
			< (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
		{
			if (check_inter_y(inter_y) == 1)
				return (new_collider(inter_y, WALL, parse_s(side, 'y')));
			else
				inter_y = increment_pos(inter_y, 'y', parse_s(side, 'y'), rot);
		}
		else
		{
			if (check_inter_x(inter_x) == 1)
				return (new_collider(inter_x, WALL, parse_s(side, 'x')));
			else
				inter_x = increment_pos(inter_x, 'x', parse_s(side, 'x'), rot);
		}
	}
	return (new_collider(new_pos(0, 0, 0), 0, 0));
}
