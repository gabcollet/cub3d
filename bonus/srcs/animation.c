/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 00:34:59 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*
* If the sprite is not already animated, it will 
* set its playing flag to true;
*/
void	start_animation(t_sprite *sprite)
{
	if (!sprite)
		return ;
	if (sprite->playing != TRUE)
	{
		sprite->playing = TRUE;
	}
}

/*
* Manage a sprite's playing animation.
* Will change its frame or end the animation if needed 
*/
void	update_animation(t_sprite *sprite)
{
	if (!sprite || sprite->playing == FALSE)
		return ;
	if (sprite->anim_countdown <= 0)
	{
		sprite->active++;
		if (sprite->active >= sprite->frames_n)
		{
			if (sprite->loop)
				sprite->active = 0;
			else
				end_animation(sprite);
		}
		sprite->anim_countdown = sprite->anim_time;
	}
	else
		sprite->anim_countdown--;
}

void	end_animation(t_sprite *sprite)
{
	if (!sprite)
		return ;
	sprite->active = 0;
	sprite->anim_countdown = 0;
	sprite->playing = FALSE;
}
