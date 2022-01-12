/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/12 14:29:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_obj	new_obj(void)
{
	t_obj	obj;

	obj.enabled = FALSE;
	obj.alive = FALSE;
	obj.pos = new_pos(0,0,0);
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
