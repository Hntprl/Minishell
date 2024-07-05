/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/05 11:32:07 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Array to lincked list .
char **ft_list_to_str(t_list *env)
{
	int i;
	char **envp;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = env->data;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// Execute shell commands (ls , grep ....) .
void shell_commands(char **split, t_list *env)
{
	char *path;
	char *cmd;
	int pid;
	char **envp;

	envp = ft_list_to_str(env);
	cmd = ft_strjoin("/", split[0]);
	pid = fork();
	if (pid == -1)
		(write(1, "Error:Fork!", 11), exit(1));
	path = ft_checkaccess(envp, ft_strjoin("/", split[0]));
	if (pid == 0)
		(commandcheck(envp, cmd), execve(ft_strjoin(path, cmd), split, envp));
	(free(path), wait(&pid));
}

// Commands :) .
void ft_command_check(char **split, t_list **ls_env)
{
	if (!ft_memcmp(split[0], "pwd", 4))
		ft_pwd_command();
	else if (!ft_memcmp(split[0], "cd", 3))
		ft_cd_command(split);
	else if (!ft_memcmp(split[0], "echo", 5))
		ft_echo_command(split, ft_list_to_str(*ls_env));
	else if (!ft_memcmp(split[0], "env", 4))
		ft_env_command(*ls_env);
	else if (!ft_memcmp(split[0], "unset", 6))
		ft_unset_command(split, ls_env);
	else if (!ft_memcmp(split[0], "export", 7))
		ft_export_command(split, *ls_env);
	else if (!ft_memcmp(split[0], "exit", 5))
		(write(1, "exit!\n", 6), exit(0));
	else if (!ft_memcmp(split[1], "|", 1))
		pipex(3, split, ft_list_to_str(*ls_env));
	else
		shell_commands(split, *ls_env);
}

// Split the input .
char **ft_line_split(char *line)
{
	char **split;

	split = ft_split(line, ' ');
	return (split);
}

// Read from 0 ...
void minishell(t_list *ls_env)
{
	char *rd_hestory;
	char **split;
	char *prompt;

	prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
	rd_hestory = readline(prompt);
	while (rd_hestory)
	{
		split = ft_line_split(rd_hestory);
		if (split[0] != NULL)
		{
			add_history(rd_hestory);
			ft_command_check(split, &ls_env);
			free_strings(split);
			free(rd_hestory);
		}
		rd_hestory = readline(prompt);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_lstclear(&ls_env);
	exit(0);
}
////////////////////////////////////////////////////////////////////////////////////////

t_lexer *create_lexer_token(char *str, t_tokens token)
{
	t_lexer *new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return (NULL);

	new_token->str = ft_strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		return (NULL);
	}

	new_token->token = token;
	new_token->i = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
	return new_token;
}
void add_token_to_collection(t_lexer **head, t_lexer *new_token)
{
	t_lexer *current;

	if (!*head)
	{
		*head = new_token;
		return;
	}

	current = *head;
	while (current->next)
		current = current->next;
	new_token->i = current->i + 1;
	current->next = new_token;
	new_token->prev = current;
}
// check qoutes still open ..
void check_qoutes(char *str)
{
	int i;
	int qoutes;
	int double_qoutes;

	i = 0;
	qoutes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			double_qoutes++;
		if (str[i] == '\'')
			qoutes++;
		i++;
	}
	if (qoutes % 2 != 0 || double_qoutes % 2 != 0)
	{
		write(1, "Error: qoutes still open!\n", 26);
		exit(1);
	}
}
//get pid of current process
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
	{
		close(fd);
		exit(1);
	}
	buffer[bytes_read] = '\0';

	close(fd);
	char *ptr = buffer;
	while (*ptr != ' ' && *ptr != '\0')
	{
		ptr++;
	}
	return (pid = ft_atoi(buffer));
}

// to get pid of curent process use  cat /proc/self/stat
int main(int ac, char **av) //, char **env)
{
	(void)av;
	
	t_lexer *head = NULL;
	char *rd_hestory;
	char *prompt;
	t_lexer *word_token;
	t_lexer *pipe_token;
	t_lexer *redirection_append_token;
	t_lexer *redirection_in_token;
	t_lexer *redirection_out_token;
	t_lexer *heredoc_token;
	if (ac == 1)
	// minishell(fill_envp(env));
	{
		prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
		rd_hestory = readline(prompt);
		// printf("%s\n", rd_hestory);
		int i = 0;
		while (rd_hestory && rd_hestory[i])
		{
			if (rd_hestory[i] == '|')
			{
				pipe_token = create_lexer_token("|", PIPE);
				add_token_to_collection(&head, pipe_token);
				i++;
			}
			else if (ft_strncmp(&rd_hestory[i], ">>", 2) == 0)
			{
				redirection_append_token = create_lexer_token(">>", REDIRECTION_APPEND);
				add_token_to_collection(&head, redirection_append_token);
				i += 2;
			}
			else if (rd_hestory[i] == '<' && rd_hestory[i + 1] != '<')
			{
				redirection_in_token = create_lexer_token("<", REDIRECTION_IN);
				add_token_to_collection(&head, redirection_in_token);
				i++;
			}
			else if (rd_hestory[i] == '>' && rd_hestory[i + 1] != '>')
			{
				redirection_out_token = create_lexer_token(">", REDIRECTION_OUT);
				add_token_to_collection(&head, redirection_out_token);
				i++;
			}
			else if (ft_strncmp(&rd_hestory[i], "<<", 2) == 0)
			{
				heredoc_token = create_lexer_token("<<", HEREDOC);
				add_token_to_collection(&head, heredoc_token);
				i += 2;
			}

			else
			{
				int j = i;
				while (rd_hestory[j] != '\0' && rd_hestory[j] != ' ' && rd_hestory[j] != '\t' && rd_hestory[j] != '|' && ft_strncmp(&rd_hestory[j], ">>", 2) != 0 && rd_hestory[j] != '<' && rd_hestory[j] != '>' && ft_strncmp(&rd_hestory[j], "<<", 2) != 0)
					j++;
				if (j > i)
				{
					char *word = ft_substr(&rd_hestory[i], 0, j - i);
					word_token = create_lexer_token(word, WORD);
					add_token_to_collection(&head, word_token);
					free(word);
					i = j;
				}
				i++;
			}
		}
		free(rd_hestory);
		rd_hestory = readline(prompt);
	}
	// PRINT TOKENS

	t_lexer *current = head;
	while (current)
	{
		// printf("Token type: %d\n", current->token);
		printf("Token: %s\n", current->str);
		printf("Token index: %d\n", current->i);
		printf("<---->");
		current = current->next;
	}
	exit(0);
}
