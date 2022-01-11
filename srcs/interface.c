/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 19:47:53 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	init_sprite(t_sprite *sprite)
{
	sprite->active = 0;
	sprite->anim_countdown = 0;
	sprite->anim_time = 0;
	sprite->frames_n = 0;
	sprite->playing = 0;
	sprite->scaling = 1;
}

void	load_sprite(t_img *img, char *path)
{
	t_mlx	*mlx;
	mlx = get_mlx();

	img->img = mlx_xpm_file_to_image(mlx->mlx, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->width, &img->endian);
}

void	gun_update(t_obj *gun)
{
	if (gun->sprite.playing)
		update_animation(&gun->sprite);
}

// need to be reworked so it works with the parse. this is for testing purpose
void	init_interface(t_obj *objs) //To be reworked
{	
	t_img	*img;

	init_sprite(&objs[UI_GUN].sprite);
	img = &objs[UI_GUN].sprite.frames[0];
	load_sprite(img, "./sprites/handgun/gun_01.xpm");
	objs[UI_GUN].pos = new_pos(WIN_W / 2 - (img->width / 8), WIN_H - (img->height), 0);
	objs[UI_GUN].sprite.scaling = 4.0;
}
