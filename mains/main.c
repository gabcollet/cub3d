/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/02/11 12:02:08 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	game(void *ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ptr;
	move_player();
	draw_background(g_game.map.back);
	raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
	mlx_put_image_to_window(mlx->mlx, mlx->win, g_game.game_img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2)
		return (parse_error(ERR_ARGC));
	init_game(&g_game);
	if (argv[1] && parse_cub(argv[1]) <= 0)
		return (0);
	mlx = get_mlx();
	g_game.map.back = create_background(WIN_W, WIN_H * 4);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook (mlx->mlx, game, mlx);
	mlx_loop (mlx->mlx);
	return (0);
}
