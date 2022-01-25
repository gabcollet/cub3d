/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:34:25 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/24 16:11:15 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

// Free $ptr if not NULL, and return NULL
void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
