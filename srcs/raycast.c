/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/23 14:05:28 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycast_draw_all(t_pos pos, double rot, double dist, double view)
{
	float		i;
	float		dista;
	t_pos		coll;

	coll = new_pos(0, 0, 0);
	//i = rot - (view / 2);
	//while (i <= (rot + (view / 2)))
	//{
		coll = check_collisions(pos.x, pos.y, rot);
		dista = sqrt(pow((coll.x - pos.x), 2) + pow((coll.y - pos.y), 2));
		// printf("pos = (%f,%f) \n", pos.x, pos.y);
		//printf("coll = (%f,%f) \n", coll.x, coll.y);
		//printf("rot = %f \n", rot);
		//printf("dista = %f\n", dista);
		raycast_draw(pos, rot, dista);
		//i += 0.2;
	//}
	return (1);
}

int raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	t_pos	dest;
	t_pos	coll;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	dest = move_pos(pos, rot, dist);
	while (i++ < dist && i < 800)
	{
		// if (check_collision_x(r_pos.x, r_pos.y, 0) || check_collision_y(r_pos.x, r_pos.y, 0))
		// 	return (0);
		my_mlx_pixel_put(get_mlx(), r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1);
	}
	return (1);
}