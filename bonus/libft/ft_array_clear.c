/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:21:45 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/25 18:28:27 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

/*
*	Apply $f and set to NULL the content of a null-terminated array.
*	It require an array with free-able content.
*/
void	*ft_array_clear(void **ptr, void *(f)(void *))
{
	while (ptr && *ptr && f)
	{
		*ptr = f(*ptr);
		ptr++;
	}
	return (NULL);
}
