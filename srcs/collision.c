
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
	d_x = TILE_SIZE - x % TILE_SIZE;
	d_y = y % TILE_SIZE;
	coll = new_pos(0, 0, 0);
	if (rot >= 0 && rot <= 90)
	{
		inter_y.x = x + (-d_y / tan(deg_to_rad((int)rot)));
		inter_y.y = y - d_y;
		inter_x.x = x + TILE_SIZE - d_x;
		inter_x.y = y - -d_x * tan(deg_to_rad((int)rot));
		x_step = TILE_SIZE;
		y_step = -TILE_SIZE;
		if (pow(inter_y.x, 2) + pow(inter_y.y, 2) < pow(inter_x.x, 2) + pow(inter_x.y, 2))
			coll = check_all_inter(inter_y, inter_x, x_step, y_step);
		else
			coll = check_all_inter(inter_x, inter_y, x_step, y_step);
	}
	/*if (rot >= 91 && rot <= 180)
	{
		inter_y.x = y - d_y;
		inter_y.y = -d_y / tan(deg_to_rad((int)rot));
		inter_x.x = x + TILE_SIZE - d_x;
		inter_x.y = -d_x * tan(deg_to_rad((int)rot));
		x_step = TILE_SIZE;
		y_step = TILE_SIZE;
		if ((pow(inter_y.x, 2) + pow(inter_y.y, 2) < (pow(inter_x.x, 2) + pow(inter_x.y, 2))))
			coll = check_all_inter(inter_y, inter_x, x_step, y_step);
		else
			coll = check_all_inter(inter_x, inter_y, x_step, y_step);
	}*/
	/*if (rot >= 0 && rot <= 90)
	{
		inter_y.x = y - d_y;
		inter_y.y = -d_y / tan(deg_to_rad((int)rot));
		inter_x.x = x + TILE_SIZE - d_x;
		inter_x.y = -d_x * tan(deg_to_rad((int)rot));
		x_step = TILE_SIZE;
		y_step = TILE_SIZE;
	}
	if (rot >= 0 && rot <= 90)
	{
		inter_y.x = y - d_y;
		inter_y.y = -d_y / tan(deg_to_rad((int)rot));
		inter_x.x = x + TILE_SIZE - d_x;
		inter_x.y = -d_x * tan(deg_to_rad((int)rot));
		x_step = TILE_SIZE;
		y_step = TILE_SIZE;
	}*/
	
	
	
	
	/*else if (rot >= 91 && rot <= 270)
		y_inter = y + TILE_SIZE - (TILE_SIZE - d_y);
	else
		y_inter = y + d_y;
	if (rot >= 181 && rot <= 360)
		x_inter = x + TILE_SIZE + (TILE_SIZE - d_x);
	else
		x_inter = x + TILE_SIZE - d_x;*/
	return (coll);
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