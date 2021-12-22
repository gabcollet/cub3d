/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/22 17:26:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycast_draw(t_pos pos, float rot, int dist)
{
	int		*map;
	t_pos	r_pos;
	t_pos	dest;
	
	r_pos = new_pos(pos.x, pos.y, pos.z);
	f_pos = move_pos(pos, rot, dist);
	dest = g_game.map.map;
	while (r_pos.x <= pos.x + f_pos.x && )
	{
		my_mlx_pixel_put(g_game.mlx, r_pos.x, r_pos.y, 0x00FF00));
	}
}