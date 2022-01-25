/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/24 15:06:18 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*
* r = raycast rotation
*/
double	door_get_height(t_door *door, double r)
{
	double	dd;
	double	dr;
	double	drs;
	double	dds;
	double	dh;

	dr = door->rot;
	drs = door->rot_side;
	dd = door->dist;
	dh = -1;
	if ((dr <= 90 && drs >= 270) && (r <= dr || r >= drs))
	{
		if (r <= 90)
			dh = dd + (door->dist_side - dd) * ((r - dr) / (drs - (dr + 360)));
		else
			dh = dd + (door->dist_side - dd) * ((r - (dr + 360))
					/ (drs - (dr + 360)));
	}
	else if (!(dr <= 90 && drs >= 270) && ((dr <= drs
				&& angle_is_between(r, dr, drs))
			|| ((dr >= drs && angle_is_between(r, drs, dr)))))
		dh = dd + ((door->dist_side - dd) * ((r - dr) / (drs - (dr))));
	return (dh);
}

void	door_adjust_index(t_door *door, double *min, double *max, double *angle)
{
	if (*min > *max)
	{
		*min = door->rot_side;
		*max = door->rot;
	}
	if (*max < *min)
	{
		if (*angle <= *max)
			*angle = *angle + 360;
		*max = *max + 360;
	}
}

double	door_get_index(t_door door, t_sprite sprite, double angle)
{
	double	min;
	double	max;
	double	i_x;

	min = door.rot;
	max = door.rot_side;
	if (min < 90 && max > 270)
	{
		if (angle < 90)
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((min - angle) / (min + 360.0 - max)));
		else
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((angle - max) / (min + 360.0 - max)));
	}
	else
	{
		door_adjust_index(&door, &min, &max, &angle);
		i_x = (int)((sprite.frames[0].width / 4.0)
				* ((angle - min) / (max - min)));
	}
	return (i_x);
}

void	door_set_visible(t_door *door, double rot, t_pos pos)
{
	int			view;
	t_pos		side_pos;
	t_plyr		plyr;

	plyr = g_game.player;
	view = VIEW_ANGLE;
	if (door->rot >= (rot - view) && door->rot <= (rot + view))
		door->visible = TRUE;
	else if ((rot + view) >= 360 && door->rot <= (rot + view - 360))
		door->visible = TRUE;
	else if (door->rot_side >= (rot - view) && door->rot_side <= (rot + view))
		door->visible = TRUE;
	if (door->visible == TRUE)
	{
		door->dist = math_pytha(door->pos.x - pos.x, door->pos.y - pos.y);
		door->rot = obj_rot(door->dist, door->pos, pos);
		if (door->face_rot == 0)
			side_pos = new_pos(door->pos.x + 50.0, door->pos.y, 0.0);
		else
			side_pos = new_pos(door->pos.x, door->pos.y + 50.0, 0.0);
		door->dist_side = math_pytha(side_pos.x - pos.x, side_pos.y - pos.y);
		door->rot_side = obj_rot(door->dist_side, side_pos, pos);
		door->dist = get_draw_distance(pos, plyr.rot, door->pos, 0);
		door->dist_side = get_draw_distance(pos, plyr.rot, side_pos, 0);
	}
}

void	doors_set_visible(t_door *doors, int size, double rot, t_pos base_pos)
{
	int			i;
	int			view;
	t_pos		side_pos;
	t_door		*door;

	i = 0;
	view = VIEW_ANGLE;
	while (i < size)
	{
		door = &doors[i];
		door_set_visible(door, rot, base_pos);
		i++;
	}
}
