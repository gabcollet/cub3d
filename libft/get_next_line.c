/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:34:32 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/04 22:05:16 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	get_next_line(char **line, int fd)
{
	char	*buffer;
	char	*temp;
	int		i;
	int		r;
	char	c;

	buffer = (char *)malloc(41);
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
		if (r > 0 && i % 40 == 0)
		{
			temp = buffer;
			buffer = (char *)malloc(i + 41);
			ft_strlcat(buffer, temp, i);
			free(temp);
		}

	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}
