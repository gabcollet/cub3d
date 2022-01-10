/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:53:35 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 16:28:44 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{	
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.rot = 0;
	game->player.hp = 100;
	game->screen_x = WIN_W;
	game->screen_y = WIN_H;
	game->map = new_map();
	init_textures(game);
	init_interface(game->ui_elems); // unfinished
}

void	exit_game(t_game *game, int exit_code)
{
	game = NULL; //va servir a faire les images destroy
	exit(exit_code);
}
