/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:56:06 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/30 00:51:18 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd command .
void	ft_pwd_command(void)
{
	char	buf[4096];
	printf("%s\n", getcwd(buf, 4096));
}

char *ft_find_env_value(char *var_name, char **env, int *is_invalid)
{
	char *var;
	int i;

	i = 0;
	if (var_name[0] != '$')
		return (NULL);
	var_name = (var_name + 1);
	while (env[i])
	{
		var = ft_substr(env[i], 0, ft_super_strlen(env[i], '='));
		if (!ft_memcmp(var_name, var, ft_strlen(var)))
			return ((free(var), ft_strchr(env[i], '=') + 1));
		free(var);
		i ++;
	}
	return ((*is_invalid) = 1, "1");
}
