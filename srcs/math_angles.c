/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:44:54 by fousse            #+#    #+#             */
/*   Updated: 2022/01/21 14:19:16 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	angle_is_between(double angle, double min, double max)
{
	if (max < min)
	{
		if (angle >= min || angle <= max)
			return (1);
	}
	else if (angle >= min && angle <= max)
		return (1);
	return (0);
}

//	Convert angle (0 to 359) to radians
double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

//	Convert radians to angle (0 to 359)
double	rad_to_deg(double rad)
{
	return (rad * 180.0 / M_PI);
}
