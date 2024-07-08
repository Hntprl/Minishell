/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:41:11 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/27 19:15:53 by amarouf          ###   ########.fr       */
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

// export command .
void	ft_export_command(char **split, t_list *env)
{
	ft_lstadd_back(&env, ft_lstnew(split[1]));
}

// unset command .
void	ft_unset_command(char **split, t_list **env)
{
	t_list	*prev;
	char	**name;
	t_list	*dlt;
	t_list	*current;
	int		var_len;

	current = (*env);
	dlt = NULL;
	prev = NULL;
	while (current)
	{
		name = ft_split(current->data, '=');
		var_len = ft_strlen(name[0]);
		free_strings(name);
		if (!ft_memcmp(split[1], current->data, var_len))
		{
			dlt = current;
			if (prev)
				prev->next = current->next;
			else
				(*env) = current->next;
			current = current->next;
			ft_lstdelone(dlt);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
