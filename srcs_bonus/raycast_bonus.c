/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2024/12/04 00:04:58 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	raycast_draw_enemies(t_obj *enemy, double height, double rot, int w_x)
{
	t_sprite	*s;

	s = &enemy->sprite;
	if (s->drawing == FALSE && enemy->visible == TRUE)
	{
		if (enemy_ray_hit(enemy, rot))
		{
			s->x_step = s->frames[0].height / enemy->dist * 2;
			s->i_x = enemy_get_index(*enemy, *s, rot);
			s->drawing = TRUE;
		}
	}
	if (s->drawing == TRUE)
	{	
		s->i_x = enemy_get_index(*enemy, *s, rot);
		if (enemy->dist >= height && s->i_x < s->frames[0].width
			/ 4 && s->i_x >= 0)
			draw_object(s, WIN_W - w_x, enemy->dist);
	}
	return (1);
}

int	raycast_draw_doors(t_door *door, double height, double rot, int w_x)
{
	t_sprite	*sprite;
	double		door_height;

	sprite = &door->sprite;
	door_height = door_get_height(door, rot);
	sprite->i_x = door_get_index(*door, *sprite, rot);
	if (door_height >= height && sprite->i_x < sprite->frames[0].width / 4)
		draw_object(&door->sprite, w_x, door_height);
	return (1);
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
	win_x = -1;
	base_rot = rot;
	obj_all_set_visible(g_game.enemies, g_game.enemy_count, base_rot, pos);
	doors_set_visible(g_game.doors, g_game.door_count, base_rot, pos);
	rot -= VIEW_ANGLE / 2;
	while (++win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		height = get_draw_distance(pos, rot, coll.pos, base_rot - rot);
		draw3d(height, coll, WIN_W - win_x);
		draw_sprites(height, rot, win_x);
		rot += (view / WIN_W);
	}
	reset_drawings();
	return (1);
}

// Literally draw a raycast on the mlx image. Use for minimap.
int	raycast_draw(double rot, double dist, int color, int side)
{
	t_pos	facing;
	t_pos	r_p;
	int		i;
	int		trans;
	t_img	img;

	img = g_game.game_img;
	trans = FALSE;
	if (color == WHITE)
		trans = TRUE;
	facing.x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S);
	facing.y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S);
	facing.z = 0;
	i = 0;
	r_p = new_pos(facing.x, facing.y, facing.z);
	while (i++ < dist && i < 800)
	{
		if (trans == TRUE)
			color = color_shift_int(color_get(img, r_p.x, r_p.y), WHITE, 0.03);
		my_mlx_pixel_put(img, r_p.x, r_p.y, color);
		r_p = move_pos(r_p, rot, side, 0);
	}
	return (1);
}
