/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:44:54 by fousse            #+#    #+#             */
/*   Updated: 2022/01/16 03:04:31 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

double	math_pytha(double x, double y)
{
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

/*
*	Return the draw distance based on the player position and rotation.
*	This is used to prevent fish-eye.
*/
double	get_draw_distance(t_pos pos, double rot, t_pos pixel, double angle)
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
	dist = dist * cos((deg_to_rad((int)angle)));
	dist = (50 * g_game.res_h) / dist;
	return (dist);
}
