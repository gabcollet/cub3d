/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:53:59 by fousse            #+#    #+#             */
/*   Updated: 2022/01/04 22:14:02 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(void)
{
	
	parse_cub("maps/square.cub");
	printf("%s", g_game.map.tiles);
	return(0);
	



	/*int	p = 0;;
	printf("valid %d\n", parse_valid_map_line("1000101", &p));
	printf("empty %d\n", parse_valid_map_line("", &p));
	printf("not enclosed %d\n", parse_valid_map_line("100010", &p));
	printf("not enclosed %d\n", parse_valid_map_line("000101", &p));
	printf("valid spaces %d\n", parse_valid_map_line("     10001", &p));
	printf("valid spaces %d\n", parse_valid_map_line("     101  101" , &p));
	printf("invalid spaces %d\n", parse_valid_map_line("     10 01" , &p));
	printf("1 player %d\n", parse_valid_map_line("     1N01" , &p));
	printf("player count = %d\n", p);
	printf("2 players %d\n", parse_valid_map_line("     1N S1" , &p));
	printf("player count = %d\n", p);*/
}