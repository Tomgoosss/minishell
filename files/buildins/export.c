/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:24 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 16:39:35 by fbiberog         ###   ########.fr       */
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

char	*prepare_for_export(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(line) + 3);
	while (line[i] && line[i] != '=')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] == '=')
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '"';
	while (line[i])
	{
		ret[i + 1] = line[i];
		i++;
	}
	ret[i + 1] = '"';
	ret[i + 2] = '\0';
	return (ret);
}

void	printf_export(t_env *var)
{
	t_node	*temp;
	char	*str;

	temp = var->head_exp;
	str = NULL;
	while (temp)
	{
		str = prepare_for_export(temp->data);
		printf("declare -x %s\n", temp->data);
		temp = temp->next;
		free(str);
	}
	temp = var->head_env;
}

int	remove_double_env(t_env *var, char *arg)
{
	t_node	*temp;
	int		len;

	len = 0;
	temp = var->head_env;
	while (arg[len] && (arg[len] != '=' || arg[len] == '\0'))
		len++;
	if (arg[len] == '\0')
		len--;
	while (temp)
	{
		if (ft_strncmp(temp->data, arg, len + 1) == 0)
		{
			remove_current_node(&var->head_env, temp);
			return (1);
		}
		temp = temp->next;
	}
	return (1);
}

void	remove_current_node(t_node **head, t_node *node)
{
	t_node	*temp;

	if (!head || !*head || !node)
		return ;
	if (*head == node)
	{
		*head = node->next;
		free(node->data);
		free(node);
		return ;
	}
	temp = *head;
	while (temp && temp->next != node)
		temp = temp->next;
	if (temp)
	{
		temp->next = node->next;
		free(node->data);
		free(node);
	}
}
