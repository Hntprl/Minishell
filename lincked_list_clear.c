/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lincked_list_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:43:29 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/01 02:45:04 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_size(t_list **lst, void (*del)(void *), int size)
{
	t_list	*dlt;

	if (!lst || !del)
		return ;
	dlt = NULL;
	while (size)
	{
		dlt = (*lst)->next;
		if (dlt->next)
			(*lst)->next = dlt->next;
		else
			(*lst)->next = NULL;
		del(dlt);
		size --;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst -> data);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (!lst || !del)
		return ;
	while ((*lst) != NULL)
	{
		p = (*lst)-> next;
		ft_lstdelone(*lst, del);
		free(*lst);
		(*lst) = p;
	}
}

void	del(void *lst)
{
	free(lst);
}
