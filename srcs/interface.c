/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/12 15:00:59 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_sprite *sprite)
{
	sprite->active = 0;
	sprite->anim_countdown = 0;
	sprite->anim_time = 0;
	sprite->frames_n = 0;
	sprite->playing = FALSE;
	sprite->scaling = 1;
	sprite->loop = FALSE;
}

void	load_sprite(t_img *img, char *path)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	img->img = mlx_xpm_file_to_image(mlx->mlx, path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->width, &img->endian);
}

// need to be reworked so it works with the parse. this is for testing purpose
void	init_interface(t_obj *objs)
{	
	t_img	img;
	int		scaling;

	init_handgun(&objs[UI_GUN].sprite);
	init_enemy_sprite(&objs[ENEMY].sprite);
	
	img = objs[UI_GUN].sprite.frames[0];
	scaling = objs[UI_GUN].sprite.scaling;
	objs[UI_GUN].pos = new_pos(WIN_W / 2 - (img.width / 8 * scaling), WIN_H, 0);
	
	img = g_game.enemies[ENEMY].sprite.frames[0];
	scaling = g_game.enemies[ENEMY].sprite.scaling;
	//g_game.enemies[ENEMY].pos = new_pos(WIN_W / 2 - (img.width / 8 * scaling), WIN_H, 0);
	// img = objs[ENEMY].sprite.frames[0];
	// scaling = objs[ENEMY].sprite.scaling;
	// objs[ENEMY].pos = new_pos(WIN_W / 2 - (img.width / 8 * scaling), WIN_H, 0);
}

void	draw_ui(t_mlx *mlx)
{
	t_obj	*obj;

	obj = g_game.ui_elems;
	//draw_object(mlx, &g_game.enemies[0]); //just for testing
	draw_object(mlx, &obj[UI_GUN]);
}
