/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:41:11 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 16:50:24 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env command .
void	ft_env_command(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
}

void	unset_checker(t_list **current
				, t_list **prev, t_list **env)
{
	t_list	*dlt;

	dlt = (*current);
	if ((*prev))
		(*prev)->next = (*current)->next;
	else
		(*env) = (*current)->next;
	(*current) = (*current)->next;
	ft_lstdelone(dlt);
}

// unset command .
void	ft_unset_command(char *split, t_list **env)
{
	t_list	*prev;
	char	**name;
	t_list	*current;
	int		var_len;

	prev = NULL;
	current = (*env);
	while (current)
	{
		name = ft_split(current->data, '=');
		var_len = ft_strlen(name[0]);
		free_strings(name);
		if (!ft_memcmp(split, current->data, var_len))
			unset_checker(&current, &prev, env);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
