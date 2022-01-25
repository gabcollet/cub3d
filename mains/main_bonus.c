/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 17:13:41 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"

int	game(void *ptr)
{
	t_mlx			*mlx;
	static double	frame_timer = 0;

	mlx = (t_mlx *)ptr;
	if (frame_timer <= 0)
	{
		// mouse_handler(0, 0);
		move_player();
		enemies_update(g_game.enemies);
		doors_update(g_game.doors);
		gun_update(&g_game.ui_elems[UI_GUN]);
		draw_background(g_game.map.back);
		raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
		draw_ui();
		if (g_game.toggle_map == 1)
			draw_map2d(g_game.map);
		mlx_put_image_to_window(mlx->mlx, mlx->win, g_game.game_img.img, 0, 0);
		frame_timer = 1.0 / FPS;
	}
	else
		frame_timer -= get_frame_time();
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2)
		return (parse_error(ERR_ARGC));
	init_game(&g_game);
	if (!parse_cub(argv[1]))
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
