/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

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
	sprite->frames_n = 15;
	sprite->anim_time = 1;
	sprite->scaling = 3.0;
	sprite->playing = FALSE;
	sprite->loop = FALSE;
	sprite->rewind = TRUE;
}

void	init_doors(t_door *doors)
{	
	int	i;

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
	t_pos		act_pos;
	int			tile_i;
	int			p_tile_i;
	int			i;
	t_plyr		p;

	p = g_game.player;
	act_pos = move_pos(p.pos, p.rot, TILE_SIZE / 2.0, 0);
	p_tile_i = ((int)p.pos.x / (int)TILE_SIZE)
		+ ((int)p.pos.y / (int)TILE_SIZE * g_game.map.width);
	tile_i = ((int)act_pos.x / (int)TILE_SIZE)
		+((int)act_pos.y / (int)TILE_SIZE * g_game.map.width);
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
		door->pos.y = i_y * TILE_SIZE + (TILE_SIZE / 2);
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
