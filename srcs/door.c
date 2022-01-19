/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/19 17:37:46 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
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

void	init_door_sprite(t_sprite *sprite)
{	
	init_sprite(sprite);
	load_sprite(&sprite->frames[0], "./sprites/door/door_1.xpm");
	load_sprite(&sprite->frames[1], "./sprites/door/door_2.xpm");
	load_sprite(&sprite->frames[2], "./sprites/door/door_3.xpm");
	load_sprite(&sprite->frames[3], "./sprites/door/door_4.xpm");
	load_sprite(&sprite->frames[4], "./sprites/door/door_5.xpm");
	load_sprite(&sprite->frames[5], "./sprites/door/door_6.xpm");
	load_sprite(&sprite->frames[6], "./sprites/door/door_7.xpm");
	load_sprite(&sprite->frames[7], "./sprites/door/door_8.xpm");
	load_sprite(&sprite->frames[8], "./sprites/door/door_9.xpm");
	load_sprite(&sprite->frames[9], "./sprites/door/door_10.xpm");
	load_sprite(&sprite->frames[10], "./sprites/door/door_11.xpm");
	load_sprite(&sprite->frames[11], "./sprites/door/door_12.xpm");
	load_sprite(&sprite->frames[12], "./sprites/door/door_13.xpm");
	load_sprite(&sprite->frames[13], "./sprites/door/door_14.xpm");
	load_sprite(&sprite->frames[14], "./sprites/door/door_15.xpm");
	//load_sprite(&sprite->frames[15], "./sprites/door/door_16.xpm");
	sprite->frames_n = 15;
	sprite->anim_time = 1;
	sprite->scaling = 3.0;
	sprite->playing = FALSE;
	sprite->loop = FALSE;
	sprite->rewind = TRUE;
}

void	init_doors(t_door *doors)
{	
	int i;

	i = 0;
	while (i < MAX_DOOR)
	{
		doors[i].opened = FALSE;
		doors[i].pos = new_pos(0, 0, 0);
		doors[i].face_rot = 0;
		doors[i].rot = 0;
		doors[i].rot_side = 0;
		doors[i].dist = 0;
		doors[i].dist_side = 0;
		doors[i].tile_i = 0;
		i++;
	}
}

void	doors_update(t_door *doors)
{
	int	id;

	id = 0;
	while (id < g_game.door_count)
	{
		if (doors[id].sprite.playing)
			update_door(&doors[id]);
		id++;
	}
}

void	interact_door(void)
{
	t_pos	act_pos;
	int		tile_i;
	int		p_tile_i;
	int		i;

	act_pos = move_pos(g_game.player.pos, g_game.player.rot, TILE_SIZE / 2.0, 0);
	p_tile_i = ((int)g_game.player.pos.x / (int)TILE_SIZE) + 
		((int)g_game.player.pos.y / (int)TILE_SIZE * g_game.map.width);
	tile_i = ((int)act_pos.x / (int)TILE_SIZE) + 
		((int)act_pos.y / (int)TILE_SIZE * g_game.map.width);
	if (tile_i >= g_game.map.width * g_game.map.height || tile_i == p_tile_i
		|| tile_i < 0)
		return ;
	if (g_game.map.tiles[tile_i] == M_DOOR)
	{
		i = 0;
		while (i < g_game.door_count)
		{
			if (g_game.doors[i].tile_i == tile_i)
				return (open_door(&g_game.doors[i]));
			i++;
		}
	}	
}

void	place_door(t_door *door, int face_rot, int i_x, int i_y)
{	
	door->pos.x = i_x * TILE_SIZE;
	door->pos.y = i_y * TILE_SIZE;
	if (face_rot == 0)
		door->pos.y = i_y * TILE_SIZE + (TILE_SIZE / 2 );
	else if (face_rot == 270)
		door->pos.x = i_x * TILE_SIZE + (TILE_SIZE / 2);
	door->face_rot = face_rot;
	door->rot = 0;
	door->rot_side = 0;
	door->dist = 0;
	door->dist_side = 0;
	door->tile_i = i_x + (i_y * g_game.map.width);
	init_door_sprite(&door->sprite);
}


//va devenir le nouveaum draw_object
void	draw_door(t_mlx *mlx, t_sprite *sprite, int x, double height)
{
	t_obj_draw	d;
	int			color;
	t_img		img;
	int			y;
	float		offset;

	offset = 0;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	img = sprite->frames[sprite->active];
	d.index_y = (TEXTURES_SIZE * offset / 2) / (height + offset);
	d.y = y;
	d.step = (double)img.height / (height + offset);
	while (d.y >= 0 && d.y < WIN_H - y && x >= 0 && x < WIN_W && d.index_y < img.height)
	{
		color = color_get(img, (int)sprite->i_x, (int)d.index_y);
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		my_mlx_pixel_put(g_game.game_img, x, d.y, color);
		d.index_y += d.step;
		d.y++;
	}
}

double	door_get_index(t_door door, t_sprite sprite, double angle)
{
	double	min;
	double	max;
	double	i_x;
	double	scaled_w;

	min = door.rot;
	max = door.rot_side;
	if (min < 90 && max > 270)
	{
		if (angle < 90)
			i_x = (int)((sprite.frames[0].width / 4.0) * ((min - angle) / (min + 360.0 - max)));
		else
			i_x = (int)((sprite.frames[0].width / 4.0) * ((min + 360.0 - angle) / (min + 360.0 - max)));
	}
	else
	{
		if (min > max)
		{
			min = door.rot_side;
			max = door.rot;
		}
		if (max < min)
		{
			if (angle <= max)
				angle += 360;
			max += 360;
		}
		i_x = (int)((sprite.frames[0].width / 4.0) * ((angle - min) / (max - min)));
	}
	return (i_x);
}

void    doors_set_visible(t_door *doors, int size, double rot, t_pos base_pos)
{
    int			i;
	int			view;
	t_pos		side_pos;
	t_door		*door;

	i = 0;
	view = VIEW_ANGLE;
    while(i < size)
    {
		door = &doors[i];
		door->visible = FALSE;
        door->dist = sqrt(pow((door->pos.x - base_pos.x), 2) + pow((door->pos.y - base_pos.y), 2));
        door->rot = obj_rot(door->dist, door->pos, base_pos);
		if (door->face_rot == 0)
			side_pos = new_pos(door->pos.x + 50, door->pos.y, 0);
		else
			side_pos = new_pos(door->pos.x, door->pos.y + 50, 0);
		door->dist_side = math_pytha(side_pos.x - base_pos.x, side_pos.y - base_pos.y);
		door->rot_side = obj_rot(door->dist_side, side_pos, base_pos);
		// if (angle_is_between(rot, door->rot, door->rot_side))
		// 	door->visible = TRUE;
        if (door->rot >= (rot - view) && door->rot <= (rot + view))
            door->visible = TRUE;
		else if ((rot + view) >= 360 && door->rot <= (rot + view - 360))
            door->visible = TRUE;
        else if (door->rot_side >= (rot - view) && door->rot_side <= (rot + view))
            door->visible = TRUE;              
		if (door->visible == TRUE)
		{
			door->dist = get_draw_distance(base_pos, g_game.player.rot, door->pos, 0); 
			door->dist_side = get_draw_distance(base_pos, g_game.player.rot, side_pos, 0); 
		}
		i++;
    }
}
