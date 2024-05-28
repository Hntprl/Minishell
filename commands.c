/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:56:06 by amarouf           #+#    #+#             */
/*   Updated: 2024/05/28 06:26:02 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_command(char **split)
{
	free_strings(split);
	char buf[225];
	printf("%s\n", getcwd(buf, 225));
}

void	ft_cd_command(char **split)
{
	chdir(split[1]);
}

void	ft_echo_command(char **split)
{
	if (!ft_memcmp(split[1], "-n", 3))
		printf("%s%%",split[2]);
	else
		printf("%s\n",split[1]);
}

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