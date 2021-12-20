/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:37 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 12:39:15 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static int	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "fract-ol");
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, \
					&mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	// mlx_key_hook(mlx->win, ft_keyhandler, mlx);
	// mlx_mouse_hook(mlx->win, ft_mousehandler, mlx);
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	ft_init_mlx(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
