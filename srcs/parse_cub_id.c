/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/11 14:12:05 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_wall_texture(char *path, int side)
{
	t_img	*img;

	while (*path == ' ')
		path++;
	img = &g_game.texture[side];
	img->img = mlx_xpm_file_to_image(g_game.mlx->mlx,
			path, &img->width, &img->height);
	if (!img->img)
		return (parse_error(ERR_TEXTURE));
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->width, &img->endian);
	if (!img->addr)
		return (parse_error(ERR_TEXTURE));
	return (1);
}

int	parse_enemy(char *line)
{
	static int	id;
	t_pos		pos;
	char		**split;
	int			error;

	error = 0;
	while (*line == ' ')
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (parse_error(-1));
	if (ft_array_size((void **)split) != 3)
		error = ERR_ENEMY;
	else
	{
		pos = new_pos(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
		g_game.enemies[id].pos = pos;
		g_game.enemies[id].type = ENEMY;
		init_enemy(&g_game.enemies[id++].sprite);
	}
	ft_free_array((void **)split, ft_free);
	if (error)
		return (parse_error(error));
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
	while (*colors == ' ')
		colors++;
	split = ft_split(colors, ',');
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
	g_game.map.ceiling_c = color_rgb_to_int(rgb);
	if (id == 'F')
		g_game.map.floor_c = color_rgb_to_int(rgb);
	return (1);
}

int	parse_identifier(char *line)
{
	int	valid;

	valid = 0;
	if (!ft_strncmp("NO ", line, 3))
		valid = parse_wall_texture(line + 3, NO);
	else if (!ft_strncmp("SO ", line, 3))
		valid = parse_wall_texture(line + 3, SO);
	else if (!ft_strncmp("WE ", line, 3))
		valid = parse_wall_texture(line + 3, WE);
	else if (!ft_strncmp("EA ", line, 3))
		valid = parse_wall_texture(line + 3, EA);
	else if (!ft_strncmp("F ", line, 2))
		valid = parse_f_c(line + 2, 'F');
	else if (!ft_strncmp("C ", line, 2))
		valid = parse_f_c(line + 2, 'C');
	else if (!ft_strncmp("E ", line, 2))
		valid = parse_enemy(line + 2);
	else if (!valid)
		return (parse_error(ERR_ID));
	return (1);
}
