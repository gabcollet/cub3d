/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/15 17:00:04 by gcollet          ###   ########.fr       */
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

int	raycast_draw_sprite(double height, double rot, int win_x)
{
	t_obj	*enemy;
	int		id;

	enemy = g_game.enemies;
	id = 0;
	while (id < 1)
	{
		if (enemy[id].sprite.drawing == FALSE && enemy[id].visible == TRUE && (int)enemy[id].rot == (int)rot)
		{
			enemy[id].sprite.x_step = enemy[id].sprite.frames[0].height / enemy[id].dist;
			enemy[id].sprite.i_x = 0;
			enemy[id].sprite.drawing = TRUE;
		}
		
		//ca fonctionne mais pas tant
		else if (enemy[id].sprite.drawing == FALSE && enemy[id].visible == FALSE)
		{
			enemy[id].sprite.i_x = 0;
			enemy[id].sprite.x_step = enemy[id].sprite.frames[0].height / enemy[id].dist;
			while (enemy[id].sprite.i_x <= enemy[id].sprite.frames[0].width / 4)
			{
				enemy[id].sprite.i_x += enemy[id].sprite.x_step;
				rot -= ((double)VIEW_ANGLE / (double)WIN_W);
				if ((int)enemy[id].rot == (int)rot)
				{
					enemy[id].sprite.drawing = TRUE;
					break ;
				}
			}
		}
		
		if (enemy[id].sprite.drawing == TRUE)
		{
			if (enemy[id].dist >= height)
				draw_object(get_mlx(), &enemy[id], WIN_W - win_x);
			enemy[id].sprite.i_x += enemy[id].sprite.x_step;
			if (enemy[id].sprite.i_x >= enemy[id].sprite.frames[0].width / 4)
				enemy[id].sprite.drawing = FALSE;
		}
		id++;
	}
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
	win_x = 0;
	base_rot = rot;
	obj_all_set_visible(g_game.enemies, g_game.enemy_count, base_rot, pos);
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
		raycast_draw_sprite(height, rot, win_x);
		win_x += 1;
		rot += (view / WIN_W);
	}
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
