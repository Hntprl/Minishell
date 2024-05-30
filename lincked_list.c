/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lincked_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:47:51 by amarouf           #+#    #+#             */
/*   Updated: 2024/05/30 09:00:19 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *content)
{
	int i;
	t_list	*node;
	char	*var;

	i = 0;
	var = malloc(ft_strlen(content));
	while (content[i])
	{
		var[i] = content[i];
		i++;
	}	
	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node -> data = content;
	node -> next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
		last -> next = new;
	new -> next = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst -> data);
}

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

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst -> next;
		i ++;
	}
	return (i);
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
		(*lst) = p;
	}
}

void del(void *lst)
{
	free(lst);
}
