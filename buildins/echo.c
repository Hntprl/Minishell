/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:57:53 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 17:11:06 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_print_variables(char *command, int i, char **env)
{
	int		is_invalid;
	char	*var_name;
	char	*var_value;
	int		name_end;

	var_value = NULL;
	is_invalid = 0;
	name_end = i + 1;
	while (command[name_end] != '$' && command[name_end] != '\0')
		name_end++;
	var_name = ft_substr(command, i, (name_end - i));
	var_value = ft_find_env_value(var_name, env, &is_invalid);
	if (var_value == NULL)
		printf("%s", var_name);
	else
	{
		if (is_invalid)
			write(1, "", 1);
		else
			printf("%s", var_value);
	}
	free(var_name);
	return (i = name_end);
}

int	is_n(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	print_variables(char **command, int j, int i, char **env)
{
	while (command[j][i] != '\0')
	{
		while (command[j][i] == '$' && command[j][i + 1] == '$')
		{
			printf("%d", ft_getpid());
			i += 2;
		}
		if (command[j][i] == '$' && command[j][i + 1] == '\0')
			(printf("$"), i++);
		else
			i = echo_print_variables(command[j], i, env);
	}
	return (i);
}

int	ft_echo(int i, char **command, int j, char **env)
{
	if (command[j][i] == '$')
		i = print_variables(command, j, i, env);
	else
	{
		if (!is_n(command[j]))
			printf("%c", command[j][i]);
		i++;
	}
	return (i);
}

void	ft_echo_command(char **command, char **env)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	j = 1;
	if (is_n(command[j]))
		flag = 1;
	while (command[j])
	{
		i = 0;
		if (!command[j] || (flag && !command[2]))
			return (free(env));
		while (command[j][i])
			i = ft_echo(i, command, j, env);
		if (command[j + 1] && !is_n(command[j]))
			printf(" ");
		j++;
	}
	if (!flag)
		printf("\n");
	free(env);
}
