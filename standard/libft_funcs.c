/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:28:55 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/14 16:33:29 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_super_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (n > 0)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		n--;
		c1++;
		c2++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
