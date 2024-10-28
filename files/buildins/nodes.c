/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:41 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 17:31:06 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_nodes(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

t_node	*make_node(char *line)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->data = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*temp;

	if (new == NULL || head == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void	fill_nodes_env(t_env *var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			handle_shlvl(var, env[i]);
		else
		{
			add_node(&var->head_env, make_node(env[i]));
			add_node(&var->head_exp, make_node(env[i]));
		}
		i++;
	}
}
