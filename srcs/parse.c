/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/04 23:19:01 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_line(char *line, int fd)
{
	int		error;
	int		i;

	if (!line)
		return (-1);
	i = 0;
	if (ft_isalpha(*line))
	{
		//error = parse_identifier(line);
		error = 0;
	}
	else if	(*line == ' ' || ft_isdigit(*line))
	{
		error = parse_map(line, &g_game.map, fd);
		parse_valid_map(g_game.map);
	}
	else if (!*line)
		return (0);
	return (error);
}

int	parse_cub(char *path)
{
	char	*line;
	int		fd;
	int		exit_code;
	
	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(ERR_FILE));
	exit_code = get_next_line(&line, fd);
	while (exit_code > 0)
	{
		exit_code = parse_line(line, fd);
		if (exit_code)
			break;
		exit_code = get_next_line(&line, fd);
	}
}