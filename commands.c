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

char	*ft_find_env_value(char *var_name, char **env, int *is_invalid)
{
	char	*var;
	int		i;

	i = 0;


	if (var_name[0] != '$')
		return (NULL);
	var_name = (var_name + 1);
	while (env[i])
	{
		var = ft_substr(env[i], 0, ft_super_strlen(env[i], '='));
		if (!ft_strcmp(var_name, var))
			return ((free(var), ft_strchr(env[i], '=') + 1));
		free(var);
		i++;
	}
	return ((*is_invalid) = 1, "1");
}

int	ft_expand_pid(int i, char *var_name)
{
	if (var_name[i + 1] == '?' || var_name[i + 1] == '$')
	{
		while (var_name[i] && var_name[i + 1])
		{
			while (var_name[i] == '$' && var_name[i + 1] == '?')
			{
				printf("%d", ft_status(0, false));
				i += 2;
			}
			while (var_name[i] == '$' && var_name[i + 1] == '$')
			{
				printf("%d", ft_getpid());
				i += 2;
			}
			if (var_name[i] != '$' || (var_name[i + 1] != '$' && var_name[i + 1] != '?'))
				break;
		}
		if (!var_name[i])
			return (printf(": No such file or directory\n"),ft_status(127, true), -1337);
	}
	return (i);
}

int	ft_expander(char *var_name, char **env)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!var_name[1])
		return (printf("%s\n", "$: command not found"));
	i = ft_expand_pid(i, var_name);
	if (i == -1337)
		return (1337);
	var_name += (i + 1);
	while (env[j])
	{
		var = ft_substr(env[j], 0, ft_super_strlen(env[j], '='));
		if (!ft_strcmp(var_name, var))
			return ((free(env), free(var)
					, printf("%s: No such file or directory\n"
						, ft_strchr(env[j], '=') + 1)));
		free(var);
		j++;
	}
	if (var_name[i - 1] != '$')
		printf("%s: No such file or directory\n", (var_name - 1));
	free(env);
	return (1);
}

void	ft_dup_close(int std_out, int std_in)
{
	if(dup2(std_out, 1) == -1 || close(std_out) == -1)
		(ft_malloc(0, 'f', false), exit(1));
	if (dup2(std_in, 0) == -1 || close(std_in) == -1)
		(ft_malloc(0, 'f', false), exit(1));
}
