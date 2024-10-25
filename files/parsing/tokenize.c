/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:36:28 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 17:43:47 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token **token, int pipe)
{
	if (pipe)
	{
		(*token)->next = malloc(sizeof(t_token));
		if (!(*token)->next)
		{
			free(*token);
			return ;
		}
		(*token) = (*token)->next;
	}
	(*token)->redirection = NULL;
	(*token)->next = NULL;
	(*token)->command = NULL;
}

void	tokenize(t_token **token, char **temp)
{
	t_token	*temp_token;
	int		i;
	int		cmd;

	i = 0;
	cmd = 0;
	init_token(token, 0);
	if (!(*token))
		return (free2pointers(temp), free(*token));
	temp_token = *token;
	while (temp[i])
	{
		if (temp[i][0] == '|')
		{
			if (temp[i + 1] == NULL)
			{
				printf("syntax error near unexpected token `|'\n");
				return (free2pointers(temp), free2pointers(temp_token->command),
					free(temp_token));
			}
			init_token(&(*token), 1);
			if (!(*token))
				return (free2pointers(temp), free2pointers(temp_token->command),
					free(temp_token));
			i++;
			cmd = 0;
		}
		else if (check_redir(&(*token)->redirection, temp[i]))
		{
			if (temp[i + 1] && valid_redirection(temp[i + 1]))
			{
				place_file(&(*token)->redirection, temp[i + 1]);
				if (!(*token)->redirection->file)
					return (free2pointers(temp),
						free2pointers((*token)->command), free(*token));
				i += 2;
			}
			else
			{
				printf("syntax error near unexpected token `%c'\n", temp[i][0]);
				free2pointers(temp);
				free2pointers((*token)->command);
				free(*token);
				*token = NULL;
				return ;
			}
		}
		else
		{
			add_command(*token, temp[i], cmd);
			if (!(*token)->command)
				return (free2pointers(temp), free2pointers((*token)->command),
					free(*token));
			cmd++;
			i++;
		}
	}
	free2pointers(temp);
	*token = temp_token;
}
