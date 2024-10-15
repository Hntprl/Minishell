/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 17:11:14 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpid(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	int		pid;
	char	*ptr;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		exit(1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
		(close(fd), exit(1));
	buffer[bytes_read] = '\0';
	close(fd);
	ptr = buffer;
	while (*ptr != ' ' && *ptr != '\0')
		ptr++;
	return (pid = ft_atoi(buffer));
}

int	ft_buildins(t_parser *parser, t_list **ls_env)
{
	if (!ft_memcmp(parser->command[0], "pwd", 4))
		return (ft_pwd_command(), 1);
	else if (!ft_memcmp(parser->command[0], "cd", 3))
		return (ft_cd_command(parser->command, ls_env), 1);
	else if (!ft_memcmp(parser->command[0], "echo", 5))
		return (ft_echo_command(parser->command, ft_list_to_str(*ls_env)), 1);
	else if (!ft_memcmp(parser->command[0], "env", 4))
		return (ft_env_command(*ls_env), 1);
	else if (!ft_memcmp(parser->command[0], "unset", 6))
		return (ft_unset_command(parser->command[1], ls_env), 1);
	else if (!ft_memcmp(parser->command[0], "export", 7))
		return (ft_export_command(parser->command, ls_env), 1);
	else if (!ft_memcmp(parser->command[0], "exit", 5))
		return ((write(1, "exit\n", 5), exit(0)), 1);
	else if (parser->command[0][0] == '$')
		return (ft_expander(parser->command[0], ft_list_to_str((*ls_env))), 1);
	else
		return (0);
}

void	minishell(t_list *ls_env)
{
	t_lexer		*lexer;
	t_parser	*parser;
	char		*prompt;
	char		*rd_history;

	lexer = NULL;
	parser = NULL;
	prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
	rd_history = readline(prompt);
	while (rd_history)
	{
		if (rd_history[0])
			process_input(&lexer, &parser, rd_history, &ls_env);
		rd_history = readline(prompt);
	}
	write(1, "exit\n", 5);
	// rl_clear_history();
	ft_lstclear(&ls_env);
	exit(0);
}

// main function
int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		minishell(fill_envp(env));
	}
	exit(0);
}
