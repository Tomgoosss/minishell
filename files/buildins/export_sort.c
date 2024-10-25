/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:30:41 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 17:30:51 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sorted(t_env *var)
{
	t_node	*temp;

	temp = var->head_exp;
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->data, temp->next->data) > 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	sort_export(t_env *var)
{
	t_node	*head;

	head = var->head_exp;
	while (sorted(var) == 0 && head->next && head)
	{
		while (head && head->next)
		{
			if (ft_strcmp(head->data, head->next->data) > 0)
				swap_nodes(&head->data, &head->next->data);
			head = head->next;
		}
		head = var->head_exp;
	}
}
