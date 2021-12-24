/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/23 19:01:56 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycast_draw_all(t_pos pos, double rot, double dist, double view)
{
	int		i;
	float	dista;
	t_pos	coll;

	coll = new_pos(0, 0, 0);
	i = 0;
	rot -= view / 2;
	while (i < VIEW)
	{
		if (rot >= 360)
			rot = (int)rot % 360;
		if (rot < 0)
			rot = 360 + rot;
		coll = check_collisions(pos.x, pos.y, rot);
		/* printf("pos : (%f, %f)\n", pos.x, pos.y);
		printf("coll : (%f, %f)\n", coll.x, coll.y);
		printf("rot : %f \n", rot); */
		dista = sqrt(pow((coll.x - pos.x), 2) + pow((coll.y - pos.y), 2));
		raycast_draw(pos, rot, dista);
		i++;
		rot++;
	}
	return (1);
}

int raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	t_pos	coll;
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