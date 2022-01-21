/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/20 19:20:54 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_object(t_mlx *mlx, t_sprite *sprite, int x, double height)
{
	t_obj_draw	d;
	int			color;
	t_img		img;
	int			y;
	double		offset;

	offset = 0;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	img = sprite->frames[sprite->active];
	d = init_d(img, offset, height, y);
	while (d.y >= 0 && d.y < WIN_H - y && x >= 0 && x < WIN_W
		&& d.index_y < img.height)
	{
		color = color_get(img, (int)sprite->i_x, (int)d.index_y);
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		my_mlx_pixel_put(g_game.game_img, x, d.y, color);
		d.index_y += d.step;
		d.y++;
	}
}

double	obj_rot(double enemy_dist, t_pos enemy_pos, t_pos pos)
{
	double	rot;
	double	dist_a;
	double	dist_b;
	double	dist_c;

	dist_a = enemy_dist;
	dist_b = sqrt(pow((pos.x - pos.x + 5), 2));
	dist_c = sqrt(pow((enemy_pos.x - (pos.x + 5)), 2)
			+ pow((enemy_pos.y - pos.y), 2));
	rot = acosf((pow(dist_a, 2) + pow(dist_b, 2) - pow(dist_c, 2))
			/ (2 * dist_a * dist_b));
	rot = rad_to_deg(rot);
	if (pos.y < enemy_pos.y)
		rot = 360.0 - rot;
	return (rot);
}

t_obj	*obj_set_visible(t_obj *obj, double rot)
{
	int		view;

	view = VIEW_ANGLE / 2;
	{
		if (obj->rot >= (rot - view) && obj->rot <= (rot + view))
			obj->visible = TRUE;
		else if ((rot + view) >= 360 && obj->rot <= (rot + view - 360))
			obj->visible = TRUE;
		else if (obj->rot_side >= (rot - view) && obj->rot_side <= (rot + view))
			obj->visible = TRUE;
	}
	return (obj);
}

void	obj_all_set_visible(t_obj *objs, int a_size, double rot, t_pos base_pos)
{
	int		id;
	t_pos	side_pos;
	t_obj	*obj;

	id = 0;
	while (id < a_size && objs[id].alive)
	{
		obj = &objs[id];
		obj->visible = FALSE;
		obj->dist = sqrt(pow((obj->pos.x - base_pos.x), 2)
				+ pow((obj->pos.y - base_pos.y), 2));
		obj->rot = obj_rot(obj->dist, obj->pos, base_pos);
		side_pos = move_pos(obj->pos, rotate(obj->rot, 90.0),
				obj->sprite.frames[0].width / 4.0, 0);
		obj->dist_side = math_pytha(side_pos.x - base_pos.x,
				side_pos.y - base_pos.y);
		obj->rot_side = obj_rot(obj->dist_side, side_pos, base_pos);
		if (obj->dist > 10)
			obj = obj_set_visible(obj, rot);
		if (obj->visible == TRUE)
			obj->dist = get_draw_distance(base_pos, rot, obj->pos, 0);
		id++;
	}
}
