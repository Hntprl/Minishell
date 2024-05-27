/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:56:06 by amarouf           #+#    #+#             */
/*   Updated: 2024/05/27 06:56:32 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd_command(char **split)
{
	free_strings(split);
	char buf[225];
	printf("%s\n", getcwd(buf, 225));
}

void	ft_cd_command(char **split)
{
	chdir(split[1]);
}

void	ft_echo_command(char **split)
{
	if (!ft_memcmp(split[1], "-n", 3))
		printf("%s%%",split[2]);
	else
		printf("%s\n",split[1]);
}