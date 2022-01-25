/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:34:32 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/24 17:30:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	get_next_line(char **line, int fd)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	i = 0;
	r = read(fd, &c, 1);
	while (r > 0 && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		r = read(fd, &c, 1);
		i++;
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}
