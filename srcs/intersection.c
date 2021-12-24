
#include	"cub3d.h"

int	check_inter_x(t_pos inter)
{
	t_map	map;
	int 	i_x;
	int 	i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.map[i_x + (i_y * map.width)] == 1)
		return (1);
	if (i_x > 0 && map.map[i_x - 1 + (i_y * map.width)] == 1)
		return (1);
	return (0);
}

int	check_inter_y(t_pos inter)
{
	t_map	map;
	int 	i_x;
	int 	i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.map[i_x + (i_y * map.width)] == 1)
		return (1);
	if (i_y > 0 && map.map[i_x + ((i_y - 1) * map.width)] == 1)
		return (1);
	return (0);
}

t_pos	check_intersections(int x, int y, int rot)
{
	int		d_x;
	int		d_y;
	t_pos	inter_y;
	t_pos	inter_x;

	d_x = x % TILE_SIZE;
	d_y = y % TILE_SIZE;
	if (rot >= 0 && rot <= 90)
	{
		inter_y.x = x + (d_y / tan(deg_to_rad((int)rot)));
		inter_y.y = y - d_y;
		
		inter_x.x = x - d_x + TILE_SIZE;
		inter_x.y = y - ((TILE_SIZE - d_x) * tan(deg_to_rad((int)rot)));
		while (1)
		{	
			if((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2)) < (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
			{
				if (check_inter_y(inter_y) == 1)
					return (inter_y) ;
				else
				{
					inter_y.x += (TILE_SIZE / tan(deg_to_rad((int)rot)));
					inter_y.y += -TILE_SIZE;
				}
			}
			else
			{
				if (check_inter_x(inter_x) == 1)
					return (inter_x) ;
				else
				{
					inter_x.x += TILE_SIZE;
					inter_x.y += (-TILE_SIZE * tan(deg_to_rad((int)rot)));
				}
			}
		}
	}
	else if (rot >= 91 && rot <= 180)
	{
		inter_y.x = x + (d_y / tan(deg_to_rad((int)rot)));
		inter_y.y = y - d_y;
		
		inter_x.x = x - d_x;
		inter_x.y = y + ((TILE_SIZE - (TILE_SIZE - d_x)) * tan(deg_to_rad((int)rot)));
		while (1)
		{	
			if((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2)) < (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
			{
				if (check_inter_y(inter_y) == 1)
					return (inter_y) ;
				else
				{
					inter_y.x += (TILE_SIZE / tan(deg_to_rad((int)rot)));
					inter_y.y += -TILE_SIZE;
				}
			}
			else
			{
				if (check_inter_x(inter_x) == 1)
					return (inter_x) ;
				else
				{
					inter_x.x += -TILE_SIZE;
					inter_x.y += (TILE_SIZE * tan(deg_to_rad((int)rot)));
				}
			}
		}
	}
	else if (rot >= 181 && rot <= 270)
	{
		inter_y.x = x - (TILE_SIZE - d_y) / tan(deg_to_rad((int)rot));
		inter_y.y = y + (TILE_SIZE - d_y);
		
		inter_x.x = x - d_x;
		inter_x.y = y + (TILE_SIZE - (TILE_SIZE - d_x)) * tan(deg_to_rad((int)rot));
		while (1)
		{	
			if((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2)) < (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
			{
				if (check_inter_y(inter_y) == 1)
					return (inter_y) ;
				else
				{
					inter_y.x -= (TILE_SIZE / tan(deg_to_rad((int)rot)));
					inter_y.y += TILE_SIZE;
				}
			}
			else
			{
				if (check_inter_x(inter_x) == 1)
					return (inter_x) ;
				else
				{
					inter_x.x += -TILE_SIZE;
					inter_x.y += (TILE_SIZE * tan(deg_to_rad((int)rot)));
				}
			}
		}
	}
	else if (rot >= 271 && rot <= 360)
	{
		inter_y.x = x + (-(TILE_SIZE - d_y) / tan(deg_to_rad((int)rot)));
		inter_y.y = y + (TILE_SIZE - d_y);
		
		inter_x.x = x + (TILE_SIZE - d_x);
		inter_x.y = y - (TILE_SIZE - d_x) * tan(deg_to_rad((int)rot));
		while (1)
		{	
			if((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2)) < (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
			{
				if (check_inter_y(inter_y) == 1)
					return (inter_y) ;
				else
				{
					inter_y.x += (-TILE_SIZE / tan(deg_to_rad((int)rot)));
					inter_y.y += TILE_SIZE;
				}
			}
			else
			{
				if (check_inter_x(inter_x) == 1)
					return (inter_x) ;
				else
				{
					inter_x.x += TILE_SIZE;
					inter_x.y += (-TILE_SIZE * tan(deg_to_rad((int)rot)));
				}
			}
		}
	}
	return (new_pos(0, 0, 0));
}
