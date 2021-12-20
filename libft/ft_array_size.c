/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:40:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/09 19:52:11 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

/* 
* Count the amount of element in a NULL-terminated array.
*
* if count reaches INT_MAX, it will return -1;
* this is to prevent an endless loop if the array is not terminated
*/
int	ft_array_size(void **arr)
{
	int	count;

	count = 0;
	while (arr && *arr)
	{
		arr++;
		count++;
		if (count == INT_MAX)
			return (-1);
	}
	return (count);
}
