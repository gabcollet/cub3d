/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/21 16:49:19 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	enemy_adjust_index(t_obj *enemy, double *min, double *max, double *angle)
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
			*min = enemy->rot_side;
			*max = enemy->rot;
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
			
	if (min < 0)
		min += 360;
	min = enemy.rot;
 	max = enemy.rot_side;
	if (min < 90 && max > 270)
	{
		max += 360;
		if (angle < 90)
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((angle + 360 - min) / (max - min))) * 1;
		else
			i_x = (int)((sprite.frames[0].width / 4.0)
					* ((angle - min) / (max - min))) * 1;
	}
	else
	{
		enemy_adjust_index(&enemy, &min, &max, &angle);
		i_x = (int)((sprite.frames[0].width / 4.0)
				* ((angle - min) / (max - min))) * 1;
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

void	init_enemy(t_obj *enemy, t_pos pos)
{	
	*enemy = new_obj();
	init_enemy_sprite(&enemy->sprite);
	enemy->pos = pos;
	enemy->type = ENEMY;
	enemy->alive = TRUE;
	enemy->sprite.playing = TRUE;
}

void	init_enemy_sprite(t_sprite *sprite)
{	
	init_sprite(sprite);
	load_sprite(&sprite->frames[0], "./sprites/enemy/enemy_01.xpm");
	load_sprite(&sprite->frames[1], "./sprites/enemy/enemy_02.xpm");
	load_sprite(&sprite->frames[2], "./sprites/enemy/enemy_03.xpm");
	load_sprite(&sprite->frames[3], "./sprites/enemy/enemy_04.xpm");
	sprite->frames_n = 4;
	sprite->anim_time = ANIM_TIME / 3;
	sprite->scaling = 6.0;
	sprite->playing = TRUE;
	sprite->loop = TRUE;
}
