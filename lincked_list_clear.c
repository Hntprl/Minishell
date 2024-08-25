/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lincked_list_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:43:29 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/03 05:01:42 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst)
		(free(lst->data), free(lst));
}

void	ft_lstclear(t_list **lst)
{
	t_list	*p;

	if (!lst)
		return ;
	while ((*lst) != NULL)
	{
		p = (*lst)->next;
		ft_lstdelone((*lst));
		(*lst) = p;
	}
}
