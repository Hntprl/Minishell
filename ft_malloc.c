/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-21 14:45:31 by amarouf           #+#    #+#             */
/*   Updated: 2024-10-21 14:45:31 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

t_garbage	*new_garbage(void *allocation, bool is_free)
{
	t_garbage	*node;

    node = malloc(sizeof(t_garbage));
    if (!node)
    {
        (ft_malloc(0, 'f', true), exit(1));
    }
	node->data = allocation;
	node->is_free = is_free;
	node->next = NULL;
	return (node);
}

void	free_garbage(t_garbage *collector)
{
    t_garbage   *current;
    t_garbage   *next;

    current = collector;
	while (current)
	{
        next = current->next;
        if (!current->is_free)
            free(current->data);
        free(current);
        current = next;
	}
}

void    add_new_garbage(void *allocation, t_garbage *collector, bool is_free)
{
    while (collector->next)
    {
        collector = collector->next;
    }
    collector->next = new_garbage(allocation, is_free);
}

void *ft_malloc(size_t size, char alloc, bool is_free)
{
	static  t_garbage	*collector;
	void				*allocation;

	allocation = NULL;
	if (alloc == 'a')
	{
		allocation = malloc(size);
		if (!allocation)
			(ft_malloc(0, 'f', false), exit(1));
		if (!collector)
			collector = new_garbage(allocation, is_free);
		else
			add_new_garbage(allocation, collector, is_free);
	}
	if (alloc == 'f')
		free_garbage(collector);
	return (allocation);
}
