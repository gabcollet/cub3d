/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/14 15:44:52 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enemy_update(t_obj *enemies)
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
	/*load_sprite(&sprite->frames[0], "./sprites/door/door_1.xpm");
	load_sprite(&sprite->frames[1], "./sprites/door/door_2.xpm");
	load_sprite(&sprite->frames[2], "./sprites/door/door_3.xpm");
	load_sprite(&sprite->frames[3], "./sprites/door/door_4.xpm");
	load_sprite(&sprite->frames[4], "./sprites/door/door_5.xpm");
	load_sprite(&sprite->frames[5], "./sprites/door/door_6.xpm");
	load_sprite(&sprite->frames[6], "./sprites/door/door_7.xpm");
	load_sprite(&sprite->frames[7], "./sprites/door/door_8.xpm");
	load_sprite(&sprite->frames[8], "./sprites/door/door_9.xpm");
	load_sprite(&sprite->frames[9], "./sprites/door/door_10.xpm");
	load_sprite(&sprite->frames[10], "./sprites/door/door_11.xpm");
	load_sprite(&sprite->frames[11], "./sprites/door/door_12.xpm");
	load_sprite(&sprite->frames[12], "./sprites/door/door_13.xpm");
	load_sprite(&sprite->frames[13], "./sprites/door/door_14.xpm");
	load_sprite(&sprite->frames[14], "./sprites/door/door_15.xpm");
	load_sprite(&sprite->frames[15], "./sprites/door/door_16.xpm");*/
	sprite->frames_n = 4;
	sprite->anim_time = ANIM_TIME / 3;
	sprite->scaling = 6.0;
	sprite->playing = TRUE;
	sprite->loop = TRUE;
}

// void	enemy_visible()
