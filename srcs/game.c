/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:53:35 by fousse            #+#    #+#             */
/*   Updated: 2022/01/07 13:01:40 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	init_game(t_game *game)
{	
	int i;
	//static char *TEXTURE[4] = {"textures/T_1.xpm", "textures/T_2.xpm",\
							"textures/T_3.xpm", "textures/T_4.xpm"};
	//minecraft set :
 	/*static char *TEXTURE[4] = {"textures/bricks.xpm", "textures/cobblestone.xpm",\
							"textures/grass_block_side.xpm", "textures/oak_planks.xpm"}; 
*/
	i = 0;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.rot = 0;
	game->player.hp = 100;
	game->screen_x = WIN_W;
	game->screen_y = WIN_H;
	game->map = new_map();
	init_textures(game);
	init_interface(game->ui_elems); // unfinished
	
	/* while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx->mlx, TEXTURE[i], &game->texture[i].width, &game->texture[i].height);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bpp,
					&game->texture[i].width, &game->texture[i].endian);
		i++;
	} */
}

void	exit_game(t_game *game, int exit_code)
{
	game = NULL;
	exit(exit_code);
}
