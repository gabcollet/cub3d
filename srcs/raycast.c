/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/01 15:09:25 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Draw a column of pixel based on a tile/wall.
*/
int	draw3d(float dist, double cast_angle, t_coll coll, int x)
{
	float	height;
	int		color;
	int		y;

	dist = dist * cos((deg_to_rad((int)cast_angle)));
	height = (g_game.map.size * WIN_H) / dist;
	if (height > WIN_H)
		height = WIN_H;
	y = (WIN_H - height) / 2;
	if (coll.dir & NORTH)
		color = NORTH_C;
	if (coll.dir & SOUTH)
		color = SOUTH_C;
	if (coll.dir & WEST)
		color = WEST_C;
	if (coll.dir & EAST)
		color = EAST_C;
	color = color_shift_int(color, BLACK, (WIN_H - height) / WIN_H);
	while (y < height + (WIN_H - height) / 2)
	{
		my_mlx_pixel_put(get_mlx()->img, x, y, color);
		y++;
	}
	return (0);
}

/*
*	Check collisions and draw pixel columns based on collisions.
*	Can also visually represent raycast in a 2d image.
*/
int	raycast_draw_all(t_pos pos, double rot, double view)
{
	int		win_x;
	float	dist;
	double	base_rot;
	t_coll	coll;

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	win_x = 0;
	base_rot = rot;
	rot -= view / 2;
	while (win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		//dist = get_draw_distance(pos, rot, coll.pos);
		dist = sqrt(pow((coll.pos.x - pos.x), 2) + pow((coll.pos.y - pos.y), 2));
		draw3d(dist, base_rot - rot, coll, WIN_W - win_x);
		win_x++;
		rot += (view / WIN_W);
	}
	return (1);
}

// Literally draw a raycast on the mlx image
int	raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	while (i++ < dist && i < 800)
	{
		my_mlx_pixel_put(get_mlx()->img, r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1, 0);
	}
	return (1);
}
