/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 12:26:06 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	gun_update(t_obj *gun)
{
	if (gun->sprite.playing)
		update_animation(&gun->sprite);
}

// need to be reworked so it works with the parse. this is for testing purpose
void	init_handgun(t_sprite *sprite)
{	
 
	init_sprite(sprite);
	load_sprite(&sprite->frames[0], "./sprites/handgun/gun_01.xpm");
	load_sprite(&sprite->frames[1], "./sprites/handgun/gun_02.xpm");
	load_sprite(&sprite->frames[2], "./sprites/handgun/gun_03.xpm");
	load_sprite(&sprite->frames[3], "./sprites/handgun/gun_04.xpm");
	load_sprite(&sprite->frames[4], "./sprites/handgun/gun_05.xpm");
	sprite->frames_n = 5;
	sprite->anim_time = 15;
	sprite->scaling = 4.0;
}
