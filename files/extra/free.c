/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:13 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 17:36:03 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free2pointers(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_node *head)
{
	t_node	*tmp;
	t_node	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
}

void	free_redirection(t_redirection *redirection)
{
	t_redirection	*tmp;
	t_redirection	*next;

	tmp = redirection;
	while (tmp->next)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
}

void	free_token_line(t_token *token, char *line)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	if (line)
		free(line);
	while (tmp)
	{
		if (tmp->redirection)
			free_redirection(tmp->redirection);
		next = tmp->next;
		free2pointers(tmp->command);
		free(tmp);
		tmp = next;
	}
}
