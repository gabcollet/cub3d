/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:53:43 by fousse            #+#    #+#             */
/*   Updated: 2022/01/05 16:59:51 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*t_map	new_map(int width, int height, )
{
	
	return (t);
}*/

/*
* Take a str_split to then fill the char *map in map_ptr.
*/
void	fill_map(char **rows, t_map *map_ptr, int width, int height)
{
	int		i;
	int		j;

	if (!rows || !*rows)
		return ;
	map_ptr->tiles = (char *)ft_calloc(width * height + 1, sizeof(char));
	if (!map_ptr->tiles)
		return ;
	i = 0;
	while (rows && *rows)
	{
		j = 0;
		while ((*rows)[j])
			map_ptr->tiles[i++] = (*rows)[j++];
		while (j < width)
			map_ptr->tiles[i++] = M_EMPTY;	
		rows++;
	}
	map_ptr->tiles[i] = '\0';
	map_ptr->width = width;
	map_ptr->height = height;
	map_ptr->size = width * height;
}

/*
* Function to be removed; used for initial testing when we didn't have parsing
*/
int	*copy_map_int(int *src, int size)
{
	int	*tiles;
	int	i;

	tiles = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		tiles[i] = src[i];
		i++;
	}
	return (tiles);
}

/*
* Function to be removed; used for initial testing when we didn't have parsing
*/
char	*copy_map(char *src, int size)
{
	char	*tiles;
	int	i;

	tiles = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		tiles[i] = src[i];
		i++;
	}
	tiles[i] == '\0';
	return (tiles);
}
