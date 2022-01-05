/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/04 23:25:12 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_error(int code)
{
	printf("Error: ");
	if (code == ERR_FILE)
		printf("file could not be found or opened\n");
	else if (code == ERR_MAPC)
		printf("map have unknown characters\n");
	else if (code == ERR_WALL)
		printf("map is not enclosed with walls\n");
	else if (code == ERR_SPACE)
		printf("map contains a space where prohibited\n");
	else if (code == ERR_PLAYER)
		printf("map contains no players or too many\n");
	return (0);
}

int	parse_valid_map_c(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (1);
	if (parse_is_player(c))
		return (1);
	return (0);
}

int	parse_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (c == 'N')
			g_game.player.rot = 90;
		if (c == 'S')
			g_game.player.rot = 270;
		if (c == 'W')
			g_game.player.rot = 180;
		if (c == 'E')
			g_game.player.rot = 0;
		return (1);
	}
		
	return (0);
}
