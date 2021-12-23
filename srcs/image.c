
#include	"cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_W || y > WIN_H || x <= 0 || y <= 0)
		return ;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bpp / 8));
	*(unsigned int*)dst = color;
}

void	mlx_clear_img(t_mlx *mlx)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < WIN_W * WIN_H)
	{
		dst = mlx->img.addr + (i * (mlx->img.bpp / 8));
		*(unsigned int*)dst = 0;
		i++;
	}
}
