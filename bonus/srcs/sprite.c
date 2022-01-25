/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:44:15 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/24 17:39:51 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_sprite *sprite)
{
	sprite->active = 0;
	sprite->anim_countdown = 0;
	sprite->anim_time = 0;
	sprite->frames_n = 0;
	sprite->playing = FALSE;
	sprite->scaling = 1;
	sprite->loop = FALSE;
	sprite->drawing = FALSE;
}

void	load_sprite(t_img *img, char *path)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	img->img = mlx_xpm_file_to_image(mlx->mlx, path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->width, &img->endian);
}
