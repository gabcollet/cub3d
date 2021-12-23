
#include	"cub3d.h"

t_coll	new_collider(t_pos pos, int type)
{
	t_coll	collider;

	collider.pos = pos;
	collider.type = type;
	return (collider);
}

int	check_collision_x(int plyr_x, int plyr_y)
{
	int		map_x;
	int		*map;

	map = g_game.map.map;
	map_x = g_game.map.width;
	if (plyr_x / TILE_SIZE > map_x || map[plyr_x / TILE_SIZE + plyr_y / TILE_SIZE * map_x] == 1)
		return (1);
	if ((plyr_x + 10) / TILE_SIZE > map_x || map[(plyr_x + 10) / TILE_SIZE + plyr_y / TILE_SIZE * map_x] == 1)
		return (1);
	if ((plyr_x) / TILE_SIZE > map_x || map[(plyr_x) / TILE_SIZE + (plyr_y + 10) / TILE_SIZE * map_x] == 1)
		return (1);
	if ((plyr_x + 10) / TILE_SIZE > map_x || map[(plyr_x + 10) / TILE_SIZE + (plyr_y + 10) / TILE_SIZE * map_x] == 1)
		return (1);
	return (0);
}
int	check_collision_y(int plyr_x, int plyr_y)
{
	int		map_y;
	int		*map;

	map = g_game.map.map;
	map_y = g_game.map.height;
	if (plyr_y / TILE_SIZE > map_y || map[plyr_x / TILE_SIZE + plyr_y / TILE_SIZE * map_y] == 1)
		return (1);
	if ((plyr_y + 10) / TILE_SIZE > map_y || map[plyr_x / TILE_SIZE + (plyr_y + 10) / TILE_SIZE * map_y] == 1)
		return (1);
	if ((plyr_y) / TILE_SIZE > map_y || map[(plyr_x + 10) / TILE_SIZE + (plyr_y) / TILE_SIZE * map_y] == 1)
		return (1);
	if ((plyr_y + 10) / TILE_SIZE > map_y || map[(plyr_x + 10) / TILE_SIZE + (plyr_y + 10) / TILE_SIZE * map_y] == 1)
		return (1);
	return (0);
}