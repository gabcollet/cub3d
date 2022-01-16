/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/16 03:06:56 by fousse           ###   ########.fr       */
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
	while (d.y >= 0 && d.y < WIN_H - y && x >= 0 && x < WIN_W && d.index_y < img.height)
	{
		color = color_get(img, (int)obj->sprite.i_x, (int)d.index_y);
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		my_mlx_pixel_put(g_game.game_img, x, d.y, color);
		d.index_y += d.step;
		d.y++;
	}		
}

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
	int			view;
	t_pos		side_pos;
	t_obj		*obj;

	id = 0;
	view = VIEW_ANGLE / 2;
    while(id < array_size && objs[id].alive)
    {
		obj = &objs[id];
        obj->dist = sqrt(pow((obj->pos.x - base_pos.x), 2) + pow((obj->pos.y - base_pos.y), 2));
        obj->rot = obj_rot(obj->dist, obj->pos, base_pos);
		side_pos = move_pos(obj->pos, rotate(obj->rot, 90.0), obj->sprite.frames[0].width / 4.0, 0);
		obj->dist_side = math_pytha(side_pos.x - base_pos.x, side_pos.y - base_pos.y);
		//sqrt(pow((side_pos.x - base_pos.x), 2) + pow((side_pos.y - base_pos.y), 2));
		obj->rot_side = obj_rot(obj->dist_side, side_pos, base_pos);
        if (obj->rot >= (rot - view) && obj->rot <= (rot + view))
            obj->visible = TRUE;
		else if ((rot + view) >= 360 && obj->rot <= (rot + view - 360))
            obj->visible = TRUE;
        else if (obj->rot_side >= (rot - view) && obj->rot_side <= (rot + view))
            obj->visible = TRUE;
		else
            obj->visible = FALSE;       
		if (obj->visible == TRUE)
			obj->dist = get_draw_distance(base_pos, rot, obj->pos, 0); 
		//printf("visible : %d | p.rot : %f | e.rot : %f e_siderot %f\n", obj->visible, rot, objs[id].rot, objs[id].rot_side);
		id++;
    }
}
