/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:37 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 12:29:02 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static int	ft_init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "fract-ol");
	vars->img.img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
					&vars->img.bpp, &vars->img.line_length, &vars->img.endian);
	// mlx_key_hook(vars->win, ft_keyhandler, vars);
	// mlx_mouse_hook(vars->win, ft_mousehandler, vars);
	return (1);
}

int	main(void)
{
	t_vars	vars;

	ft_init_mlx(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
