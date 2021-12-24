/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:24:40 by fousse            #+#    #+#             */
/*   Updated: 2021/12/24 11:24:43 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	rotate_player(t_player *player, double rot)
{
	if (player->rot + rot >= 360)
		player->rot = fmod((player->rot + rot), (double)360);
	else if (player->rot + rot < 0)
		player->rot = 360 - fmod(fabs((player->rot + rot)), (double)360);
	else
		player->rot += rot;
	return (player->rot);
}
