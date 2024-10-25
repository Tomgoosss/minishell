/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/22 16:37:29 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_whitespaces(char *line, int i)
{
	if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f'))
		return (-1);
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		&& line[i])
	{
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	return (1);
}

int	closing_quote(char *line, int i, char c, int extra)
{
	i++;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	if (extra == 0)
		return (0);
	return (-1);
}

void	remove_node(t_token **token)
{
	t_token	*temp;

	if (token == NULL || *token == NULL)
		return ;
	temp = (*token)->next;
	(*token)->next = temp->next;
	free(temp);
}

t_token	*main_pars(char *line, t_env *var, t_ex *ex)
{
	t_token	*token;
	char	**temp;
	char	*updated_line;

	if (empty_line(line))
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	updated_line = check_dollar_sign(line, var, ex);
	temp = ft_split_mod(updated_line, ' ');
	if (!temp)
		return (free(token), free(updated_line), NULL);
	tokenize(&token, temp);
	free(updated_line);
	if (!token)
	{
		ex->exit_status = 2;
		return (NULL);
	}
	return (token);
}
