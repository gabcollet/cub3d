/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/20 18:02:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*
*	Draw a column of pixel based on a tile/wall.
*/
int	draw3d(float height, t_coll coll, int x)
{
	int		y;
	float	offset;

	offset = 0;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	if (coll.dir & NORTH)
		fill_with_texture(&g_game.texture[NO], new_pos(x, y, 0),
			height, textures_index(coll.pos, offset, height, 1));
	else if (coll.dir & SOUTH)
		fill_with_texture(&g_game.texture[SO], new_pos(x, y, 0),
			height, textures_index(coll.pos, offset, height, 1));
	else if (coll.dir & WEST)
		fill_with_texture(&g_game.texture[WE], new_pos(x, y, 0),
			height, textures_index(coll.pos, offset, height, 0));
	else if (coll.dir & EAST)
		fill_with_texture(&g_game.texture[EA], new_pos(x, y, 0),
			height, textures_index(coll.pos, offset, height, 0));
	return (0);
}

int	raycast_draw_enemies(t_obj *enemy, double height, double rot, int win_x)
{
	t_sprite	*sprite;

	sprite = &enemy->sprite;
	if (sprite->drawing == FALSE && enemy->visible == TRUE)
	{
		if (angle_is_between(rot, enemy->rot - ((enemy->rot_side - enemy->rot) / 2.0), enemy->rot_side))
		{
			sprite->x_step = sprite->frames[0].height / enemy->dist;
			sprite->i_x = enemy_get_index(*enemy, *sprite, rot);
			sprite->drawing = TRUE;
		}
	}
	if (sprite->drawing == TRUE)
	{
		if (enemy->dist >= height && sprite->i_x < sprite->frames[0].width 
			/ 4)
			draw_object(get_mlx(), &enemy->sprite, WIN_W - win_x, enemy->dist);
		sprite->i_x += sprite->x_step;
	}
	return (1);
}

int	raycast_draw_doors(t_door *door, double height, double rot, int win_x)
{
	t_sprite	*sprite;
	double		door_height;

	sprite = &door->sprite;
	
	if ((door->rot < 90 && door->rot_side > 270) && (rot <= door->rot || rot >= door->rot_side))
	{
		sprite->i_x = door_get_index(*door, *sprite, rot);
		if (rot < 90)
			door_height = door->dist + ((door->dist_side - door->dist) * ((rot - door->rot) / (door->rot_side - (door->rot + 360))));
		else
			door_height = door->dist + ((door->dist_side - door->dist) * ((rot - (door->rot + 360)) / (door->rot_side - (door->rot + 360))));
		if (door_height >= height && sprite->i_x < sprite->frames[0].width / 4)
			draw_object(get_mlx(), &door->sprite, win_x, door_height);
	}
	else if (!(door->rot < 90 && door->rot_side > 270) && ((door->rot <= door->rot_side && angle_is_between(rot, door->rot, door->rot_side))
				|| ((door->rot >= door->rot_side && angle_is_between(rot, door->rot_side, door->rot)))))
	{
		sprite->i_x = door_get_index(*door, *sprite, rot);
		door_height = door->dist + ((door->dist_side - door->dist) * ((rot - door->rot) / (door->rot_side - (door->rot))));
		if (door_height >= height && sprite->i_x < sprite->frames[0].width / 4)
			draw_object(get_mlx(), &door->sprite, win_x, door_height);
	}
	return (1);
}

void	draw_sprites(double height, double rot, int win_x)
{
	int		i;
	double	i_dist;
	int		i_draw;
	int		id;
	double	smallest;
	
	i = 0;
	smallest = 0;
	while (i < (g_game.enemy_count + g_game.door_count))
	{
		id = 0;
		i_dist = 20000000.0;
		while (id < g_game.enemy_count)
		{
			if (g_game.enemies[id].dist < i_dist && g_game.enemies[id].dist > smallest)
			{
				i_dist = g_game.enemies[id].dist;
				i_draw = id;
			}
			id++;
		}
		id = 0;
		while (id < g_game.door_count)
		{
			if (g_game.doors[id].dist < i_dist && g_game.doors[id].dist > smallest)
			{
				i_dist = g_game.doors[id].dist;
				i_draw = id;
			}
			id++;
		}
		smallest = i_dist;
		if (i_draw < g_game.enemy_count && (double)g_game.enemies[i_draw].dist == i_dist)
			raycast_draw_enemies(&g_game.enemies[i_draw], height, rot, win_x);
		else if (i_draw < g_game.door_count && (double)g_game.doors[i_draw].dist == i_dist)
			raycast_draw_doors(&g_game.doors[i_draw], height, rot, WIN_W - win_x);
		i++;
	}
}

/*
*	Check collisions and draw pixel columns based on collisions.
*	Can also visually represent raycast in a 2d image.
*/
int	raycast_draw_all(t_pos pos, double rot, double view)
{
	int		win_x;
	double	height;
	double	base_rot;
	t_coll	coll;

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	win_x = 0;
	base_rot = rot;
	obj_all_set_visible(g_game.enemies, g_game.enemy_count, base_rot, pos);
	doors_set_visible(g_game.doors, g_game.door_count, base_rot, pos);
	rot -= VIEW_ANGLE / 2;
	while (win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		height = get_draw_distance(pos, rot, coll.pos, base_rot - rot);
		draw3d(height, coll, WIN_W - win_x);
		draw_sprites(height, rot, win_x);
		win_x += 1;
		rot += (view / WIN_W);
	}
	reset_drawings();
	return (1);
}

// Literally draw a raycast on the mlx image
int	raycast_draw(double rot, double dist, int color, int side)
{
	t_pos	facing;
	t_pos	r_pos;
	int		i;
	int		trans;

	trans = FALSE;
	if (color == WHITE)
		trans = TRUE;
	facing.x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S);
	facing.y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S);
	i = 0;
	r_pos = new_pos(facing.x, facing.y, facing.z);
	while (i++ < dist && i < 800)
	{
		if (trans == TRUE)
			color = color_shift_int(color_get(g_game.game_img, r_pos.x, r_pos.y), WHITE, 0.03);
		my_mlx_pixel_put(g_game.game_img, r_pos.x, r_pos.y, color);
		r_pos = move_pos(r_pos, rot, side, 0);
	}
	return (1);
}
