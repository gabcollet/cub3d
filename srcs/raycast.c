/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/31 16:09:04 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Draw a column of pixel based on a tile/wall.
*/
/* int draw_column(t_pos player_pos, t_coll coll, double rot, int i_x, float dist)
{
	int		color;
	int		y;
	t_pos	pos;
	int		draw_dist;
	double		height;

	pos = coll.pos;
	// Fisheye adjustment (not working???)
	draw_dist = get_draw_distance(player_pos, rot, pos);
	//draw_dist = dist * cos(deg_to_rad(rot));
	if (draw_dist < 1)
		draw_dist = 1;
	height = WIN_H - dist * 2;
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
		my_mlx_pixel_put(get_mlx()->img, i_x, y, color);
		y++;
	}
	return (1);
} */

int	draw3D(float dist, double base_rot, double rot, t_coll coll, int x)
{
	float	cast_angle;
	float	height;
	int		color;
	int		y;
	
	cast_angle = base_rot - rot;
	dist = dist * cos((deg_to_rad((int)cast_angle)));
	height = (g_game.map.size * WIN_H)/dist;
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
int raycast_draw_all(t_pos pos, double rot, double view)
{
	int	win_x;
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
			rot = (int)rot % 360;
		if (rot < 0)
			rot = 360 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		dist = sqrt(pow((coll.pos.x - pos.x), 2) + pow((coll.pos.y - pos.y), 2));

		draw3D(dist, base_rot, rot, coll, WIN_W - win_x);
		//draw_column(pos, coll, base_rot, WIN_W - i, dist); // remove me for 2D !!!!!!!!!!!!!
		
		win_x++;
		rot += (view / WIN_W) ;
	}
	return (1);
}

// Literally draw a raycast on the mlx image
int raycast_draw(t_pos pos, double rot, double dist)
{
	t_pos	r_pos;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	while (i++ < dist && i < 800)
	{
		my_mlx_pixel_put(get_mlx()->img, r_pos.x, r_pos.y, 0x00FF00);
		r_pos = move_pos(r_pos, rot, 1);
	}
	return (1);
}
