/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:44:54 by fousse            #+#    #+#             */
/*   Updated: 2021/12/24 15:46:23 by fousse           ###   ########.fr       */
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
double	get_draw_distance(t_pos pos, double rot, t_pos pixel)
{
	int		d_x;
	int 	d_y;

	d_x = (int)fabs(pos.x - pixel.x);
	d_y = (int)fabs(pos.y - pixel.y);
	return (d_x * fabs(cos(deg_to_rad((int)rot))) + d_y * fabs(sin(deg_to_rad((int)rot))));
}
