/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:44:54 by fousse            #+#    #+#             */
/*   Updated: 2022/01/04 16:49:13 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

//	Convert angle (0 to 359) to radians
double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

/*
*	Return the draw distance based on the player position and rotation.
*	This is used to prevent fish-eye.
*/
double	get_draw_distance(t_pos pos, double rot, t_pos pixel, double cast_angle)
{
	double	d_x;
	double	d_y;
	double	sin_result;
	double	cos_result;
	double	dist;

	d_x = (int)fabs(pos.x - pixel.x);
	d_y = (int)fabs(pos.y - pixel.y);
	cos_result = fabs(cos(deg_to_rad((int)rot)));
	sin_result = fabs(sin(deg_to_rad((int)rot)));
	dist = d_x * cos_result + d_y * sin_result;
	dist = dist * cos((deg_to_rad((int)cast_angle)));
	dist = (g_game.map.size * WIN_H) / dist;
	return (dist);
}
