
#include	"cub3d.h"

int	rotate_player(t_player player, int rot)
{
	player.rot += rot;
	return (player.rot);
}

/*t_vect	get_direction(float rot)
{
	t_vect	dir;
	
	
	dir.x = 

	vect
}*/

t_pos	move_pos(t_pos pos, float rot, float dist)
{
	t_pos	new_pos;
	
	new_pos.x = dist * cos(rot);
	new_pos.y = dist * sin(rot);
	new_pos.z = 0;

	return (new_pos);
}

// X=distance*cos(angle) +x0

// Y=distance*sin(angle) +y0