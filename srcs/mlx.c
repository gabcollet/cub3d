/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:17:29 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 19:21:59 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

t_mlx	*get_mlx(void)
{
	static t_mlx	mlx;

	if (mlx.init != 1)
	{
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "Cub3D");
		my_mlx_new_image(mlx.mlx, &mlx.img, WIN_W, WIN_H);
		mlx.init = 1;
	}
	return (&mlx);
}

/*
* Will fill the window (win_img) with an (img).
* That (img) will be stretch to fit the window's size.
*/ 
void	mlx_fill_window(t_img *w_img, t_img *img)
{
	double	step_x;
	double	step_y;
	int		i_win;
	double	i_x;
	double	i_y;
	int		color;

	i_win = 0;
	i_x = 0;
	i_y = 0;
	step_x = (double)img->width / (double)w_img->width;
	step_y = (double)img->height / (double)w_img->height;
	while (i_win < w_img->width / 4 * w_img->height)
	{
		color = *(unsigned int *)(img->addr + (int)i_y * img->width + (int)i_x * (img->bpp / 8));
		my_mlx_pixel_put(*w_img, i_win % (w_img->width / 4),  i_win / (w_img->width / 4), color);
		i_x += step_x;
		if (i_win % (w_img->width / 4) == 0)
		{
			i_y += step_y;
			i_x = 0;
		}	
		i_win++;
	}
	mlx_put_image_to_window(get_mlx()->mlx, get_mlx()->win, w_img->img, 0, 0);
}
