/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:51:46 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 14:08:02 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_new_image(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->width, &img->endian);
	img->height = height;
}

void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_W || y > WIN_H || x <= 0 || y <= 0)
		return ;
	dst = img.addr + (y * img.width + x * (img.bpp / 8));
	if (color != TRANS)
		*(unsigned int *)dst = color;
}

/* Set all pixel to black in a given image */
void	mlx_clear_img(t_img img)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < WIN_W * WIN_H)
	{
		dst = img.addr + (i * (img.bpp / 8));
		*(unsigned int *)dst = 0;
		i++;
	}
}
