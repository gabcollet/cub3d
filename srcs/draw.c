/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/20 19:25:54 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	reset_drawings(void)
{
	int	i;

	i = 0;
	while (i < g_game.door_count)
	{
		g_game.doors[i].sprite.drawing = FALSE;
		g_game.doors[i].visible = FALSE;
		g_game.doors[i].dist = 0;
		g_game.doors[i].dist_side = 0;
		i++;
	}
	i = 0;
	while (i < g_game.enemy_count)
	{
		g_game.enemies[i].sprite.drawing = FALSE;
		g_game.enemies[i].visible = FALSE;
		i++;
	}
}
