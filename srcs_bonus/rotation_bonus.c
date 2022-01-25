/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:24:40 by fousse            #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

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
