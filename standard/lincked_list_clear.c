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

#include "../minishell.h"

char	**ft_list_to_str(t_list *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = env->data;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

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
