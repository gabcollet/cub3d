/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:57:26 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 19:56:35 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	color_get(t_img img, int x, int y)
{
	int	color;
	
	if (x >= img.width / 4 || y >= img.height)
		return (0);
	color = *((unsigned int *)(img.addr
					+ y * img.width + x * (img.bpp / 8)));
	return (color);

}

int	color_valid_rgb(t_rgb rgb)
{
	if (rgb.r > 255 || rgb.r < 0)
		return (0);
	if (rgb.g > 255 || rgb.g < 0)
		return (0);
	if (rgb.b > 255 || rgb.b < 0)
		return (0);
	return (1);

}

int	color_rgb_to_int(t_rgb rgb)
{
	int	color_int;

	color_int = rgb.r << 16 | rgb.g << 8 | rgb.b;
	return (color_int);
}

t_rgb	color_int_to_rgb(int color)
{
	t_rgb	rgb;

	rgb.r = get_r(color);
	rgb.g = get_g(color);
	rgb.b = get_b(color);
	return (rgb);
}

int	color_shift_int(int base, int shift, double force)
{
	t_rgb	rgb;
	t_rgb	base_rgb;
	t_rgb	shift_rgb;

	base_rgb = color_int_to_rgb(base);
	shift_rgb = color_int_to_rgb(shift);
	rgb = color_shift_rgb(base_rgb, shift_rgb, force);
	return (color_rgb_to_int(rgb));
}

t_rgb	color_shift_rgb(t_rgb base, t_rgb shift, double force)
{
	t_rgb	new;

	new.r = base.r + ((shift.r - base.r) * force);
	new.g = base.g + ((shift.g - base.g) * force);
	new.b = base.b + ((shift.b - base.b) * force);
	return (new);
}
