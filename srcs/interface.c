/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/17 14:49:01 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifndef S_OBJ_DRAW
# define S_OBJ_DRAW
typedef struct s_obj_draw
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
}				t_obj_draw;
#endif

void	init_sprite(t_sprite *sprite)
{
	sprite->active = 0;
	sprite->anim_countdown = 0;
	sprite->anim_time = 0;
	sprite->frames_n = 0;
	sprite->playing = FALSE;
	sprite->scaling = 1;
	sprite->loop = FALSE;
	sprite->drawing = FALSE;
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
}

void	draw_ui(t_mlx *mlx)
{
	t_obj	*obj;

	obj = g_game.ui_elems;
	draw_ui_element(mlx, &obj[UI_GUN]);
}

void	draw_ui_element(t_mlx *mlx, t_obj *obj)
{
	t_obj_draw	d;
	int			color;
	t_img		img;

	img = obj->sprite.frames[obj->sprite.active];
	d.step = 1.0 / obj->sprite.scaling;
	d.index_y = 0;
	d.index_x = 0;
	d.x = obj->pos.x;
	d.y = obj->pos.y - (double)img.height * obj->sprite.scaling;
	while (d.index_y < img.height)
	{
		if (d.index_x < img.width / 4)
		{
			color = color_get(img, (int)d.index_x, (int)d.index_y);
			my_mlx_pixel_put(g_game.game_img, (int)d.x, (int)d.y, color);
			d.index_x += d.step;
			d.x++;
		}
		else if (d.index_x <= img.width / 4)
		{
			d.y++;
			d.index_y += d.step;
			d.x = obj->pos.x;
			d.index_x = 0;
		}
	}
}
