
#include	"cub3d.h"

int	rotate_player(t_player *player, double rot)
{
	if (player->rot + rot >= 360)
		player->rot = fmod((player->rot + rot), (double)360);
	else if (player->rot + rot < 0)
		player->rot = 360 - fmod(fabs((player->rot + rot)), (double)360);
	else
		player->rot += rot;
	return (player->rot);
}

/*t_vect	get_direction(double rot)
{
	t_vect	dir;
	
	
	dir.x = 

	vect
}*/

// X=distance*cos(angle) +x0

// Y=distance*sin(angle) +y0