/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:50:29 by fousse            #+#    #+#             */
/*   Updated: 2021/12/31 15:52:34 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	init_game(t_game *game)
{
	int tiles[64] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,1,0,1,
		1,0,1,0,0,1,0,1,
		1,0,0,0,1,0,0,1,
		1,0,1,0,1,0,1,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	int tiles_coll[64] = {
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
	};
	game->player.pos.x = 190;
	game->player.pos.y = 121;
	game->player.rot = 90;
	game->player.hp = 100;
	game->map.width = 8;
	game->map.size = 64;
	game->map.height = 8;
	game->map.tiles = copy_map(tiles, 64);
	game->map.tiles_coll = copy_map(tiles_coll, 64);
	game->mlx = get_mlx();
	mlx_get_screen_size(game->mlx->mlx, &game->screen_x, &game->screen_y);
	mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
}

void	exit_game(t_game *game, int exit_code)
{
	game = NULL;
	exit(exit_code);
}
