/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:52:11 by fbiberog          #+#    #+#             */
/*   Updated: 2024/11/05 16:42:45 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_var(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isalnum(line[i]))
		i++;
	return (i);
}

t_redirection	*create_redir_node(char *temp)
{
	t_redirection	*new_node;

	if (ft_strlen(temp) > 2)
		return (NULL);
	new_node = malloc(sizeof(t_redirection));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->file = NULL;
	if (ft_strcmp(temp, ">>") == 0)
		new_node->type = REDIR_OUT_APPEND;
	else if (ft_strcmp(temp, ">") == 0)
		new_node->type = REDIR_OUT;
	else if (ft_strcmp(temp, "<<") == 0)
		new_node->type = REDIR_IN_HERE_DOC;
	else if (ft_strcmp(temp, "<") == 0)
		new_node->type = REDIR_IN;
	else
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

int	check_redir(t_redirection **redirection, char *temp)
{
	t_redirection	*new_node;
	t_redirection	*last;

	new_node = create_redir_node(temp);
	if (!new_node)
		return (0);
	if (*redirection == NULL)
		*redirection = new_node;
	else
	{
		last = *redirection;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	return (1);
}

void	add_command(t_token *token, char *cmd, int array_len)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (array_len + 2));
	if (!ret)
		return ;
	while (i != array_len)
	{
		ret[i] = ft_strdup(token->command[i]);
		if (!ret[i])
		{
			free2pointers(ret);
			return (free2pointers(token->command));
		}
		i++;
	}
	ret[i] = ft_strdup(cmd);
	if (!ret[i])
		return (free2pointers(ret), free2pointers(token->command));
	ret[i + 1] = 0;
	free2pointers(token->command);
	token->command = ret;
	return ;
}

void	place_file(t_redirection **redirection, char *temp)
{
	t_redirection	*last;

	if (*redirection == NULL)
		return ;
	last = *redirection;
	while (last->next != NULL)
		last = last->next;
	if (last == NULL)
		return ;
	if (last->file)
		free(last->file);
	last->file = ft_strdup(temp);
	if (!last->file)
		return ;
}
