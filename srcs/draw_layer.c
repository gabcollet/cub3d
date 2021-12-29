/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_layer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2021/12/29 10:12:39 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

/*void drawTile(t_mlx *mlx, int x, int y, int type)
{
	int	index_x;
	int index_y;

	index_x = x;
	index_y = y;
	while (index_y < (y + TILE_SIZE))
	{
		index_x = x;
		while (index_x < (x + TILE_SIZE))
		{
			if (index_y % 50 == 0 || index_x % 50 == 0)
				my_mlx_pixel_put(mlx->img, index_x, index_y, RED);
			else if (type == WALL)
				my_mlx_pixel_put(mlx->img, index_x, index_y, WHITE);
			else if (type == PLAYER)
				my_mlx_pixel_put(mlx->img, index_x, index_y, 0x000040);
			index_x++;
		}
		index_y++;
	}
}*/

void	drawMap3D(t_mlx *mlx, t_map map)
{
	draw_background(mlx->img);
	/*int 	x, y;
	t_pos	p_pos;

	p_pos = g_game.player.pos;
	for (y=0; y<map.height; y++)
	{
		for (x=0; x<map.width; x++)
		{
			if (map.tiles[y*map.width+x]==1)
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, WALL);
			else if (x==(int)p_pos.x / TILE_SIZE && y==(int)p_pos.y / TILE_SIZE)
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, PLAYER);
			else
				drawTile(mlx, x * TILE_SIZE, y * TILE_SIZE, FLOOR);
		}
	}*/
}

void	draw_background(t_img img)
{
	int		x;
	int 	y;
	int		color;
	double	shift_force;

	x = 0;
	y = 0;
	while (x + y * img.width < img.width * img.height)
	{
		color = CEILING_C;
		shift_force = (double)(y % (img.height / 2)) / (double)(img.height / 2);
		if (y >= img.height / 2)
		{
			color = FLOOR_C;
			shift_force = (double)1 - shift_force;
		}
		color = color_shift_int(color, BLACK, shift_force);
		my_mlx_pixel_put(img, x, y, color);	
		x++;
		if (x == img.width)
		{
			x = 0;
			y++;
		}
	}
	return (0);	
}

/*int	draw_tiles(t_mlx *mlx)
{
	t_pos	start;
	t_pos	pixel;
	int		rot;

	


}*/

int	draw_sprites(t_mlx *mlx)
{

}

int	draw_UI(t_mlx *mlx)
{

}
