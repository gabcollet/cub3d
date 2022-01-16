/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/15 15:07:35 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	gun_update(t_obj *gun)
{
	static int		shoot;
	static t_obj	bullet;

	if (gun->sprite.playing)
		update_animation(&gun->sprite);
	if (!shoot && gun->sprite.active == 1)
	{

	}
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
	sprite->anim_time = ANIM_TIME / 5;
	sprite->scaling = 4.0;
}
