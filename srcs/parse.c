/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/06 16:37:22 by fousse           ###   ########.fr       */
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

int	parse_wall_text(char *path, int side)
{
	t_img	*img;

	while (*path == ' ')
		path++;
	img = &g_game.texture[side];
	img->img = mlx_xpm_file_to_image(g_game.mlx->mlx, path, &img->width, &img->height);
	if (!img->img)
		return (parse_error(ERR_TEXTURE));
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
				&img->width, &img->endian);
	if (!img->addr)
		return (parse_error(ERR_TEXTURE));
	return (1);
}

/*
* Received format is "r,g,b\0"
*/
int	parse_f_c(char *colors, char id)
{
	t_rgb	rgb;
	char	**split;
	int		error;

	error = 0;
	split = ft_split(colors, ',');
	while (*colors == ' ')
		colors++;
	if (!split)
		return (parse_error(-1));
	if (ft_array_size((void **)split) != 3)
		error = ERR_COLOR;
	else
	{
		rgb = new_rgb(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
		if (!color_valid_rgb(rgb))
			error = 0;
	}
	ft_free_array((void **)split, ft_free);
	if (error)
		return (parse_error(error));
	if (id == 'F')
		g_game.map.floor_c = color_rgb_to_int(rgb);
	else
		g_game.map.ceiling_c = color_rgb_to_int(rgb);
	return (1);
}

int parse_identifier(char *line)
{
	int	valid;

	valid = 0;
	if (!ft_strncmp("NO ", line, 3))
		valid = parse_wall_text(line + 3, NO);
	else if (!ft_strncmp("SO ", line, 3))
		valid = parse_wall_text(line + 3, SO);
	else if (!ft_strncmp("WE ", line, 3))
		valid = parse_wall_text(line + 3, WE);
	else if (!ft_strncmp("EA ", line, 3))
		valid = parse_wall_text(line + 3, EA);
	else if (!ft_strncmp("F ", line, 2))
		valid = parse_f_c(line + 2, 'F');
	else if (!ft_strncmp("C ", line, 2))
		valid = parse_f_c(line + 2, 'C');
	else if (!valid)
		return (parse_error(ERR_ID));
	return (1);
}

int	parse_line(char *line, int fd)
{
	int		valid;
	int		i;

	valid = 0;
	if (!line)
		return (-1);
	i = 0;
	if (*line && g_game.map.tiles != NULL)
		return (parse_error(ERR_MAP_LAST));
	else if (ft_isalpha(line[0]))
		valid = parse_identifier(line);
	else if	(*line == ' ' || ft_isdigit(*line))
	{
		valid = parse_map(line, &g_game.map, fd);
		valid = parse_valid_map(g_game.map);
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
		if (!valid)
			break;
		bytes = get_next_line(&line, fd);
	}
	if (valid)
		valid = parse_is_all_valid(g_game);
	return (valid);
}
