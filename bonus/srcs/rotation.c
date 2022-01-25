/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:24:40 by fousse            #+#    #+#             */
/*   Updated: 2022/01/14 20:31:14 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	rotate_player(t_plyr *player, double rot)
{
	if (player->rot + rot >= 360)
		player->rot = fmod((player->rot + rot), (double)360);
	else if (player->rot + rot < 0)
		player->rot = 360 - fmod(fabs((player->rot + rot)), (double)360);
	else
		player->rot += rot;
	return (player->rot);
}

double	rotate(double base_rot, double rot)
{
	if (base_rot + rot >= 360.0)
		base_rot = fmod((base_rot + rot), 360.0);
	else if (base_rot + rot < 0)
		base_rot = 360 - fmod(fabs((base_rot + rot)), 360.0);
	else
		base_rot += rot;
	return (base_rot);
}
