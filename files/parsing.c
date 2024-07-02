/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/07/02 18:57:48 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check_whitespaces function is used to skip whitespaces in the line
// it returns
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

//
	//check_redirections function is used to check if there is any redirection in the line
// // it returns -1 if there is no redirection in the line
// // it returns 1 if there is a redirection in the line
// // it returns 0 if there is a redirection in the line but it is not valid,

int	check_redirections(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			break ;
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	i = 0;
	while (line[i + 2])
	{
		if (((line[i] == '<' && line[i + 1] == '<') || ((line[i] == '>')
					&& line[i + 1] == '>')) && check_whitespaces(line, (i
					+ 2)) == 1)
			return (1);
		if (check_whitespaces == -1)
			return (0);
		i++;
	}
	return (0);
}

int	closing_quote(char *line, int i, char c)
{
	i++;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}


void	tokenize(t_token **token, char *line)
{
	t_token	*head;
	char	**temp;
	int		i;

	i = 0;
	head = (*token);
	temp = ft_split(line, ' ');
	while (temp[i])
	{
		(*token)->command = temp[i];
		(*token)->next = malloc(sizeof(t_token));
		if (ft_strcmp(temp[i], "|") == 0)
			(*token)->type = 1;
		else if (ft_strcmp(temp[i], "<") == 0)
			(*token)->type = 2;
		else if (ft_strcmp(temp[i], "<<") == 0)
			(*token)->type = 3;
		else if (ft_strcmp(temp[i], ">") == 0)
			(*token)->type = 4;
		else if (ft_strcmp(temp[i], ">>") == 0)
			(*token)->type = 5;
		else
			(*token)->type = 0;
		(*token) = (*token)->next;
		i++;
	}
	(*token)->next = NULL;
	(*token) = head;
}

void prep_commands(t_token **token, char *line)
{
	t_token *head;
	int i;
	
	i = 0;
	head = (*token);
	while((*token)->next)
	{
		if((*token)->type == 0)
			if((*token)->command[0][0] == '\'' || (*token)->command[0][0] == 34)
				(*token)->type == 6;
			else
				(*token)->type == 7;
		(*token) = (*token)->next;
	}
	(*token) = head;
	return;
}
void	main_pars(char *line, t_env *var)
{
	t_token *token;
	token = malloc(sizeof(t_token));
	tokenize(&token, line);
	// prep_commands(&token , line);
	// while(token->next)
	// {
	// 	printf("command; %s , %i\n", token->command, token->type);
	// 	token = token->next;
	// }
	return ;
}
