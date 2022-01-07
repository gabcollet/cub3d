/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/07 01:57:40 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*
* Show the right error message and return 0
*/
int	parse_error(int code)
{
	ft_putendl_fd("Error", 2);
	if (code == ERR_FILE)
		ft_putendl_fd("file could not be found or opened", 2);
	else if (code == ERR_TEXTURE)
		ft_putendl_fd("texture file could not be found or opened", 2);
	else if (code == ERR_MAPC)
		ft_putendl_fd("map have unknown characters", 2);
	else if (code == ERR_WALL)
		ft_putendl_fd("map is not enclosed with walls", 2);
	else if (code == ERR_SPACE)
		ft_putendl_fd("map contains a space where prohibited", 2);
	else if (code == ERR_PLAYER)
		ft_putendl_fd("map contains no players or too many", 2);
	else if (code == ERR_ARGC)
		ft_putendl_fd("cub3D requires only 1 argument, which is a .cub file", 2);
	else if (code == ERR_ID)
		ft_putendl_fd(".cub file contains erronous identifiers", 2);
	else if (code == ERR_MISS)
		ft_putendl_fd(".cub file is missing mandatory elements", 2);
	else if (code == ERR_COLOR)
		ft_putendl_fd(".cub file has invalid floor or ceiling color format", 2);
	else if (code == ERR_MAP_LAST)
		ft_putendl_fd(".cub file's map is not the last element", 2);
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
