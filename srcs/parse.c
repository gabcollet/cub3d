/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/01 19:50:28 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_valid_map_c(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	parse_valid_map_line(char *line, int *player_found)
{
	int	wall_found;
	int	error;
	int i;

	wall_found = 0;
	error = 0;
	i = 0;
	while (line && line[i])
	{
		if (!parse_valid_map_c(line[i]))
			return (parse_error(ERR_MAPC));
		if (line[i] == '1')
			wall_found = 1;
		else if (line[i] == '0')
		{
			if (!wall_found)
				return (parse_error(ERR_WALL));
			if (i != 0 && (line[i - 1] == ' ' || line[i + 1] == ' '))
				return (parse_error(ERR_SPACE));
		}
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			*player_found = *player_found + 1;
	}
	if (line && i != 0 && (line[i - 1] != 1 && line[i - 1] != ' ') || !wall_found)
		return (parse_error(ERR_WALL));
	return (0);
}

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
	return (code);
}

int	parse_map_line(char *line, int fd)
{
	int		player_found;
	int		error;
	int		i;
	int		len;
	
	i = 0;
	len = 0;
	error = parse_valid_map_line(line, &player_found);
	while (error == 0)
	{
		if (ft_strlen(line) > len)
			len = ft_strlen(line);
		map_str[i++] = ft_strdup(line);
		free(line);
		error = get_next_line(&line);
		error = parse_valid_map_line(line, &player_found);
	}
	map_str[i] == NULL;
	if (player_found != 1)
		error = parse_err(ERR_PLAYER);
	player_found = 0;
}

int	parse_map(char *line, int fd, t_map *map)
{
	char	**map_str;
	int		player_found;
	int		error;
	int		i;
	
	i = 0;
	map_str = (char **)ft_calloc(100, sizeof(char *));
	error = parse_valid_map_line(line, &player_found);
	while (error == 0)
	{
		if (ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		map_str[i++] = ft_strdup(line);
		free(line);
		get_next_line(&line);
		error = parse_valid_map_line(line, &player_found);
	}
	map_str[i] == NULL;
	if (player_found != 1)
		error = parse_err(ERR_PLAYER);
	player_found = 0;
}

int	parse_line(char *line, int fd)
{
	int		error;
	int		i;

	if (!line)
		return (-1);
	i = 0;
	if (ft_isalpha(*line))
	{
		error = parse_identifier(line);
	}
	else if	(*line == ' ' || ft_isdigit(*line))
	{
		
		error = parse_map_line(line, fd);
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
	fd = open(path, 0_RDONLY);
	if (fd < 0)
		return (parse_error(ERR_FILE));
	exit_code = get_next_line(&line);
	while (exit_code > 0)
	{
		exit_code = parse_line(line, fd);
		if (exit_code)
			break;
		exit_code = get_next_line(&line);
	}


}