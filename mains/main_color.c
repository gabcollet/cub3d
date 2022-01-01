/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:06:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/29 09:44:31 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_rgb(t_rgb rgb)
{
	int	color;

	color = color_rgb_to_int(rgb);
	printf("print_rgb : int%d r%d g%d b%d\n", color, rgb.r, rgb.g, rgb.b);
}
void	print_int(int color)
{
	t_rgb	rgb;

	rgb = color_int_to_rgb(color);
	printf("print_int : int%d r%d g%d b%d\n", color, rgb.r, rgb.g, rgb.b);
}

int main(void)
{
	int		color;
	t_rgb	rgb;

	color = 0x554466;
	print_int(color);
	color = color_shift_int(color, 0xFFFFFF, 1);
	print_int(color);
	

	return (0);
}