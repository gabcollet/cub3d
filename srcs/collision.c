
#include	"cub3d.h"

t_coll	new_collider(t_pos pos, int type)
{
	t_coll	collider;

	collider.pos = pos;
	collider.type = type;
	return (collider);
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
	return (0);
}