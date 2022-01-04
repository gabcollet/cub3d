/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/03 14:35:16 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1000
#define HEIGHT 500

#include "cub3d.h"
#include "mlx.h"

/*void	draw_texture(t_img *win, t_img *text, int x, int y, double scale)
{
	double	i_x;
	double	i_y;
	double	x_step;
	double	y_step;
	int		base_x;
	int	color;

	i_x = fmod(x, (text->width * scale / 4));
	i_y = 0;
	x_step = 1.0 / scale;
	y_step = 1.0 / scale;
	base_x = x;
	while (i_y < text->height && y < win->height)
	{
		color = *((unsigned int *)(text->addr + ((int)i_y * text->width + (int)i_x * (text->bpp / 8))));
		if (x >= 0)
			my_mlx_pixel_put(*win, x, y, color);
		i_x += x_step;
		x++;
		if ((int)i_x * (text->bpp / 8) >= text->width || x >= win->width)
		{
			i_x = base_x % (text->width / 4);
			i_y += y_step;
			y++;
			x = base_x;
		}	
	}
}*/

// This draws from left to right and can be changed to do a vertical column.
void	fill_with_texture(t_img *win, t_img *text, int x, int y, double scale)
{
	double	i_x;
	double	i_y;
	double	x_step;
	double	y_step;
	int		bytes;
	int		base_x;
	int		color;

	// initial i_x and i_y are based on the initial x and y position
	i_x = fmod(x, (text->width * scale / bytes));
	i_y = fmod(y, (text->height * scale));

	// This is the step. it will be used to draw the same pixel multiple times or to skip pixels.
	x_step = 1.0 / scale;
	y_step = 1.0 / scale;

	// Bytes is the size of each element in the img->addr array.
	bytes = (text->bpp / 8);
	base_x = x;
	while (y < win->height)
	{
		// The color of a pixel in a mlx image is the unsigned int value at the right address
		color = *((unsigned int *)(text->addr + ((int)i_y * text->width + (int)i_x * bytes)));
		
		// Prevents out of bound, but it is already handled in my_mlx_pixel_put
		if (x >= 0 && x < win->width)
			my_mlx_pixel_put(*win, x, y, color);

		//The fmod will "reset" the texture x_index so it can redraw itself from the beginning.
		i_x += x_step;
		i_x = fmod(i_x, text->width / bytes);

		x++;
		if (x >= win->width / bytes)
		{
			// this resets the texture indexes so it begins at the right place
			i_x = fmod(base_x, (text->width * scale / bytes));
			i_y += y_step;
			i_y = fmod(i_y, (text->height));
			y++;
			x = base_x;
		}	
	}
}

/* void	draw_texture(t_img *win, t_img *text, int x, int y, double scale)
{
	double	i_x;
	double	i_y;
	double	x_step;
	double	y_step;
	int		base_x;
	int		bytes;
	int	color;

	i_x = 0;
	i_y = 0;
	x_step = 1.0 / scale;
	y_step = 1.0 / scale;
	bytes = (text->bpp / 8);
	base_x = x;
	while (i_y < text->height && y < win->height)
	{
		color = *((unsigned int *)(text->addr + ((int)i_y * text->width + (int)i_x * bytes)));
		if (x >= 0)
			my_mlx_pixel_put(*win, x, y, color);
		i_x += x_step;
		x++;
		if (x >= win->width / bytes || i_x >= text->width / bytes)
		{
			i_x = 0;
			i_y += y_step;
			y++;
			x = base_x;
		}		
	}
} */

int 	main(void)
{
	t_mlx	*mlx;
	t_img	texture;
	int		i = 0;
	int		x = 0;

	mlx = get_mlx();
	texture.img = mlx_xpm_file_to_image(mlx->mlx, "textures/T_1.xpm", &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp,
				&texture.width, &texture.endian);

	// draw_texture draws an image at a location with a specific scaling.
	//draw_texture(&mlx->img, &texture, 1, 1, 1);

	// fill_with_texture will fill the entire window with the texture with a specific scaling
	fill_with_texture(&mlx->img, &texture, 1, 1, 10);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	//mlx_put_image_to_window(mlx->mlx, mlx->win, texture.img, 0, 0);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_loop(mlx->mlx);	
	return (0);
}