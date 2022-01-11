/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/11 12:58:14 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enemy_update(t_obj *enemy)
{
	if (enemy->sprite.playing)
		update_animation(&enemy->sprite);
}

void	init_enemy(t_sprite *sprite)
{	
 
	init_sprite(sprite);
	load_sprite(&sprite->frames[0], "./sprites/enemy/enemy_01.xpm");
	load_sprite(&sprite->frames[1], "./sprites/enemy/enemy_02.xpm");
	load_sprite(&sprite->frames[2], "./sprites/enemy/enemy_03.xpm");
	load_sprite(&sprite->frames[3], "./sprites/enemy/enemy_04.xpm");
	sprite->frames_n = 4;
	sprite->anim_time = 30;
	sprite->scaling = 6.0;
	sprite->playing = TRUE;
	sprite->loop = TRUE;
}