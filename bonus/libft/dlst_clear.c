/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:24:54 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 11:23:27 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*dlst_clear(t_dlist *dlst, void *(d)(void *))
{
	if (dlst == NULL)
		return (NULL);
	if (dlst->next)
		dlst_clear(dlst->next, d);
	if (d)
		d(dlst->content);
	ft_free(dlst);
	return (NULL);
}

void	*dlst_clear_node(t_dlist **dlst, t_dlist *node, void *(d)(void *))
{
	dlst_unlink_node(dlst, node);
	if (d && node->content)
		d(node->content);
	return (ft_free(node));
}
