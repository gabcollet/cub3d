/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/11 13:19:23 by fousse           ###   ########.fr       */
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
	enemy_update(&g_game.ui_elems[ENEMY]);
	gun_update(&g_game.ui_elems[UI_GUN]);
	draw_ui(mlx);
	//draw_map2d(mlx, g_game.map);
	move_player();
	//mlx_fill_window(&mlx->img, &g_game.game_img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, g_game.game_img.img, 0, 0);
	//mlx_do_sync(mlx->mlx);
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
	g_game.map.back = create_background(g_game.res_w, g_game.res_h);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_hook(mlx->win, 17, 0, quit_handler, NULL);
	mlx_loop_hook(mlx->mlx, game, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}