/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:56:06 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/03 18:56:40 by amarouf          ###   ########.fr       */
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
void	ft_echo_command(char **split, char **env)
{
	char *var_name;
	char *var_value;

	if (!ft_memcmp(split[1], "-n", 3))
		printf("%s%%", split[2]);
	else if ((var_name = ft_strrchr(split[1], '$')))
		{
			var_name = *ft_split(var_name, '$');
			while (*env ++)
			{
				if (!ft_memcmp(var_name, *env, ft_strlen(var_name)))
				{
					var_value = ft_strrchr(*env, '=');
					printf("%s\n", ++ var_value);
				}
			}
		}
	else
		printf("%s\n", split[1]);
}
