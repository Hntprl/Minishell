/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:11:15 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/25 16:35:23 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int double_export(char *var_name, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_memcmp(var_name, env[i], ft_super_strlen(env[i], '=')))
            return (free(env), 1);
        i ++;
    }
    free(env);
    return (0);
}

// export command .
void	ft_export_command(char **split, t_list **env)
{
	if (split[1] == NULL)
	{
		ft_env_command((*env), 1);
		return;
	}
    if (!ft_isalpha(split[1][0]))
        printf("export: %s: not a valid identifier\n", split[1]);
    if (!ft_strchr(split[1], '='))
        return;
    if (double_export(split[1], ft_list_to_str(*(env))))
    {        
        ft_unset_command(split, env);
    }
	ft_lstadd_back(env, ft_lstnew(split[1]));
}