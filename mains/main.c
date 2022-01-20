/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/19 20:16:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

int game(void *ptr)
{
	t_mlx *mlx;
	static double	frame_timer = 0;
	static int	i;

	mlx = (t_mlx *)ptr;
	if (frame_timer <= 0)
	{
		//frame_timer = MLX_CD / FPS;
		mouse_handler(0, 0);
		//mlx_clear_img(mlx->img);
		enemies_update(g_game.enemies);
		doors_update(g_game.doors);
		gun_update(&g_game.ui_elems[UI_GUN]);
		move_player();
		draw_background(g_game.map.back);
		raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
		draw_ui(mlx);
		if (g_game.toggle_map == 1)
			draw_map2d(mlx, g_game.map);
		//mlx_fill_window(&mlx->img, &g_game.game_img);
		mlx_put_image_to_window(mlx->mlx, mlx->win, g_game.game_img.img, 0, 0);
		frame_timer = 1.0 / FPS;
	}
	else
		frame_timer -= get_frame_time();	
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx *mlx;

	if (argc != 2)
		return (parse_error(ERR_ARGC));
	init_game(&g_game);
	if (!parse_cub(argv[1]))
		return (0);
	mlx = get_mlx();
	g_game.map.back = create_background(WIN_W, WIN_H);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook(mlx->mlx, game, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}