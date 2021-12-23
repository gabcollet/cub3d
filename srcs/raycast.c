/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/22 20:19:32 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycast_draw_all(t_pos pos, double rot, double dist, double view)
{
	float		i;

	i = rot - (view / 2);
	//while (r_pos.x <= pos.x + dest.x && r_pos.y <= pos.y + dest.y)
	while (i <= (rot + (view / 2)))
	{
		raycast_draw(pos, i, dist);
		i += 0.2;
	}
	return (1);
}

int raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	t_pos	dest;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x + 5, pos.y + 5, pos.z);
	dest = move_pos(pos, rot, dist);
	//while (r_pos.x <= pos.x + dest.x && r_pos.y <= pos.y + dest.y)
	while (i++ < 1000)
	{
		if (check_collision_x(r_pos.x, r_pos.y, 0) || check_collision_y(r_pos.x, r_pos.y, 0))
			return (0);
		my_mlx_pixel_put(get_mlx(), r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1);
	}
	return (1);
}