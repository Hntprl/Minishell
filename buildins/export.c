/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:11:15 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 16:33:19 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_export(char *var_name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_memcmp(var_name, env[i], ft_super_strlen(env[i], '=')))
			return (free(env), 1);
		i++;
	}
	free(env);
	return (0);
}

void	export_printer(t_export **export, int end)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (i < end)
	{
		j = 0;
		while (j < end)
		{
			if ((*export)[j].index == i)
				printf("declare -x %s: %d\n", ((*export)[j].str),
					((*export)[j].index));
			j++;
		}
		i++;
	}
	free((*export));
}

void	export_indexer(t_export **export, int end)
{
	int	i;
	int	j;

	i = 0;
	while (i < end)
	{
		j = 0;
		(*export)[i].index = 0;
		while (j < end)
		{
			if (ft_strcmp((*export)[i].str, (*export)[j].str) > 0)
				(*export)[i].index++;
			j++;
		}
		i++;
	}
	export_printer(export, end);
}

void	print_export(t_list *env)
{
	int			i;
	t_export	*export;

	i = 0;
	export = malloc(sizeof(t_export) * ft_lstsize(env));
	if (!export)
		return ;
	while (env)
	{
		export[i].str = env->data;
		env = env->next;
		i++;
	}
	export_indexer(&export, i);
}

// export command .
void	ft_export_command(char **split, t_list **env)
{
	if (split[1] == NULL)
	{
		print_export((*env));
		return ;
	}
	if (!ft_isalpha(split[1][0]))
		printf("export: %s: not a valid identifier\n", split[1]);
	if (!ft_strchr(split[1], '='))
		return ;
	if (double_export(split[1], ft_list_to_str(*(env))))
	{
		ft_unset_command(split[1], env);
	}
	ft_lstadd_back(env, ft_lstnew(split[1]));
}
