/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:41 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 16:36:12 by fbiberog         ###   ########.fr       */
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

char	*create_shlvl(char *line)
{
	char	*shlvl;
	int		temp;

	temp = ft_atoi(line + 6);
	temp++;
	if (temp >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(temp, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		temp = 1;
	}
	shlvl = ft_itoa(temp);
	return (shlvl);
}

void	fill_nodes_env(t_env *var, char **env)
{
	int		i;
	char	*shlvl;
	char	*temp;

	i = 0;
	shlvl = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			temp = ft_strjoin("SHLVL=", create_shlvl(env[i]));
			if (!temp)
				return ;
			add_node(&var->head_env, make_node(temp));
			add_node(&var->head_exp, make_node(temp));
			free(temp);
			free(shlvl);
		}
		else
		{
			add_node(&var->head_env, make_node(env[i]));
			add_node(&var->head_exp, make_node(env[i]));
		}
		i++;
	}
}
