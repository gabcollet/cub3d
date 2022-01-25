/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:53:43 by fousse            #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

int	get_map_index_x(int win_x)
{
	int	tile_x;

	tile_x = win_x / (int)TILE_SIZE;
	return (tile_x);
}

int	get_map_index_y(int win_y)
{
	int	tile_y;

	tile_y = win_y / (int)TILE_SIZE;
	return (tile_y);
}

int	get_map_index(int win_x, int win_y)
{
	int	tile_i;
	int	tile_x;
	int	tile_y;

	tile_x = get_map_index_x(win_x);
	tile_y = get_map_index_y(win_y);
	tile_i = tile_x + tile_y * g_game.map.width;
	return (tile_i);
}
