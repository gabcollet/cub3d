/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/12 17:34:40 by gcollet          ###   ########.fr       */
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


double enemy_rot(double enemy_dist, t_pos enemy_pos, t_pos pos)
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
		rot = 360 - rot;
	//printf("rot enemy : %f", rot);
	return (rot);
}

/*
*	Check collisions and draw pixel columns based on collisions.
*	Can also visually represent raycast in a 2d image.
*/
int	raycast_draw_all(t_pos pos, double rot, double view)
{
	int		win_x;
	float	dist;
	double	base_rot;
	t_coll	coll;

	t_obj	*enemy;
	int		id = 0;
	/* t_coll	coll_enemy; */

	enemy = (char *)g_game.enemies;
	enemy[0].pos = new_pos(80.0, 80.0, 0);
	enemy[0].dist = 0;
	enemy[0].rot = 0;
	enemy[0].visible = 0;
	enemy[0].alive = 1;
	enemy[0].enabled = 1;

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	win_x = 0;
	base_rot = rot;
	//printf("rot player : %f  ", rot);
	/* while(id < 1 && enemy[id].enabled && enemy[id].alive)
	{ */
		enemy[id].dist = sqrt(pow((enemy[id].pos.x - pos.x), 2) + pow((enemy[id].pos.y - pos.y), 2));
		enemy[id].rot = enemy_rot(enemy[id].dist, enemy[id].pos, pos);
		if (enemy[id].rot > (rot - (view/2)) && enemy[id].rot < (rot + (view/2)))
			enemy[id].visible = TRUE;
		else if ((rot + view / 2) > 360 && enemy[id].rot < (rot + (view/2) - 360))
			enemy[id].visible = TRUE;
		else
			enemy[id].visible = FALSE;
		printf("  visible : %d\n", enemy[id].visible);
	/* 	id++;
	} */
	/* coll_enemy.obj = &enemy[id];
	coll_enemy.pos = enemy[id].pos;
	coll_enemy.type = ENEMY; */
	rot -= view / 2;
	while (win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		dist = get_draw_distance(pos, rot, coll.pos, base_rot - rot);
		draw3d(dist, coll, WIN_W - win_x);
		
		if (enemy[0].visible == TRUE
			&& ((int)enemy[0].rot - (int)(enemy[0].sprite.frames->width / 2) < (int)rot
				 && (int)enemy[0].rot + (int)(enemy[0].sprite.frames->width / 2) > (int)rot))
		{
			if (enemy[id].dist < dist)
			{
				dist = get_draw_distance(pos, rot, enemy[id].pos, base_rot - rot);
				//draw_enemy(&enemy[id].sprite.frames[0], enemy[id].pos, dist, textures_index(enemy[id].pos, 0, dist, 0));
				draw_enemy(&enemy[id].sprite.frames[0], new_pos(win_x, (WIN_H - dist) / 2, 0), dist, textures_index(enemy[id].pos, 0, dist, 0));
			}
			 /* id++; */
		}
		
		win_x += 1;
		rot += (view / WIN_W);
	}
	return (1);
}

// Literally draw a raycast on the mlx image
int	raycast_draw(t_pos pos, double rot, double dist, int color)
{
	t_pos	r_pos;
	int		i;

	i = 0;
	r_pos = new_pos(pos.x, pos.y, pos.z);
	while (i++ < dist && i < 800)
	{
		my_mlx_pixel_put(g_game.game_img, r_pos.x, r_pos.y, color);
		r_pos = move_pos(r_pos, rot, 1, 0);
	}
	return (1);
}
