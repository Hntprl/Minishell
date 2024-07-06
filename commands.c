/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:56:06 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/06 16:07:06 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// pwd command .
void	ft_pwd_command(void)
{
	char	buf[225];

	printf("%s\n", getcwd(buf, 225));
}

// cd command .
void	ft_cd_command(char **split)
{
	chdir(split[1]);
}

// echo command .

char *ft_find_env_value(char *var_name, char **env)
{
	int i;

	i = 0;
	if (var_name[0] != '$')
		return NULL;
	var_name = (var_name + 1);
	while (env[i])
	{
		if (!ft_memcmp((var_name), env[i], ft_strlen(var_name)))
			return ((ft_strrchr(env[i], '=') + 1));
		i ++;
	}
	return (NULL);
}


void	ft_echo_command(char **split, char **env)
{
	int		i;
	int		name_end;
	char	*var_name;
	char	*var_value = NULL;
	int		flag;
	int		is_found;

	flag = 0;
	is_found = 0;
	if (!ft_memcmp(split[1], "-n", 3))
		flag = 1;
	i = 0;
	name_end = 0;
	if ((!ft_memcmp(split[1], "$", 1)))
		{
			while (split[1][i] != '\0')
			{
				while (split[1][i] == '$' && split[1][i + 1] == '$')
				{
					printf("%d", getpid());
					i += 2;
				}
				if (split[1][i] == '$' && split[1][i + 1] == '\0')
					(printf("$"), i ++);
				else
				{
					name_end = i;
					name_end ++;
					while (split[1][name_end] != '$' && split[1][name_end] != '\0')
						 name_end ++;
					var_name = ft_substr(split[1], i, (name_end - i));
					var_value = ft_find_env_value(var_name, env);
					if (var_value == NULL)
						printf("%s", var_name);
					else
						printf("%s", var_value);
					i += name_end;
				}
			}
		}
	else
		printf("%s", split[1]);
	if (!flag)
		printf("\n");
}
