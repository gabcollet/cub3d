/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	enemy_ray_hit(t_obj *e, double rot)
{
	double	er;
	double	ers;

	er = e->rot;
	ers = e->rot_side;
	if (angle_is_between(rot, er - ((ers - er) / 2.0), ers))
		return (1);
	else if (ers < 90 && er > 270 && rot > 270)
	{
		if (angle_is_between(rot, er, ers))
		{
			return (1);
		}
	}
	return (0);
}

void	enemy_adjust_index(t_obj *e, double *min, double *max, double *angle)
{
	if (*min > 270 && *max < 90 && (*angle < *min || *angle > *max))
	{
		if (*angle <= *max)
			*angle = *angle + 360;
		*max = *max + 360;
	}
	else
	{
		if (*min > *max)
		{
			*min = e->rot_side;
			*max = e->rot;
		}
		if (*max < *min)
		{
			if (*angle <= *max)
				*angle = *angle + 360;
			*max = *max + 360;
		}
	}
}

double	enemy_get_index(t_obj enemy, t_sprite sprite, double angle)
{
	double	min;
	double	max;
	double	i_x;

	min = enemy.rot;
	max = enemy.rot_side;
	if (min < 90 && max > 270)
	{
		max += 360;
		if (angle < 90)
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((angle + 360 - min) / (max - min)));
		else
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((angle - min) / (max - min)));
	}
	else
	{
		enemy_adjust_index(&enemy, &min, &max, &angle);
		i_x = (int)((sprite.frames[0].width / 4.0)
				* ((angle - min) / (max - min)));
	}
	return (i_x);
}

void	enemies_update(t_obj *enemies)
{
	int	id;

	id = 0;
	while (id < g_game.enemy_count)
	{
		if (enemies[id].sprite.playing && enemies[id].alive)
			update_animation(&enemies[id].sprite);
		id++;
	}
}
