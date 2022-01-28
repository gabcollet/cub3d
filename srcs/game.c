/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:53:35 by fousse            #+#    #+#             */
/*   Updated: 2022/01/28 17:49:05 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{	
	g_game.mlx = get_mlx();
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.rot = 0;
	game->res_w = WIN_W;
	game->res_h = WIN_H;
	game->map = new_map();
	my_mlx_new_image(g_game.mlx->mlx, &game->game_img,
		game->res_w, game->res_h);
	init_textures(game);
}

void	destroy_img(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

void	exit_game(int exit_code)
{
	void	*mlx;

	mlx = g_game.mlx->mlx;
	mlx_destroy_window(mlx, g_game.mlx->win);
	destroy_img(mlx, g_game.mlx->img.img);
	destroy_img(mlx, g_game.texture[0].img);
	destroy_img(mlx, g_game.texture[1].img);
	destroy_img(mlx, g_game.texture[2].img);
	destroy_img(mlx, g_game.texture[3].img);
	destroy_img(mlx, g_game.game_img.img);
	destroy_img(mlx, g_game.map.back.img);
	exit(exit_code);
}
