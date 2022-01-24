/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:48:56 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/24 11:49:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
