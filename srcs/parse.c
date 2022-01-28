/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/28 18:08:05 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_is_all_valid(t_game game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game.texture[i++].img == NULL)
			return (parse_error(ERR_MISS));
	}
	if (game.map.ceiling_c < 0 || game.map.floor_c < 0)
		return (parse_error(ERR_MISS));
	if (!game.map.tiles)
		return (parse_error(ERR_MISS));
	return (1);
}

int	parse_line(char *line, int fd)
{
	int		valid;

	valid = 0;
	if (!line)
		return (-1);
	if (*line && g_game.map.tiles != NULL)
		return (parse_error(ERR_MAP_LAST));
	else if (ft_isalpha(line[0]))
	{
		valid = parse_identifier(line);
	}		
	else if (*line == ' ' || ft_isdigit(*line))
	{
		valid = parse_map(line, &g_game.map, fd);
		valid = parse_valid_map(&g_game.map);
	}
	else if (!*line)
		return (1);
	return (valid);
}

int	parse_cub(char *path)
{
	char	*line;
	int		fd;
	int		valid;
	int		bytes;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(ERR_FILE));
	valid = 1;
	bytes = get_next_line(&line, fd);
	while (valid > 0 && bytes > 0)
	{
		valid = parse_line(line, fd);
		if (valid <= 0)
			break ;
		line = ft_free(line);
		bytes = get_next_line(&line, fd);
	}
	line = ft_free(line);
	if (valid)
		valid = parse_is_all_valid(g_game);
	return (valid);
}
