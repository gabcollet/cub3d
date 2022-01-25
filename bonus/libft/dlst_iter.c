/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:01:04 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/20 12:33:24 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

t_dlist	*dlst_iter(t_dlist *dlst, void *(iter)(void *), void *(d)(void *))
{
	t_dlist	*new_lst;
	t_dlist	*new_node;
	void	*content;

	new_lst = NULL;
	if (dlst == NULL)
		return (NULL);
	while (dlst != NULL && dlst->content != NULL)
	{
		content = iter(dlst->content);
		if (content == NULL)
			return (dlst_clear(new_lst, d));
		new_node = dlst_new_node(content);
		dlst_add_back(&new_lst, new_node);
		dlst = dlst->next;
	}
	return (new_lst);
}
