/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/10 16:45:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

int game(void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx *)ptr;
	//frame_timer = MLX_CD / FPS;
	mouse_handler(0, 0);
	//mlx_clear_img(mlx->img);
	draw_background(g_game.map.back);
	raycast_draw_all(g_game.player.pos, g_game.player.rot, VIEW_ANGLE);
	draw_ui(mlx);
	drawMap2D(mlx, g_game.map);
	move_Player();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	//mlx_do_sync(mlx->mlx);
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx *mlx;

	if (argc != 2)
		return (parse_error(ERR_ARGC));
	mlx = get_mlx();
	g_game.mlx = mlx;
	init_game(&g_game);
	if (!parse_cub(argv[1]))
		return (0);
	g_game.map.back = create_background(WIN_W, WIN_H);
	mlx_get_screen_size(mlx->mlx, &g_game.screen_x, &g_game.screen_y);
	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook(mlx->mlx, game, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}