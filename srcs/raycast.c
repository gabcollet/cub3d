/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/24 12:39:43 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycast_draw_all(t_pos pos, double rot, double view)
{
	int		i;
	float	dist;
	t_coll	coll;

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	i = 0;
	rot -= view / 2;
	while (i < VIEW)
	{
		if (rot >= 360)
			rot = (int)rot % 360;
		if (rot < 0)
			rot = 360 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		printf("pos : (%f, %f)\n", pos.x, pos.y);
		printf("coll : (%f, %f)\n", coll.pos.x, coll.pos.y);
		printf("rot : %f \n", rot);
		dist = sqrt(pow((coll.pos.x - pos.x), 2) + pow((coll.pos.y - pos.y), 2));
		raycast_draw(pos, rot, dist);
		i++;
		rot++;
	}
	return (1);
}

int raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	while (i++ < dist && i < 800)
	{
		my_mlx_pixel_put(get_mlx(), r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1);
	}
	return (1);
}