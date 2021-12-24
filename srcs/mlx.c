/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:17:29 by fousse            #+#    #+#             */
/*   Updated: 2021/12/24 13:33:54 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

t_mlx	*get_mlx(void)
{
	static t_mlx mlx;
	
	if (mlx.init != 1)
	{
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "Cub3D");
		mlx.img.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
		mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp,
					&mlx.img.width, &mlx.img.endian);
		mlx.img.height = WIN_H;
		mlx.init = 1;
	}
	return(&mlx);
}
