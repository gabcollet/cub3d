/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/14 16:26:33 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	init_door_sprite(t_sprite *sprite)
{	
	init_sprite(sprite);
	load_sprite(&sprite->frames[0], "./sprites/door/door_1.xpm");
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
	load_sprite(&sprite->frames[15], "./sprites/door/door_16.xpm");
	sprite->frames_n = 16;
	sprite->anim_time = ANIM_TIME / 3;
	sprite->scaling = 3.0;
	sprite->playing = FALSE;
	sprite->loop = FALSE;
	sprite->rewind = TRUE;
}

// /*
// * If the sprite is not already animated, it will 
// * set its playing flag to true;
// */
// void	open_door(t_sprite *sprite)
// {
// 	if (!sprite)
// 		return ;
// 	if (sprite->playing != TRUE)
// 	{
// 		sprite->playing = TRUE;
// 	}
// }

// /*
// * Manage a sprite's playing animation.
// * Will change its frame or end the animation if needed 
// */
// void	update_animation(t_sprite *sprite)
// {
// 	if (!sprite || sprite->playing == FALSE)
// 		return ;
// 	if (sprite->anim_countdown <= 0)
// 	{
// 		sprite->active++;
// 		if (sprite->active >= sprite->frames_n)
// 		{
// 			if (sprite->loop)
// 				sprite->active = 0;
// 			else
// 				end_animation(sprite);
// 		}
// 		sprite->anim_countdown = sprite->anim_time;
// 	}
// 	else
// 		sprite->anim_countdown--;
// }

// void	end_animation(t_sprite *sprite)
// {
// 	if (!sprite)
// 		return ;
// 	sprite->active = 0;
// 	sprite->anim_countdown = 0;
// 	sprite->playing = FALSE;
// }
