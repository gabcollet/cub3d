/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:21:45 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/25 17:59:41 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_free_array(void **ptr, void *(f)(void *))
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return (NULL);
	if (ptr != NULL && ptr[i] != NULL)
		ft_array_clear(ptr, f);
	ft_free(ptr);
	return (NULL);
}
