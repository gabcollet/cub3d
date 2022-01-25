/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

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

void	find_smallest(double *i_dist, int *draw, double smallest)
{
	int				id;

	id = 0;
	while (id < g_game.enemy_count)
	{
		if (g_game.enemies[id].dist < *i_dist
			&& g_game.enemies[id].dist > smallest)
		{
			*i_dist = g_game.enemies[id].dist;
			*draw = id;
		}
		id++;
	}
	id = 0;
	while (id < g_game.door_count)
	{
		if (g_game.doors[id].dist < *i_dist
			&& g_game.doors[id].dist > smallest)
		{
			*i_dist = g_game.doors[id].dist;
			*draw = id;
		}
		id++;
	}
}

void	draw_sprites(double height, double rot, int win_x)
{
	int		i;
	double	i_dist;
	int		draw;
	double	smallest;

	i = 0;
	while (i < (g_game.enemy_count + g_game.door_count))
	{
		i_dist = 20000000.0;
		find_smallest(&i_dist, &draw, smallest);
		smallest = i_dist;
		if (draw < g_game.enemy_count
			&& (double)g_game.enemies[draw].dist == i_dist)
			raycast_draw_enemies(&g_game.enemies[draw], height, rot, win_x);
		else if (draw < g_game.door_count
			&& (double)g_game.doors[draw].dist == i_dist)
			raycast_draw_doors(&g_game.doors[draw], height, rot, WIN_W - win_x);
		i++;
	}
}
