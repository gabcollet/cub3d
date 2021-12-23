
#include	"cub3d.h"

t_coll	new_collider(t_pos pos, int type)
{
	t_coll	collider;

	collider.pos = pos;
	collider.type = type;
	return (collider);
}

int	check_inter(t_pos inter)
{
	t_map	map;
	int 	i_x;
	int 	i_y;

	map = g_game.map;
	i_x = inter.x / TILE_SIZE;
	i_y = inter.y / TILE_SIZE;
	//printf("ix = %d \n", i_x);
	//printf("iy = %d \n", i_y);
	if (i_x >= map.width && i_y >= map.height)
		return (1);
	if (i_x < 0 || i_y < 0)
		return (1);
	if ((int)inter.x % TILE_SIZE == 0 && i_x != 0)
		if (map.map[i_x - 1 + (i_y * map.width)] == 1)
			return (1);
	if (map.map[i_x + (i_y * map.width)] == 1)
		return (1);
	if ((int)inter.y % TILE_SIZE == 0 && i_y != 0)
		if (map.map[i_x + ((i_y - 1) * map.width)] == 1)
			return (1);
	if (map.map[i_x + (i_y * map.width)] == 1)
		return (1);
	return (0);
}

t_pos	check_all_inter(t_pos inter1, t_pos inter2, int step_x, int step_y)
{
	while (1)
	{
		if (check_inter(inter1) == 1)
			return (inter1);
		else if (check_inter(inter2) == 1)
			return (inter2);
		else
		{
			inter1.y += step_y;
			inter1.x += step_x;
			inter2.y += step_y;
			inter2.x += step_x;
		}
	}
	return (inter1);
}

t_pos	check_collisions(int x, int y, int rot)
{
	int		map_x;
	int		*map;
	t_pos	coll;
	int		d_x;
	int		d_y;
	int		c_x;
	int		c_y;
	int		x_step;
	int		y_step;
	int		i;
	t_pos	inter_y;
	t_pos	inter_x;

	map = g_game.map.map;
	map_x = g_game.map.width;
	d_x = x % TILE_SIZE;
	d_y = y % TILE_SIZE;
	coll = new_pos(0, 0, 0);
	if (rot >= 270 && rot <= 360)
	{
		//inter_y.x = x + (-d_y / tan(deg_to_rad((int)rot)));
		//inter_y.y = y - d_y;
		
		inter_x.x = x - d_x + TILE_SIZE;
		inter_x.y = y + (-d_x * tan(deg_to_rad((int)rot)));
		
		// while (1)
		// {	
		// 	if (check_inter(inter_y) == 1)
		// 		break ;
		// 	else
		// 	{
		// 		inter_y.x += (-TILE_SIZE / tan(deg_to_rad((int)rot)));
		// 		inter_y.y += -TILE_SIZE;
		// 	}
		while (check_inter(inter_x) != 1)
		{	
			inter_x.x += TILE_SIZE;
			inter_x.y -= (TILE_SIZE / tan(deg_to_rad((int)rot)));
		}
	}
	return (inter_x);
}

int	check_collision_x(int x, int y, int size)
{
	int		map_x;
	int		*map;

	map = g_game.map.map;
	map_x = g_game.map.width;
	if (map[x / TILE_SIZE + (y / TILE_SIZE * map_x)] == 1)
		return (1);
	if (map[(x + size) / TILE_SIZE + (y / TILE_SIZE * map_x)] == 1)
		return (1);
	if (map[(x) / TILE_SIZE + ((y + size) / TILE_SIZE * map_x)] == 1)
		return (1);
	if (map[(x + size) / TILE_SIZE + ((y + size) / TILE_SIZE * map_x)] == 1)
		return (1);
	/*if (x / TILE_SIZE > map_x || map[x / TILE_SIZE + y / TILE_SIZE * map_x] == 1)
		return (1);
	if ((x + size) / TILE_SIZE > map_x || map[(x + size) / TILE_SIZE + y / TILE_SIZE * map_x] == 1)
		return (1);
	if ((x) / TILE_SIZE > map_x || map[(x) / TILE_SIZE + (y + size) / TILE_SIZE * map_x] == 1)
		return (1);
	if ((x + size) / TILE_SIZE > map_x || map[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map_x] == 1)
		return (1);*/
	return (0);
}

int	check_collision_y(int x, int y, int size)
{
	int		map_y;
	int		*map;

	map = g_game.map.map;
	map_y = g_game.map.height;
	if (map[x / TILE_SIZE + y / TILE_SIZE * map_y] == 1)
		return (1);
	if (map[x / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);
	if (map[(x) / TILE_SIZE + (y) / TILE_SIZE * map_y] == 1)
		return (1);
	if (map[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);
	/*if (y / TILE_SIZE > map_y || map[x / TILE_SIZE + y / TILE_SIZE * map_y] == 1)
		return (1);
	if ((y + size) / TILE_SIZE > map_y || map[x / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);
	if ((y) / TILE_SIZE > map_y || map[(x) / TILE_SIZE + (y) / TILE_SIZE * map_y] == 1)
		return (1);
	if ((y + size) / TILE_SIZE > map_y || map[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);*/
	return (0);
}