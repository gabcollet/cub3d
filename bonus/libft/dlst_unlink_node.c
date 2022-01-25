/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_unlink_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:24:54 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 10:45:31 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

/*
*	Unlink $node from a double list, and return it.
*	It will link the previous and next nodes if needed.
*
*	if $node is the head of $dlst, the head of $dlst
*	will become the next node in that list.
*/
t_dlist	*dlst_unlink_node(t_dlist **dlst, t_dlist *node)
{
	if (dlst != NULL && *dlst == node)
		*dlst = (*dlst)->next;
	if (node == NULL)
		return (node);
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
