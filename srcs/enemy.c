/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/20 19:41:50 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	enemy_ray_hit(t_obj *e, double rot)
{
	if (angle_is_between(rot, e->rot - ((e->rot_side - e->rot) / 2.0),
			e->rot_side))
		return (1);
	else if (e->rot < 90 && e->rot_side > 360 && rot < 90)
	{
		if (angle_is_between(rot + 360, e->rot_side, e->rot + 360
				- ((e->rot - e->rot_side) / 2.0)))
			return (1);
	}
	return (0);
}

double	enemy_get_index(t_obj enemy, t_sprite sprite, double angle)
{
	double	min;
	double	max;
	double	i_x;

	min = enemy.rot - ((enemy.rot_side - enemy.rot) / 2.0);
	max = enemy.rot_side;
	if (min < 0)
		min += 360;
	if (max < min)
	{
		if (angle <= max)
			angle += 360.0;
		max += 360.0;
	}
	i_x = ((sprite.frames[0].width / 4.0) * sprite.x_step)
		* ((int)(angle - min) / (max - min)
			/ sprite.x_step) * 1.5;
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
