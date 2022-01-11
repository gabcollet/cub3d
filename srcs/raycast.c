/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:50:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/11 16:36:20 by gcollet          ###   ########.fr       */
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
			height, textures_index(coll, offset, height, 1));
	else if (coll.dir & SOUTH)
		fill_with_texture(&g_game.texture[SO], new_pos(x, y, 0),
			height, textures_index(coll, offset, height, 1));
	else if (coll.dir & WEST)
		fill_with_texture(&g_game.texture[WE], new_pos(x, y, 0),
			height, textures_index(coll, offset, height, 0));
	else if (coll.dir & EAST)
		fill_with_texture(&g_game.texture[EA], new_pos(x, y, 0),
			height, textures_index(coll, offset, height, 0));
	return (0);
}

//fonction qui trouve la rot des ennemies selon la pos du player et la pos de la rot 0 
//(trouver un angle a partir de 3 points)
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

	coll = new_collider(new_pos(0, 0, 0), 0, 0);
	win_x = 0;
	base_rot = rot;
	rot -= view / 2;
	
	/* while(enemy[id])
	{
		enemy[id].dist = sqrt(pow((enemy[id].pos.x - pos.x), 2) + pow((enemy[id].pos.y - pos.y), 2));
		enemy[id].rot = enemy_rot(enemy[id].dist, enemy[id].pos, pos);
		if (enemy[id].rot < rot += view/2 && enemy[id].rot > rot -= view/2)
			enemy[id].visible = TRUE;
		else
			enemy[id].visible = FALSE;
		id++;
	} */

	while (win_x < WIN_W)
	{
		if (rot >= 360)
			rot = fmod(rot, 360);
		if (rot < 0)
			rot = 360.0 + rot;
		coll = check_intersections(pos.x, pos.y, rot);
		dist = get_draw_distance(pos, rot, coll.pos, base_rot - rot);
		draw3d(dist, coll, WIN_W - win_x);
		
		/* while(enemy[id])
		{
			if (enemy[id].visible && enemy[id].dist < dist)
				//fonction qui collide avec la hit box du monstre pour connaitre son Y
				//fonction qui dessine une collone selon la dist et selon la hit box du mob
			id++;
		} */
		
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
