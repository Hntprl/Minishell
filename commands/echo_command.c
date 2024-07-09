/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:57:53 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/08 01:32:10 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_getpid(void)
{
	int fd;
	char buffer[256];
	ssize_t bytes_read;
	int pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		exit(1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
		(close(fd), exit(1));
	buffer[bytes_read] = '\0';
	close(fd);
	char *ptr = buffer;
	while (*ptr != ' ' && *ptr != '\0')
		ptr++;
	return (pid = ft_atoi(buffer));
}

int echo_print_variables(char *command, int i, char **env)
{
	char	*var_name;
	char	*var_value = NULL;
	int		name_end;

	name_end = i + 1;
	while (command[name_end] != '$' && command[name_end] != '\0')
		name_end ++;
	var_name = ft_substr(command, i, (name_end - i));
	var_value = ft_find_env_value(var_name, env);
	if (var_value == NULL)
		printf("%s", var_name);
	else
		printf("%s", var_value);
	return (i = name_end);
}

void	ft_echo_command(char **command, char **env)
{
	int		i;
	int		j;
	int		flag;
	int		is_found;

	flag = 0;
	is_found = 0;
	j = 1;
	if (!ft_memcmp(command[1], "-n", 3))
		flag = 1;
	while (command[j])
	{
		i = 0;
		if (!command[j])
			printf("");
		else if ((!ft_memcmp(command[j], "$", 1)))
			{
				while (command[j][i] != '\0')
				{
					while (command[j][i] == '$' && command[j][i + 1] == '$')
					{
						printf("%d", ft_getpid());
						i += 2;
					}
					if (command[j][i] == '$' && command[j][i + 1] == '\0')
						(printf("$"), i ++);
					else
						i = echo_print_variables(command[j], i, env);
				}
			}
		else
			printf("%s", command[j]);
		printf(" ");
		j ++;
	}
	if (!flag)
		printf("\n");
	free(env);
}
