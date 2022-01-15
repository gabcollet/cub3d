/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/14 21:40:09 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_obj_draw
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
}				t_obj_draw;

t_obj	new_obj(void)
{
	t_obj	obj;

	obj.alive = FALSE;
	obj.pos = new_pos(0,0,0);
	obj.rot = 0;
	obj.dist = 0;
	obj.type = 0;
	obj.update = NULL;
	obj.visible = FALSE;
	return (obj);
}

void	init_obj_array(t_obj *obj, int size)
{
	if (!obj)
		return ;
	while (size-- > 0)
	{
		*obj = new_obj();
		obj++;
	}
}

void	draw_object(t_mlx *mlx, t_obj *obj, int x)
{
	t_obj_draw	d;
	int			color;
	t_img		img;
	int		y;
	float	offset;
	double	height;

	offset = 0;
	height = obj->dist;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	img = obj->sprite.frames[obj->sprite.active];
	d.index_y = 0;
	d.index_x = 0;
	d.x = x;
	d.y = y;
	d.step = (double)img.height / height;
	//printf("in draw x : %d\n", d.x);
	while (d.y >= 0 && d.y < WIN_H - y && x >= 0 && x < WIN_W)
	{
		
		/*color = *((unsigned int *)(img.addr
					+ ((int)d.index_y * img.width + (int)obj->sprite.i_x * 4)));*/
		color = color_get(img, (int)obj->sprite.i_x, (int)d.index_y);
		//color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		if (x >= 0 && x < WIN_W)
			my_mlx_pixel_put(g_game.game_img, x, d.y, color);
		d.index_y += d.step;
		d.y++;
	}		
/*
	while (d.index_y < img.height)
	{
		d.x = obj->pos.x;
		d.index_x = 0;
		while (d.index_x < img.width / 4)
		{
			color = color_get(img, (int)d.index_x, (int)d.index_y);
			my_mlx_pixel_put(g_game.game_img, (int)d.x, (int)d.y, color);
			d.index_x += d.step;
			d.x++;
		}
		d.y++;
		d.index_y += d.step;
	}*/
}

/*void	draw_object(t_mlx *mlx, t_obj *obj, int x)
{
	t_obj_draw	d;
	int			color;
	t_img		img;
	int		y;
	float	offset;
	double	height;

	offset = 0;
	height = obj->dist;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	img = obj->sprite.frames[obj->sprite.active];
	d.index_y = 0;
	d.index_x = 0;
	d.x = x;
	d.y = y;
	d.step = (double)img.height / height;
	while (d.index_x < img.width / 4)
	{
		color = color_get(img, (int)d.index_x, (int)d.index_y);
		//color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		if (x >= 0 && x < WIN_W)
			my_mlx_pixel_put(g_game.game_img, d.x, d.y, color);
		d.index_y += d.step;
		d.y++;
		if (d.y >= height + y)
		{
			d.y = y;
			d.index_y = 0;
			d.index_x += d.step;
			d.x++;
		}		
	}
/*
	while (d.index_y < img.height)
	{
		d.x = obj->pos.x;
		d.index_x = 0;
		while (d.index_x < img.width / 4)
		{
			color = color_get(img, (int)d.index_x, (int)d.index_y);
			my_mlx_pixel_put(g_game.game_img, (int)d.x, (int)d.y, color);
			d.index_x += d.step;
			d.x++;
		}
		d.y++;
		d.index_y += d.step;
	}
}*/

double obj_rot(double enemy_dist, t_pos enemy_pos, t_pos pos)
{
	double rot;
	double dist_A;
	double dist_B;
	double dist_C;
	
	dist_A = enemy_dist;
	dist_B = sqrt(pow((pos.x - pos.x + 5), 2));
	dist_C = sqrt(pow((enemy_pos.x - (pos.x + 5)), 2) + pow((enemy_pos.y - pos.y), 2));
	rot = acosf((pow(dist_A, 2) + pow(dist_B, 2) - pow(dist_C, 2)) / (2 * dist_A * dist_B));
	rot = rad_to_deg(rot);
	if (pos.y < enemy_pos.y)
		rot = 360.0 - rot;
	return (rot);
}

void    obj_all_set_visible(t_obj *objs, int array_size, double rot, t_pos base_pos)
{
    int			id;
	t_pos		side_pos;

	id = 0;
    while(id < array_size && objs[id].alive)
    {
        objs[id].dist = sqrt(pow((objs[id].pos.x - base_pos.x), 2) + pow((objs[id].pos.y - base_pos.y), 2));
        objs[id].rot = obj_rot(objs[id].dist, objs[id].pos, base_pos);
		// side_pos = move_pos(objs[id].pos, rotate(objs[id].rot, -90.0), objs[id].sprite.frames[0].width / 4.0, 0);
		// objs[id].rot_side = obj_rot( sqrt(pow((side_pos.x - base_pos.x), 2) + pow((side_pos.y - base_pos.y), 2)), side_pos, base_pos);
        if (objs[id].rot > (rot - (VIEW_ANGLE/2)) && objs[id].rot < (rot + (VIEW_ANGLE/2)))
            objs[id].visible = TRUE;
        else if ((rot + VIEW_ANGLE / 2) > 360 && objs[id].rot < (rot + (VIEW_ANGLE/2) - 360))
            objs[id].visible = TRUE;
        else
            objs[id].visible = FALSE;
		if (objs[id].visible == TRUE)
			objs[id].dist = get_draw_distance(base_pos, rot, objs[id].pos, 0); 
		id++;
    }
}
