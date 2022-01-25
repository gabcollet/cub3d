/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:24:54 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 10:45:11 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

// Return a malloced node with $content as its content.
t_dlist	*dlist_new_node(void *content)
{
	t_dlist	*node;

	node = (t_dlist *)malloc(sizeof(t_dlist));
	if (node == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
