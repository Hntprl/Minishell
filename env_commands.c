/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:41:11 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/01 02:41:55 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_command(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
}

void	ft_export_command(char **split, t_list *env)
{
	ft_lstadd_back(&env, ft_lstnew(split[1]));
}

void	ft_unset_command(char **split, t_list *env)
{
	while (env)
	{
		if (!ft_memcmp(env->next->data, split[1], ft_strlen(split[1])))
			ft_lstclear_size(&env, del, 1);
		env = env->next;
	}
}
