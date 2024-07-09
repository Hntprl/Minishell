/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:52:00 by ochemsi           #+#    #+#             */
/*   Updated: 2024/07/09 01:11:43 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_qoutes(char *str)
{
	int i;
	int qoutes;
	int double_qoutes = 0;
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