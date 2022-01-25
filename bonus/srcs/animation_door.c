/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/20 19:23:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*
* If the sprite is not already animated, it will 
* set its playing flag to true;
*/
void	open_door(t_door *door)
{
	t_sprite	*sprite;

	sprite = &door->sprite;
	if (!sprite)
		return ;
	if (sprite->playing != TRUE)
	{
		if (door->opened)
			door->opened = FALSE;
		else
			door->opened = TRUE;
		sprite->playing = TRUE;
	}
}

void	end_door_animation(t_door *door)
{
	t_sprite	*sprite;

	sprite = &door->sprite;
	sprite->anim_countdown = 0;
	sprite->playing = FALSE;
}

void	closing_door(t_door *door)
{
	t_sprite	*sprite;

	sprite = &door->sprite;
	if (sprite->active <= 0 && sprite->anim_countdown == 0)
		end_door_animation(door);
	else
	{
		sprite->active--;
		sprite->anim_countdown = sprite->anim_time;
	}
}

void	opening_door(t_door *door)
{
	t_sprite	*sprite;

	sprite = &door->sprite;
	if (sprite->active >= sprite->frames_n - 1 && sprite->anim_countdown == 0)
	{
		end_door_animation(door);
	}
	else
	{
		sprite->active++;
		sprite->anim_countdown = sprite->anim_time;
	}
}

void	update_door(t_door *door)
{
	t_sprite	*sprite;

	sprite = &door->sprite;
	if (sprite->playing)
	{
		if (sprite->anim_countdown <= 0)
		{
			if (door->opened == TRUE)
				opening_door(door);
			else
				closing_door(door);
		}
		else
			sprite->anim_countdown--;
	}
}
