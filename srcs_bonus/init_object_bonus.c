/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:59:07 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/30 18:05:56 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_obj	new_obj(void)
{
	t_obj	obj;

	obj.alive = FALSE;
	obj.pos = new_pos(0, 0, 0);
	obj.rot = 0;
	obj.dist = 0;
	obj.type = 0;
	obj.update = NULL;
	obj.visible = FALSE;
	return (obj);
}

void	init_obj_array(t_obj *obj, int size)
{
	if (!obj)
		return ;
	while (size-- > 0)
	{
		*obj = new_obj();
		obj++;
	}
}

t_obj_d	init_d(t_img img, double offset, double height, int y)
{
	t_obj_d	d;

	d.index_y = (TEXTURES_SIZE * offset / 2) / (height + offset);
	d.y = y;
	d.step = (double)img.height / (height + offset);
	return (d);
}
