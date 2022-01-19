/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:53:35 by fousse            #+#    #+#             */
/*   Updated: 2022/01/18 14:35:04 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{	
	g_game.mlx = get_mlx();
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.rot = 0;
	game->player.hp = 100;
	game->player.gravity = GRAVITY;
	game->player.vel_z = 0;
	game->res_w = WIN_W;
	game->res_h = WIN_H;
	game->map = new_map();
	my_mlx_new_image(g_game.mlx->mlx, &game->game_img,
		game->res_w, game->res_h);
	init_textures(game);
	init_interface(game->ui_elems);
	init_doors(game->doors);
	init_obj_array(game->enemies, MAX_ENEMY);
	game->enemy_count = 0;
	game->door_count = 0;
}

void	exit_game(t_game *game, int exit_code)
{
	game = NULL; //va servir a faire les images destroy
	exit(exit_code);
}
